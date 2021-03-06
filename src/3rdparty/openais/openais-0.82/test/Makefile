# Copyright (c) 2002-2004 MontaVista Software, Inc.
# Copyright (c) 2006-2007 Red Hat, Inc.
# Copyright (c) 2006 Sun Microsystems, Inc.
# 
# All rights reserved.
# 
# This software licensed under BSD license, the text of which follows:
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# - Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
# - Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
# - Neither the name of the MontaVista Software, Inc. nor the names of its
#   contributors may be used to endorse or promote products derived from this
#   software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
# THE POSSIBILITY OF SUCH DAMAGE.

# Include configuration
#
include ../Makefile.inc

ifeq (${OPENAIS_COMPAT}, SOLARIS)
	override LDFLAGS += -lnsl -lsocket -lrt
endif

LIBRARIES= ../lib/libSaClm.a ../lib/libSaAmf.a ../lib/libSaCkpt.a ../lib/libSaEvt.a ../lib/libSaLck.a ../lib/libSaMsg.a ../lib/libevs.a ../lib/libcpg.a ../lib/libcfg.a
LIBS = $(LIBRARIES) 

override CFLAGS += -I../include
override LDFLAGS += -L../lib

EXTRA_CFLAGS = -I../include
TEST_SRC =  testclm.c testamf1.c \
	testamf4.c testamf5.c testamf6.c testamfth.c  \
	testckpt.c ckptstress.c ckptbench.c  \
	ckptbenchth.c testevt.c testevs.c evsbench.c \
	subscription.c publish.c evtbench.c \
	sa_error.c unlink.c testclm2.c testlck.c testmsg.c \
	logsys_s1.c logsys_s2.c logsys_s.c logsys_t1.c logsys_t2.c

all: testclm testamf1 \
	testckpt ckptstress ckptbench \
	ckptbenchth ckpt-rd ckpt-wr testevt testevs \
	evsbench subscription publish evtbench unlink testclm2 testlck \
	testmsg testcpg testcpg2 cpgbench openais-cfgtool \
	logsys_s logsys_t1 logsys_t2

testtimer: testtimer.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testtimer testtimer.o ../exec/timer.o

testamf: testamf.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testamf testamf.o $(LIBS)

testamf1: testamf1.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testamf1 testamf1.o $(LIBS)

testamf2: testamf2.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testamf2 testamf2.o $(LIBS)

testamf3: testamf3.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testamf3 testamf3.o $(LIBS)

testamf4: testamf4.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testamf4 testamf4.o $(LIBS)

testamf5: testamf5.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testamf5 testamf5.o $(LIBS)

testamf6: testamf6.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testamf6 testamf6.o $(LIBS)

testamfth: testamfth.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testamfth testamfth.o $(LIBS)

testevt: testevt.o sa_error.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testevt testevt.o sa_error.o $(LIBS)

testevs: testevs.o $(LIBS)
	$(CC) $(LDFLAGS) -o testevs testevs.o $(LIBS)

testevsth: testevsth.o $(LIBS)
	$(CC) $(LDFLAGS) -o testevsth testevsth.o $(LIBS)

evsbench: evsbench.o $(LIBS)
	$(CC) $(LDFLAGS) -o evsbench evsbench.o $(LIBS)

testclm: testclm.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testclm testclm.o $(LIBS)

testckpt: testckpt.o sa_error.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testckpt testckpt.o sa_error.o $(LIBS)

ckptbench: ckptbench.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o ckptbench ckptbench.o sa_error.o $(LIBS)

ckptbenchth: ckptbenchth.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o ckptbenchth ckptbenchth.o sa_error.o $(LIBS)

ckptstress: ckptstress.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o ckptstress ckptstress.o $(LIBS)

subscription: subscription.o sa_error.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o subscription subscription.o sa_error.o $(LIBS)

publish: publish.o sa_error.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o publish publish.o sa_error.o $(LIBS)

