CXX=g++
LD=g++
PHP_HOME=$(HOME)/opt/php-5.2
BOOST_HOME=$(HOME)/Sources/boost_1_35_0
PHP_CONFIG=$(PHP_HOME)/bin/php-config
PHP_INCLUDES=$(shell $(PHP_CONFIG) --includes)
BOOST_INCLUDES=-I$(BOOST_HOME)
CPPFLAGS=-I. $(PHP_INCLUDES) $(BOOST_INCLUDES)
CXXFLAGS=-g
LDFLAGS:=$(if $(shell uname | grep "Darwin"),  -bundle -undefined dynamic_lookup, -shared)

all: m001.so m002.so m003.so m004.so m005.so m006.so m007.so m008.so

m001.o: m001.cpp
	$(CXX) -DCOMPILE_DL_M001 $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

m001.so: m001.o
	$(LD) $(LDFLAGS) -o $@ $^

m002.o: m002.cpp
	$(CXX) -DCOMPILE_DL_M002 $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

m002.so: m002.o
	$(LD) $(LDFLAGS) -o $@ $^

m003.o: m003.cpp
	$(CXX) -DCOMPILE_DL_M003 $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

m003.so: m003.o
	$(LD) $(LDFLAGS) -o $@ $^

m004.o: m004.cpp
	$(CXX) -DCOMPILE_DL_M004 $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

m004.so: m004.o
	$(LD) $(LDFLAGS) -o $@ $^

m005.o: m005.cpp
	$(CXX) -DCOMPILE_DL_M005 $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

m005.so: m005.o
	$(LD) $(LDFLAGS) -o $@ $^

m006.o: m006.cpp
	$(CXX) -DCOMPILE_DL_M006 $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

m006.so: m006.o
	$(LD) $(LDFLAGS) -o $@ $^

m007.o: m007.cpp
	$(CXX) -DCOMPILE_DL_M007 $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

m007.so: m007.o
	$(LD) $(LDFLAGS) -o $@ $^

m008.o: m008.cpp
	$(CXX) -DCOMPILE_DL_M008 $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

m008.so: m008.o
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm -f *.so

.PHONY: clean all
.SUFFIXES: .o .cpp .so
