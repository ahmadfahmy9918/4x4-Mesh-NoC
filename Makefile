#
CC=/usr/bin/g++
ARCH := $(shell arch)
SYSTEMC_HOME=/usr/local/SystemC-2.3.0

# 64bit or 32bit libaries to link to
LINUXLIB := $(shell if [ ${ARCH} = "i686" ]; \
                    then \
                         echo lib-linux; \
                    else \
                         echo lib-linux64; \
                    fi)

INCLUDES = -I$(SYSTEMC_HOME)/include -I.

LIBRARIES = -L. -L$(SYSTEMC_HOME)/$(LINUXLIB) -lsystemc -lm

RPATH = -Wl,-rpath=$(SYSTEMC_HOME)/$(LINUXLIB)

PROGRAM = noc.x
SRCS    =  arbiter.cpp buf_fifo.cpp crossbar.cpp router.cpp sink.cpp source.cpp  main_noc.cpp
OBJS    =  arbiter.o buf_fifo.o crossbar.o router.o sink.o source.o  main_noc.o


all : $(PROGRAM)

$(OBJS)	: $(SRCS)
	$(CC) $(INCLUDES) -c $(SRCS)

$(PROGRAM) : $(OBJS)
	$(CC) $(INCLUDES) $(LIBRARIES) $(RPATH) -o $(PROGRAM) $(OBJS)

clean:
	@rm -f $(OBJS) $(PROGRAM) *.cpp~ *.h~
