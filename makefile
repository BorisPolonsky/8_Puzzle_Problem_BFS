exec_file = 8_Puzzle_BFS_Solution
$(exec_file): 8_Puzzle.o main.o
	g++ 8_Puzzle.o main.o -std=c++11 -o $(exec_file)
main.o: main.h main.cpp
	g++ -c main.cpp -std=c++11
8_Puzzle.o: 8_Puzzle.h 8_Puzzle.cpp
	g++ -c 8_Puzzle.cpp -std=c++11
