CROSS_COMPILE ?=
GCC ?= $(CROSS_COMPILE)gcc
GXX ?= $(CROSS_COMPILE)g++

C_FLAGS := -Wall -Wno-unused-but-set-variable -Os -fPIC -DPIC -ffunction-sections -DWITH_OPENSSL

LDFLAGS := -lpthread -lws2_32 -lcrypto -lssl

C_INCLUDES :=

PROGS = onvif-server

OMX_COMP_C_SRCS=$(wildcard ./*.c)
OMX_COMP_C_SRCS_NO_DIR=$(notdir $(OMX_COMP_C_SRCS))
OBJECTS=$(patsubst %.c, %.c.o, $(OMX_COMP_C_SRCS_NO_DIR))

OMX_COMP_CPP_SRCS=$(wildcard ./*.cpp)
OMX_COMP_CPP_SRCS_NO_DIR=$(notdir $(OMX_COMP_CPP_SRCS))
CXXOBJS=$(patsubst %.cpp, %.cpp.o, $(OMX_COMP_CPP_SRCS_NO_DIR))

OBJDIR ?= $(shell pwd)/obj
BINDIR ?= $(shell pwd)/bin
INCDIR ?= $(shell pwd)/inc

OBJPROG = $(addprefix $(OBJDIR)/, $(PROGS))

.PHONY: clean prepare PROGS

all: prepare $(OBJPROG)

prepare:

clean:
	@rm -Rf $(OBJDIR)
	@rm -Rf $(BINDIR)

$(OBJPROG): $(addprefix $(OBJDIR)/, $(OBJECTS)) $(addprefix $(OBJDIR)/, $(CXXOBJS))
	@mkdir -p $(BINDIR)
	@echo "  BIN $@"
	$(GCC) -o $@ $(addprefix $(OBJDIR)/, $(OBJECTS)) $(addprefix $(OBJDIR)/, $(CXXOBJS)) $(LDFLAGS)
	@echo ""
	mv -f ${OBJDIR}/$(PROGS) ${BINDIR}
	
$(OBJDIR)/%.c.o : %.c
	@mkdir -p obj
	@echo "  CC  $<"
	$(GCC) $(C_FLAGS) $(C_INCLUDES) -c $< -o $@

$(OBJDIR)/%.cpp.o : %.cpp
	@mkdir -p obj
	@echo "  CC  $<"
	@$(GXX) $(C_FLAGS) $(C_INCLUDES) -c $< -o $@
