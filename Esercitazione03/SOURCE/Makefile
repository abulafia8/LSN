CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3
INCLUDES = -I./RNG
#executables
EXE1 = CallPutDirect
EXE2 = CallPutWalk

all: $(EXE1) $(EXE2)

$(EXE1): CallPutDirect.o LibPricing.o WalkerSpot.o RNG/random.o RNG/GeneralPurposeLib.o
	$(CXX) $(CXXFLAGS) -o $(EXE1) CallPutDirect.o LibPricing.o WalkerSpot.o RNG/random.o RNG/GeneralPurposeLib.o

$(EXE2): CallPutWalk.o LibPricing.o WalkerSpot.o RNG/random.o RNG/GeneralPurposeLib.o
	$(CXX) $(CXXFLAGS) -o $(EXE2) CallPutWalk.o LibPricing.o WalkerSpot.o RNG/random.o RNG/GeneralPurposeLib.o

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o CallPutDirect CallPutWalk RNG/*.o
#	rm -rf ../OUTPUT/*.dat