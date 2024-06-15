CC = mpic++
CFLAGS = -Wall -O3 --std=c++11
LIBS = -larmadillo -llapack
DIR = GA/RNG

all: Migrazioni	

Migrazioni : Migrazioni.o GA/Trip.o GA/GenLib.o $(DIR)/random.o $(DIR)/GeneralPurposeLib.o GA/Population.o
	$(CC) $^ -o $@ $(LIBS)

Migrazioni.o: Migrazioni.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

Trip.o: GA/Trip.cc GA/Trip.h 
	$(CC) -c $< -o $@ $(CFLAGS)

GenLib.o: GA/GenLib.cc GA/GenLib.h $(DIR)/random.h $(DIR)/GeneralPurposeLib.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR)/random.o: $(DIR)/random.cpp $(DIR)/random.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR)/GeneralPurposeLib.o: $(DIR)/GeneralPurposeLib.cc
	$(CC) -c $< -o $@ $(CFLAGS)
	
Population.o: GA/Population.cc GA/Population.h GA/Trip.h GA/GenLib.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o GA/*.o $(DIR)/*.o Migrazioni 
