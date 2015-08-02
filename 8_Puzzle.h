#ifndef __8_Puzzle_H
#define __8_Puzzle_H

using namespace std;

#define EQ 0
#define UNEQ !EQ
#define ERROR 0
#define DONE 1

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <math.h>


typedef unsigned int STATUS;

class _8_Puzzle_Solution;

class _8_Puzzle
{
public:
	_8_Puzzle()
	{
		unsigned int i;
		for (i = 0; i < 9; i++)
			Element[i] = i;
	}
	STATUS USER_Set8_Puzzle();
	void Print8_Puzzle();
	static bool SearchSolution(_8_Puzzle,_8_Puzzle, _8_Puzzle_Solution&);
	friend bool operator ==(_8_Puzzle &,_8_Puzzle &);
	friend bool operator ==(_8_Puzzle &, _8_Puzzle const &);
	friend bool operator !=(_8_Puzzle &, _8_Puzzle &);
	friend bool operator !=(_8_Puzzle &, _8_Puzzle const &);
	
private:
	unsigned int Element[9];//Element[]>=0&&Element[]<=8
	unsigned int FindZeroIn8_Puzzle(_8_Puzzle);
	STATUS MoveZeroUp();
	STATUS MoveZeroDown();
	STATUS MoveZeroLeft();
	STATUS MoveZeroRight();
	unsigned int HeuristicFunction(_8_Puzzle);
	int PuzzleID_1(_8_Puzzle);
	int PuzzleID_2(_8_Puzzle);
};

class _8_Puzzle_Solution
{
public:
	_8_Puzzle_Solution()
	{
		Solution.clear();
	}
	void print();
	int steps_in_total();
private:
	vector <_8_Puzzle> Solution;
	friend _8_Puzzle;
};




#endif