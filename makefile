# Chess
# makefile

# ********************************************************

OBJS	= main.o chess.o
CC	= g++ -g -Wall -pedantic -std=c++11
DEPS	= chess.o

all: chess++

chess++: $(OBJS) $(DEPS)
	$(CC) -o chess++ $(OBJS)

main.o: main.cpp $(DEPS)
	$(CC) -c main.cpp

chess.o: chess.cpp
	$(CC) -c chess.cpp

# -----
# clean by removing object files

clean:
	rm $(OBJS)