unlink: unlink.o sa_error.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o unlink unlink.o sa_error.o $(LIBS)

evtbench: evtbench.o sa_error.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o evtbench evtbench.o sa_error.o $(LIBS)

test: test.o $(LIBRARIES)
	g++ $(LDFLAGS) -o test test.o $(LIBS)

ckpt-rd: ckpt-rd.o sa_error.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o ckpt-rd ckpt-rd.o sa_error.o $(LIBS)

ckpt-wr: ckpt-wr.o sa_error.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o ckpt-wr ckpt-wr.o sa_error.o $(LIBS)

testclm2: testclm2.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testclm2 testclm2.o $(LIBS)

testlck: testlck.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testlck testlck.o $(LIBS)

testmsg: testmsg.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testmsg testmsg.o $(LIBS)

testcpg: testcpg.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testcpg testcpg.o $(LIBS)

testcpg2: testcpg2.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o testcpg2 testcpg2.o $(LIBS)

cpgbench: cpgbench.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o cpgbench cpgbench.o $(LIBS)

openais-cfgtool: openais-cfgtool.o $(LIBRARIES)
	$(CC) $(LDFLAGS) -o openais-cfgtool openais-cfgtool.o $(LIBS)

logsys_s: logsys_s.o logsys_s1.o logsys_s2.o ../exec/liblogsys.a
	$(CC) $(LDFLAGS) -o logsys_s logsys_s.o logsys_s1.o logsys_s2.o ../exec/liblogsys.a

logsys_t1: logsys_t1.o ../exec/liblogsys.a
	$(CC) $(LDFLAGS) -o logsys_t1 logsys_t1.o ../exec/liblogsys.a

logsys_t2: logsys_t2.o ../exec/liblogsys.a
	$(CC) $(LDFLAGS) -o logsys_t2 logsys_t2.o ../exec/liblogsys.a

clean:
	rm -f *.o testclm testamf testamf1 testamf2 testamf3 testamf4 \
	testamf5 testamf6 testamfth testckpt ckptstress testtimer \
	ckptbench ckptbenchth testevt testevs ckpt-wr ckpt-rd \
	evsbench subscription publish evtbench unlink testmsg testcpg \
	testclm2 testlck

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -c -o $@ $<

depend:
	makedepend -Y -- $(CFLAGS) $(CPPFLAGS) $(TEST_SRC) > /dev/null 2>&1
# DO NOT DELETE

testclm.o: ../include/saAis.h ../include/saClm.h
testamf.o: ../include/saAis.h ../include/saAmf.h ../include/saClm.h
testamf1.o: ../include/saAis.h ../include/saAmf.h
testamf2.o: ../include/saAis.h ../include/saAmf.h
testamf3.o: ../include/saAis.h ../include/saAmf.h
testamf4.o: ../include/saAis.h ../include/saAmf.h
testamf5.o: ../include/saAis.h ../include/saAmf.h
testamf6.o: ../include/saAis.h ../include/saAmf.h
testamfth.o: ../include/saAis.h ../include/saAmf.h ../include/saClm.h
testckpt.o: ../include/saAis.h ../include/saCkpt.h sa_error.h
ckptstress.o: ../include/saAis.h ../include/saCkpt.h
ckptbench.o: ../include/saAis.h ../include/saCkpt.h
ckptbenchth.o: ../include/saAis.h ../include/saCkpt.h
testevt.o: ../include/saAis.h ../include/saEvt.h
testevs.o: ../include/evs.h
evsbench.o: ../include/saAis.h ../include/evs.h
subscription.o: ../include/saAis.h ../include/saEvt.h
publish.o: ../include/saAis.h ../include/saEvt.h
evtbench.o: ../include/saAis.h ../include/saEvt.h
sa_error.o: ../include/saAis.h
unlink.o: ../include/saAis.h ../include/saEvt.h
