CC = g++
CFLAGS = -Wall -O --std=c++11
DIR = RNG

all : Exercise1.1 Exercise1.2

Exercise1.1: Exercise1.1.o $(DIR)/random.o $(DIR)/GeneralPurposeLib.o Walker.o Lib.o
	$(CC) $^ -o $@

Exercise1.1.o: Exercise1.1.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

Exercise1.2: Exercise1.2.o $(DIR)/random.o $(DIR)/GeneralPurposeLib.o Walker.o Lib.o 
	$(CC) $^ -o $@

Exercise1.2.o: Exercise1.2.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR)/random.o: $(DIR)/random.cpp $(DIR)/random.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR)/GeneralPurposeLib.o: $(DIR)/GeneralPurposeLib.cc $(DIR)/GeneralPurposeLib.h $(DIR)/random.h 
	$(CC) -c $< -o $@ $(CFLAGS)

Walker.o: Walker.cc Walker.h $(DIR)/random.h $(DIR)/GeneralPurposeLib.h
	$(CC) -c $< -o $@ $(CFLAGS)

Lib.o: Lib.cc Lib.h Walker.h $(DIR)/random.h
	$(CC) -c $< -o $@ $(CFLAGS)


clean:
	rm -f *.o Exercise1.1 Exercise1.2 

