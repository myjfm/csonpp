# Fallback to gcc when $CC is not in $PATH.
CXX							:= $(shell sh -c 'type $(CXX) >/dev/null 2>/dev/null && echo $(CXX) || echo g++')
OPTIMIZATION		?= -O2
WARNINGS				= -Wall -W -Wwrite-strings
DEBUG						?= -g -ggdb
REAL_CPPFLAGS		= $(OPTIMIZATION) -fPIC \
									-I../../../3rdparty/gmock/include \
									-I../../../3rdparty/gmock/gtest/include \
									-I../../ \
									$(CPPFLAGS) $(WARNINGS) $(DEBUG) $(ARCH)
REAL_LDFLAGS		= -lpthread $(LDFLAGS) $(ARCH)

export OUTPUT_PATH	= output

TEST						= $(OUTPUT_PATH)/test
OBJS						= $(OUTPUT_PATH)/TestMain.o \
									$(OUTPUT_PATH)/CsonppTest.o

GMOCK_LIB				= ../../../3rdparty/gmock/output/libgmock.a
CSONPP_LIB			= ../../../output/libcsonpp.a

.PHONY : everything clean realclean all

everything : others $(TEST)

all : clean everything

clean : 
	rm -rf $(OBJS)

realclean : 
	rm -rf $(OBJS)
	rm -rf $(TEST)
	rm -rf $(SH_LIB_NAME)

$(TEST) : $(OBJS)
	$(CXX) $(REAL_LDFLAGS) -o $(TEST) $(OBJS) $(GMOCK_LIB) $(CSONPP_LIB)

others : 
	mkdir -p $(OUTPUT_PATH)

$(OUTPUT_PATH)/TestMain.o : ../TestMain.cc
	$(CXX) --std=c++11 $(REAL_CPPFLAGS) -c -o $@ $<

$(OUTPUT_PATH)/CsonppTest.o : ../CsonppTest.cc
	$(CXX) --std=c++11 $(REAL_CPPFLAGS) -c -o $@ $<

