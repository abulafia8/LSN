CC = g++
CFLAGS = -Wall -O3 --std=c++11
DIR = RNG

all : Exercise1.1 Exercise1.2 Exercise1.3 Exercise2.1 Exercise3.1

Exercise1.1: Exercise1.1.o $(DIR)/random.o $(DIR)/GeneralPurposeLib.o
	$(CC) $^ -o $@
Exercise1.1.o: Exercise1.1.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
Exercise1.2: Exercise1.2.o $(DIR)/random.o $(DIR)/GeneralPurposeLib.o
	$(CC) $^ -o $@
Exercise1.2.o: Exercise1.2.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
Exercise1.3: Exercise1.3.o $(DIR)/random.o $(DIR)/GeneralPurposeLib.o
	$(CC) $^ -o $@
Exercise1.3.o: Exercise1.3.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
Exercise2.1: Exercise2.1.o $(DIR)/random.o $(DIR)/GeneralPurposeLib.o
	$(CC) $^ -o $@
Exercise2.1.o: Exercise2.1.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
Exercise3.1: Exercise3.1.o $(DIR)/random.o $(DIR)/GeneralPurposeLib.o
	$(CC) $^ -o $@
Exercise3.1.o: Exercise3.1.cpp
	$(CC) -c $< -o $@ $(CFLAGS)


$(DIR)/random.o: $(DIR)/random.cpp $(DIR)/random.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR)/GeneralPurposeLib.o: $(DIR)/GeneralPurposeLib.cc $(DIR)/GeneralPurposeLib.h $(DIR)/random.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o $(DIR)/*.o Exercise1.1 Exercise1.2 Exercise1.3 Exercise2.1 Exercise3.1 

