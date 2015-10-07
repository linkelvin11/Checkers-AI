checkers.exe: board.o
	g++ -o checkers.exe board.o

board.o: board.cpp board.h
	g++ -c -std=c++11 board.cpp -o board.o

debug: board.o
	g++ -g -o checkersDebug.exe board.o

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups