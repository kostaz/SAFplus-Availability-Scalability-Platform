S7 := 1
SAFPLUS_MSG_PLUGIN := 1
include ../../mk/preface.mk

CPP_FLAGS += -I$(BOOST_DIR) -I. -I.. -I../../protoc

CLIENT_H := $(wildcard *.hxx) $(wildcard $(SAFPLUS_INC_DIR)/*.hxx)
CLIENT_SRC := $(wildcard *.cxx)
CLIENT_OBJ := $(addprefix $(OBJ_DIR)/,$(subst .cxx,.o,$(CLIENT_SRC)))

CHECK_INOTIFY := $(shell ../check_inotify.sh $(COMPILE_CPP))
ifeq ($(strip $(CHECK_INOTIFY)), )
	CPP_FLAGS += -DHAVE_INOTIFY
endif

CHECK_SCTP := $(strip $(shell ../check_sctp.sh $(COMPILE_CPP)))

ifeq ($(CHECK_SCTP), )
	CPP_FLAGS += -DHAVE_SCTP
        SCTP_TARGET := $(PLUGIN_DIR)/clMsgSctp.so
else
# on Ubuntu: sudo apt-get install libsctp-dev lksctp-tools
$(info Operating system does not have SCTP support.  SCTP message transport plugin will not be compiled)
 SCTP_TARGET :=
endif

# Specify the required libraries
SAFPLUS_LIBS := clMsg
# Then use these in the make rule
SAFPLUS_DEP_LIBS  := $(addsuffix .so,$(addprefix $(LIB_DIR)/lib,$(SAFPLUS_LIBS)))
SAFPLUS_LINK_LIBS := -L$(LIB_DIR) $(addprefix -l,$(SAFPLUS_LIBS))

LINK_SO_LIBS += -lboost_thread

Release all: $(PLUGIN_DIR)/clMsgUdp.so $(SCTP_TARGET) $(PLUGIN_DIR)/clMsgTcp.so $(PLUGIN_DIR)/clMsgTipc.so

# Note, I have to link with libclMsg because base class functions are implemented in there.  TODO: move these into a separate .o that can be directly linked so that the message transport plugins are completely standalone

$(PLUGIN_DIR)/clMsgUdp.so: $(OBJ_DIR)/msgUdp.o $(OBJ_DIR)/clPluginHelper.o
	$(LINK_SO) $@ $^ $(SAFPLUS_LINK_LIBS) $(LINK_SO_LIBS)

$(PLUGIN_DIR)/clMsgSctp.so: $(OBJ_DIR)/msgSctp.o $(OBJ_DIR)/clPluginHelper.o
	$(LINK_SO) $@ $^ $(SAFPLUS_LINK_LIBS) $(LINK_SO_LIBS)

$(PLUGIN_DIR)/clMsgTcp.so: $(OBJ_DIR)/msgTcp.o $(OBJ_DIR)/clPluginHelper.o
	$(LINK_SO) $@ $^ $(SAFPLUS_LINK_LIBS) $(LINK_SO_LIBS)

$(PLUGIN_DIR)/clMsgTipc.so: $(OBJ_DIR)/msgTipc.o $(OBJ_DIR)/clPluginHelper.o
	$(LINK_SO) $@ $^ $(SAFPLUS_LINK_LIBS) $(LINK_SO_LIBS)

$(OBJ_DIR)/%.o: %.cxx Makefile $(CLIENT_H)
	$(COMPILE_CPP) $@ $<

clean:
	rm -f $(PLUGIN_DIR)/clMsgUdp.so $(PLUGIN_DIR)/clMsgSctp.so $(CLIENT_OBJ) $(PLUGIN_DIR)/clMsgTcp.so

include $(SAFPLUS_MAKE_DIR)/safplus_targets.mk
