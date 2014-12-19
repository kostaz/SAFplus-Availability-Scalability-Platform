import pdb
import microdom
from types import *
import common
import svg

nameIdx = {
}

def NameCreator(typ):
  """Create a unique name by using the type and an instance number"""
  idx = nameIdx.get(typ, 1)
  nameIdx[typ] = idx+1
  return typ + str(idx)

def EntityTypeSortOrder(a,b):
  if not type(a[1]) is DictType:
    return 1
  if not type(b[1]) is DictType:
    return -1
  return cmp(a[1].get("order",10000),b[1].get("order",10001))
  

class EntityType:
  """This defines the concept, for example 'Service Group'"""
  def __init__(self,name, data, context=None):
    self.name = name
    self.data = data
    self.context = context  # I may need to know the larger context (the model) to resolve types
    self.iconFile = data.get("icon", "generic.svg")
    f = open(common.fileResolver(self.iconFile),"r")
    self.iconSvg =  svg.Svg(f.read(),(256,128))
    f.close()

    self.buttonFile = data.get("button", "generic_button.svg")
    f = open(common.fileResolver(self.buttonFile),"r")
    self.buttonSvg =  svg.Svg(f.read(),(32,32))
    f.close()

  def createEntity(self,pos, size=None):
    """Create an entity of this type"""
    if not size:
      size = self.iconSvg.size
    ret = Entity(self, pos,size)
    return ret
 

class ContainmentArrow:
  def __init__(self, container, offset, contained, end_offset, midpoints=None):
    """Creates a containment arrow.  Pass the "container" Entity object and the pixel tuple "offset" from the container's position.  And pass the "contained" Entity object and the pixel tuple "offset" from the contained's position.  The midpoints parameter allows the arrow to be curved using sequential first order bezier curves
    """
    self.container = container
    self.beginOffset = offset
    self.contained = contained
    self.endOffset = end_offset
    self.midpoints = midpoints

class Entity:
  """This is a UML object of a particular entity type, for example the 'Apache' service group"""
  def __init__(self, entityType, pos, size,name=None):
    self.et = entityType
    assert(type(pos) == TupleType);
    self.pos  = pos
    self.size = size
    self.scale = (1.0,1.0)
    self.rotate = 0.0
    self.data = {}
    self.updateDataFields()
    self.instanceLocked = {}  # Whether this data data fields can be changed by an instance
    self.data["entityType"] = self.et.name
    self.data["name"] = NameCreator(entityType.name) if name is None else name
    self.bmp  = self.et.iconSvg.instantiate(self.size,self.data)
    self.containmentArrows = []

  def canContain(self, entity):
    """Return true if this entity can contain the passed entity"""
    # TODO: check the entitytype relationship
    # TODO: make sure that the ordinality is correct (i.e. if self can only contain one entity, make sure that currently self is containing no of them)
    return True

  def canBeContained(self, entity):
    """Return true if this entity can be contained by the passed entity"""
    # TODO: check the entitytype relationship
    # TODO: make sure that the ordinality is correct (i.e. if self can only be contained by one entity, make sure that currently self is contained by no entity)
    return True

  def xxxinstantiateData(self,entity, dataDict):
    for (itemName,itemData) in entity.et.data.items():
      if not type(item[1]) is DictType: continue  # Its not a datatype skip it
      val = None
      if dataDict.has_key(itemName):
        val = dataDict[itemName]
        # TODO validate proper val type and range based on definition in itemData
      elif entity.data.has_key(itemName):
        val = entity.data[itemName] # No override provided so use what already exists
      else: # Use default
        # TODO should the default set, or left blank to indicate that it is the default?
        val = "" # TODO look in itemData for the default  
      entity.data[itemName] = val

  def updateDataFields(self, dataDict = None):
    """Creates/modifies the data fields in this entity based on the entityType"""
    new = self.data  # Keep what is already there
    for (name,metadata) in self.et.data.items():  # Dig thru everything in the entity type, moving it all into the entity
      if type(metadata) == DictType: # If its not a dictionary type it cannot be changed; don't copy over
        if dataDict and dataDict.has_key(name):
          val = dataDict[name]
          if microdom.microdomFilter(val):
            new[name] = val.data_.strip()
          else: new[name] = val
        elif self.data.has_key(name):  # If its assigned pull it over
          new[name] = self.data[name]
        else:  # Create it new
          if metadata.has_key("default"):
            new[name] = metadata["default"]
          elif metadata.has_key("type"):
            new[name] = self.et.context.defaultForType(metadata["type"])
          else:
            new[name] = ""
    # self.data = new  

class Instance:
  """This is an actual instance of an Entity, for example the 'Apache' service group running on node 'ctrl0'"""
  def __init__(self, entity, data):
    self.entity = entity
    self.data = data #micro dom data
    #binding entity and data, this make straight render in gui
    #{entity.a : value1, entity.b: value 2}