# Copyright 2019 SiFive, Inc #
# SPDX-License-Identifier: Apache-2.0 #

PROGRAM ?= empty

$(PROGRAM): $(wildcard *.cpp) $(wildcard *.h) $(wildcard *.S) $(wildcard *.c) $(wildcard *.hpp)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(filter %.cpp %.S,$^) $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f $(PROGRAM) $(PROGRAM).hex
