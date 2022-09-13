CROSS_COMPILE ?=
GCC   ?= $(CROSS_COMPILE)gcc
GXX   ?= $(CROSS_COMPILE)g++
STRIP ?= $(CROSS_COMPILE)strip

C_FLAGS := -Wall -Wno-unused-but-set-variable -Os -fPIC -DPIC -ffunction-sections -DWITH_OPENSSL

LDFLAGS := -lpthread -lcrypto -lssl

C_INCLUDES :=

LIBS  = libonvif.a
PROGS = onvif-server

OMX_COMP_C_SRCS=$(wildcard ./*.c)
OMX_COMP_C_SRCS_NO_DIR=$(notdir $(OMX_COMP_C_SRCS))
OBJECTS=$(patsubst %.c, %.c.o, $(OMX_COMP_C_SRCS_NO_DIR))

OMX_COMP_CPP_SRCS=$(wildcard ./*.cpp)
OMX_COMP_CPP_SRCS_NO_DIR=$(notdir $(OMX_COMP_CPP_SRCS))
CXXOBJS=$(patsubst %.cpp, %.cpp.o, $(OMX_COMP_CPP_SRCS_NO_DIR))

OBJDIR ?= $(shell pwd)/obj
LIBDIR ?= $(shell pwd)/lib
BINDIR ?= $(shell pwd)/bin
INCDIR ?= $(shell pwd)/inc

OBJLIB  = $(addprefix $(LIBDIR)/, $(LIBS))
OBJPROG = $(addprefix $(BINDIR)/, $(PROGS))

.PHONY: clean prepare LIBS PROGS

all: prepare $(OBJLIB) $(OBJPROG)

prepare:

clean:
	@rm -Rf $(OBJDIR)
	@rm -Rf $(BINDIR)

$(OBJLIB): $(addprefix $(OBJDIR)/, $(OBJECTS)) $(addprefix $(OBJDIR)/, $(CXXOBJS))
	@mkdir -p $(LIBDIR)
	@echo "  LIB $@"
	@$(AR) rcs $@ $(OBJDIR)/*.o

$(OBJPROG): onvifserver.h onvifserver.c $(OBJLIB)
	@mkdir -p $(BINDIR)
	@echo "  BIN $@"
	@$(GCC) -o $@ -D_TEST_ onvifserver.c $(OBJLIB) $(LDFLAGS)

$(OBJDIR)/%.c.o : %.c
	@mkdir -p obj
	@echo "  CC  $<"
	@$(GCC) $(C_FLAGS) $(C_INCLUDES) -c $< -o $@

$(OBJDIR)/%.cpp.o : %.cpp
	@mkdir -p obj
	@echo "  CC  $<"
	@$(GXX) $(C_FLAGS) $(C_INCLUDES) -c $< -o $@
