CC = g++
CFLAGS = -Wall -O3 --std=c++11
DIR = RNG

all: ImpSamp

ImpSamp: ImpSamp.o $(DIR)/random.o $(DIR)/GeneralPurposeLib.o LibIntegration.o Distribution.o
	$(CC) $^ -o $@

ImpSamp.o: ImpSamp.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR)/random.o: $(DIR)/random.cc $(DIR)/random.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR)/GeneralPurposeLib.o: $(DIR)/GeneralPurposeLib.cc $(DIR)/GeneralPurposeLib.h $(DIR)/random.h
	$(CC) -c $< -o $@ $(CFLAGS)

LibIntegration.o: LibIntegration.cc LibIntegration.h $(DIR)/random.h $(DIR)/GeneralPurposeLib.h Distribution.h
	$(CC) -c $< -o $@ $(CFLAGS)

Distribution.o: Distribution.cc Distribution.h $(DIR)/random.h
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o ImpSamp $(DIR)/*.o