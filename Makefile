#!/bin/make

# The prefix of your PHP installation. Leave it blank for auto-detection.
PHP_ROOT=

# System config
CXX=g++
LD=g++
CPPFLAGS=
CXXFLAGS=
LDFLAGS=

# Check if we system-wide php-config is available, or should we stay compatible
# with initial makefile
PHP_CONFIG=$(shell $(if $(PHP_ROOT),PATH="$(PHP_ROOT)/bin:$$PATH",) which 2>/dev/null php-config)
PHP_BINARY=$(shell $(if $(PHP_ROOT),PATH="$(PHP_ROOT)/bin:$$PATH",) which 2>/dev/null php)
PHP_TEST=$(shell find $(shell $(PHP_CONFIG) --prefix) -name run-tests.php)
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

all: $(patsubst %.cpp, %.so, $(wildcard tests/*.cpp))

tests/m%.o: tests/m%.cpp
	$(CXX) -DCOMPILE_DL_M$* $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

tests/m%.so: tests/m%.o
	$(LD) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

# invoke PHP for each target (may not work if your php installation is too "deep")
test: $(TARGETS)
	TEST_PHP_EXECUTABLE="$(PHP_BINARY)" $(PHP_BINARY) $(PHP_TEST) -n -d extension_dir=`pwd`/tests tests

clean:
	rm -f tests/*.o
	rm -f tests/*.so

.PHONY: clean all test
.SUFFIXES: .o .cpp .so

