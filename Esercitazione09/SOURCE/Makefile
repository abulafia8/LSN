CC = g++
CFLAGS = -Wall -O3 --std=c++11
LIBS = -larmadillo -llapack
DIR = RNG

all: Main

Main: Main.o Trip.o GenLib.o $(DIR)/random.o $(DIR)/GeneralPurposeLib.o Population.o
	$(CC) $^ -o $@ $(LIBS)

Main.o: Main.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

Trip.o: Trip.cc Trip.h 
	$(CC) -c $< -o $@ $(CFLAGS)

GenLib.o: GenLib.cc GenLib.h $(DIR)/random.h $(DIR)/GeneralPurposeLib.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR)/random.o: $(DIR)/random.cpp $(DIR)/random.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR)/GeneralPurposeLib.o: $(DIR)/GeneralPurposeLib.cc
	$(CC) -c $< -o $@ $(CFLAGS)
	
Population.o: Population.cc Population.h Trip.h GenLib.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o $(DIR)/*.o Main
