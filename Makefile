LIB_NAME			= libcsonpp

VER_MAJOR			= 0
VER_MINOR			= 1

# Fallback to gcc when $CC is not in $PATH.
CXX					:= $(shell sh -c 'type $(CXX) >/dev/null 2>/dev/null && echo $(CXX) || echo g++')
OPTIMIZATION		?= -O2
WARNINGS			= -Wall -W -Wwrite-strings
DEBUG				?= -g -ggdb
REAL_CPPFLAGS		= $(OPTIMIZATION) -fPIC $(CPPFLAGS) $(WARNINGS) $(DEBUG) $(ARCH)
REAL_LDFLAGS		= $(LDFLAGS) $(ARCH)

export OUTPUT_PATH	= output
OBJ_DIR				= $(OUTPUT_PATH)

SH_LIB_SUFFIX		= so
ST_LIB_SUFFIX		= a
SH_LIB_MINOR_NAME	= $(OUTPUT_PATH)/$(LIB_NAME).$(SH_LIB_SUFFIX).$(VER_MAJOR).$(VER_MINOR)
SH_LIB_MAJOR_NAME	= $(OUTPUT_PATH)/$(LIB_NAME).$(SH_LIB_SUFFIX).$(VER_MAJOR)
SH_LIB_NAME			= $(OUTPUT_PATH)/$(LIB_NAME).$(SH_LIB_SUFFIX)
SH_LIB_MAKE_CMD		= $(CXX) -shared -D_REENTRANT -Wl,-soname,$(SH_LIB_MINOR_NAME) -o $(SH_LIB_NAME) $(LDFLAGS)

ST_LIB_NAME			= $(OUTPUT_PATH)/$(LIB_NAME).$(ST_LIB_SUFFIX)
ST_LIB_MAKE_CMD		= ar rcs $(ST_LIB_NAME)

OBJS				= $(OUTPUT_PATH)/csonpp_impl.o

.PHONY : everything clean realclean all

everything : others $(ST_LIB_NAME) $(SH_LIB_NAME)

all : clean everything

clean : 
	rm -rf $(OBJS)

realclean : 
	rm -rf $(OBJS)
	rm -rf $(ST_LIB_NAME)
	rm -rf $(SH_LIB_NAME)

shared : others $(SH_LIB_NAME)

static : others $(ST_LIB_NAME)

$(ST_LIB_NAME) : $(OBJS)
	$(ST_LIB_MAKE_CMD) $(OBJS)

$(SH_LIB_NAME) : $(OBJS)
	$(SH_LIB_MAKE_CMD) $(OBJS)

others : 
	mkdir -p $(OUTPUT_PATH)

$(OUTPUT_PATH)/csonpp_impl.o : src/private/csonpp_impl.cc
	$(CXX) --std=c++11 $(REAL_CPPFLAGS) -c -o $@ $<

