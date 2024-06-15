CC = g++
CFLAGS = -Wall -O3 --std=c++11
DIR = RNG

all: DiscrRW ContRW

DiscrRW: DiscrRW.o $(DIR)/random.o $(DIR)/GeneralPurposeLib.o WalkLib.o Walker.o
	$(CC) $^ -o $@

DiscrRW.o: DiscrRW.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

ContRW: ContRW.o $(DIR)/random.o $(DIR)/GeneralPurposeLib.o WalkLib.o Walker.o
	$(CC) $^ -o $@

ContRW.o: ContRW.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR)/random.o: $(DIR)/random.cc $(DIR)/random.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR)/GeneralPurposeLib.o: $(DIR)/GeneralPurposeLib.cc $(DIR)/GeneralPurposeLib.h $(DIR)/random.h
	$(CC) -c $< -o $@ $(CFLAGS)

WalkLib.o: WalkLib.cc WalkLib.h $(DIR)/random.h $(DIR)/GeneralPurposeLib.h Walker.h
	$(CC) -c $< -o $@ $(CFLAGS)

Walker.o: Walker.cc Walker.h $(DIR)/random.h $(DIR)/GeneralPurposeLib.h 
	$(CC) -c $< -o $@ $(CFLAGS)


.PHONY: clean

clean:
	rm -f *.o DiscrRW ContRW $(DIR)/*.o