ServerSrc:=$(wildcard ./src/*.cpp)
ServerObj:=$(patsubst %.cpp, %.o, $(ServerSrc))
ServerElf:= ./bin/server.out

LIBS:= -lpthread -llog4cpp -ljson
CXX:=g++
CXXFLAGS:= -Wall -std=c++11 $(LIBS)
$(ServerElf) $(ClientElf):$(ServerObj) $(ClientObj)
	$(CXX) $(ServerObj) -o $(ServerElf) $(CXXFLAGS)

.PHONY:clean
clean:
	rm -rf $(ServerElf)
	rm -rf $(ServerObj)
