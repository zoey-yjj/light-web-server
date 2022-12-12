CXX ?= g++

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CXXFLAGS += -g
else
    CXXFLAGS += -O2

endif

server: main.cpp  ./server.cpp 
	$(CXX) -o server  $^ $(CXXFLAGS) 

clean:
	rm  -r server