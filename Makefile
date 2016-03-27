CXX      = g++
CXXFLAGS = -std=c++1y -Wall -lpthread
SOURCES  = $(wildcard *.cpp)
HPPS        = $(wildcard *.hpp)
OBJECTS     = $(HPPS:.hpp=.o)
EXEC     = apl

all: $(EXEC) clean tags

$(EXEC): $(OBJECTS) $(EXEC).o
	-$(CXX) $(CXXFLAGS) -o $(EXEC) $(EXEC).o $(OBJECTS)

%.o: %.cpp
	-$(CXX) $(CXXFLAGS) -c $< -o $@

check-syntax:
	$(CXX) $(CXXFLAGS) ${CHK_SOURCES} -o /dev/null
# -S-fsyntax-only

tags:
	rm -f TAGS
	ls|grep "pp$$"|xargs etags -a

clean:
	rm -f $(OBJECTS) $(EXEC).o
