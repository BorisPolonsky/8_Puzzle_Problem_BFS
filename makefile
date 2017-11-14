exec_file = 8_Puzzle_BFS_Solution
$(exec_file): 8_Puzzle.o main.o
	g++ 8_Puzzle.o main.o -o $(exec_file)
main.o: main.h main.cpp
	g++ -c main.cpp
8_Puzzle.o: 8_Puzzle.h 8_Puzzle.cpp
	g++ -c 8_Puzzle.cpp
