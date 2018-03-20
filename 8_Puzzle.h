#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <math.h>
#include <initializer_list>
using namespace std;

class _8_Puzzle_Solution;

class _8_Puzzle
{
public:
	typedef unsigned int STATUS;
	typedef unsigned int MOVE;
	typedef int SERIAL;
	static const STATUS ERROR = 0, DONE = 1;
	static const MOVE UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3;
	_8_Puzzle();
	_8_Puzzle(initializer_list<unsigned int>);
	STATUS USER_Set8_Puzzle();
	void Print8_Puzzle();
	static vector<_8_Puzzle> SearchSolution(_8_Puzzle&,_8_Puzzle&);
	bool operator ==(_8_Puzzle &);
	bool operator ==(_8_Puzzle const &);
	bool operator !=(_8_Puzzle &);
	bool operator !=(_8_Puzzle const &);
	STATUS MoveZeroUp();
	STATUS MoveZeroDown();
	STATUS MoveZeroLeft();
	STATUS MoveZeroRight();
	STATUS Move(MOVE);
	static SERIAL Encode(_8_Puzzle&);
	static _8_Puzzle Decode(SERIAL);
private:
	unsigned int Element[9];//Element[]>=0&&Element[]<=8
	unsigned int FindZeroIn8_Puzzle(_8_Puzzle);
	
	
};
