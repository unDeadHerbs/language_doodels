CXX      = g++
CXXFLAGS = -std=c++1y -Wall -lpthread
SOURCES  = $(wildcard *.cpp)
OBJECTS  = $(SOURCES:.cpp=.o)
EXEC     = $(SOURCES:.cpp=.out)


all: $(EXEC) clean

%.out: %.o
	-$(CXX) $(CXXFLAGS) $< -o $@ $($< -o $@:.out=.o)

%.o: %.cpp
	-$(CXX) $(CXXFLAGS) -c $< -o $@

check-syntax:
	$(CXX) $(CXXFLAGS) ${CHK_SOURCES} #-o /dev/null
# -S-fsyntax-only

clean:
	rm -f $(OBJECTS)
