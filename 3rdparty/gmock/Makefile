LIB_NAME			= libgmock

# Fallback to gcc when $CC is not in $PATH.
CXX					:= $(shell sh -c 'type $(CXX) >/dev/null 2>/dev/null && echo $(CXX) || echo g++')
OPTIMIZATION		?= -O2
WARNINGS			= -Wall -W -Wwrite-strings
DEBUG				?= -g -ggdb
REAL_CPPFLAGS		= $(OPTIMIZATION) -fPIC \
					  -I./include -I./gtest/include -I. -I./gtest \
					  $(CPPFLAGS) $(WARNINGS) $(DEBUG) $(ARCH)
REAL_LDFLAGS		= $(LDFLAGS) $(ARCH)

export OUTPUT_PATH	= output

ST_LIB_SUFFIX		= a
ST_LIB_NAME			= $(OUTPUT_PATH)/$(LIB_NAME).$(ST_LIB_SUFFIX)
ST_LIB_MAKE_CMD		= ar rcs $(ST_LIB_NAME)

OBJS				= $(OUTPUT_PATH)/gmock-all.o \
					  $(OUTPUT_PATH)/gtest-all.o

.PHONY : everything clean realclean all

everything : others $(ST_LIB_NAME) $(SH_LIB_NAME)

all : clean everything

clean : 
	rm -rf $(OBJS)

realclean : 
	rm -rf $(OBJS)
	rm -rf $(ST_LIB_NAME)

static : others $(ST_LIB_NAME)

$(ST_LIB_NAME) : $(OBJS)
	$(ST_LIB_MAKE_CMD) $(OBJS)

others : 
	mkdir -p $(OUTPUT_PATH)

$(OUTPUT_PATH)/gmock-all.o : src/gmock-all.cc
	$(CXX) $(REAL_CPPFLAGS) -c -o $@ $<

$(OUTPUT_PATH)/gtest-all.o : gtest/src/gtest-all.cc
	$(CXX) $(REAL_CPPFLAGS) -c -o $@ $<

