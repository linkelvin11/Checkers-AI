checkers.exe: board.o move.o player.o game.cpp game.h
	g++ -std=c++11 -o checkers.exe game.cpp board.o move.o player.o

board.o: board.cpp board.h
	g++ -c -std=c++11 board.cpp -o board.o

move.o: move.cpp move.h
	g++ -c -std=c++11 move.cpp -o move.o

player.o: player.cpp player.h
	g++ -c -std=c++11 player.cpp -o player.o

debug: board.o move.o player.o game.cpp game.h
	g++ -g -std=c++11 -o DebugCheckers.exe game.cpp move.cpp board.cpp player.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups