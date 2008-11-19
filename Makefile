#!/bin/make

# The prefix of your PHP installation. Leave it blank for auto-detection.
PHP_ROOT=

# System config
CXX=g++
LD=g++
CPPFLAGS=
CXXFLAGS=
LDFLAGS=

# Objects to be built by default
TARGETS=m001.so m002.so m003.so m004.so m005.so m006.so m007.so m008.so

# Check if we system-wide php-config is available, or should we stay compatible
# with initial makefile
PHP_CONFIG=$(shell $(if $(PHP_ROOT),PATH="$(PHP_ROOT)/bin:$$PATH",) which 2>/dev/null php-config)
ifeq ($(PHP_CONFIG),)
$(error Could not find PHP, make sure you have php-config in PATH!)
endif

# Find out some stuff
PHP_INCLUDES=$(shell $(PHP_CONFIG) --includes)
PHP_LDFLAGS=$(shell $(PHP_CONFIG) --ldflags)

# Initialize variables
CPPFLAGS+=-I. $(PHP_INCLUDES)
CXXFLAGS+=-g -pipe -Wall

# PIC should be ignored if the arch doesn't need it. 
CXXFLAGS+=-fPIC -DPIC

# This one is also to stay compatible with initial makefile
ifneq ($(wildcard $(HOME)/Sources/boost_1_35_0),)
CPPFLAGS+=-I$(HOME)/Sources/boost_1_35_0
endif

# Darwin's way of building shared libs
LDFLAGS+=$(if $(shell uname | grep "Darwin"),  -bundle -undefined dynamic_lookup, -shared)

all: $(TARGETS)

m%.o: m%.cpp
	$(CXX) -DCOMPILE_DL_M$* $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

m%.so: m%.o
	$(LD) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm -f *.so

.PHONY: clean all
.SUFFIXES: .o .cpp .so

