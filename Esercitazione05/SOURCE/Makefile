CC = g++
CFLAGS = -Wall -O --std=c++11
DIR = RNG

all: Metro

Metro: Metro.o $(DIR)/random.o $(DIR)/GeneralPurposeLib.o Walker.o MetroLib.o
	$(CC) $^ -o $@
	
Metro.o: Metro.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR)/random.o: $(DIR)/random.cpp $(DIR)/random.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR)/GeneralPurposeLib.o: $(DIR)/GeneralPurposeLib.cc $(DIR)/GeneralPurposeLib.h $(DIR)/random.h
	$(CC) -c $< -o $@ $(CFLAGS)

Walker.o: Walker.cc Walker.h $(DIR)/random.h $(DIR)/GeneralPurposeLib.h MetroLib.h
	$(CC) -c $< -o $@ $(CFLAGS)

MetroLib.o: MetroLib.cc MetroLib.h Walker.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o Metro $(DIR)/*.o