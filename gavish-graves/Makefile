CC = g++
CPPFLAGS = -g -Wall -O2
LDFLAGS =

CPX_BASE    = /opt/ibm/ILOG/CPLEX_Studio
CPX_INCDIR  = $(CPX_BASE)/cplex/include
CPX_LIBDIR  = $(CPX_BASE)/cplex/lib/x86-64_linux/static_pic
CPX_LDFLAGS = -lcplex -lm -pthread -ldl

EXE := main.out
SOURCES := $(wildcard *.cpp) $(shell find ../libraries -name "*.cpp")
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))

%.o: %.cpp
	$(CC) $(CPPFLAGS) -I$(CPX_INCDIR) -c $^ -o $@

main: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $(EXE) -L$(CPX_LIBDIR) $(CPX_LDFLAGS)

# -include $(DEPENDS)

clean:
	rm -rf $(OBJECTS) $(DEPENDS) $(EXE)


.PHONY: clean
