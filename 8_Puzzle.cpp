#include "8_Puzzle.h"

STATUS _8_Puzzle::USER_Set8_Puzzle()
{
	unsigned int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			//printf("Row:%d Column:%d\n'0' represents a void.\n\nEnter a number(0-8). ",i+1,j+1);
			cout << "Row:" << i + 1 << endl << "Column:" << j + 1 << endl << "'0' represents a void." << endl << endl << "Enter a number(0-8). " << endl;
			/*scanf_s("%d",&(this->Element[3*i+j]));*/
			cin >> (this->Element[3 * i + j]);
		}
	}
	return(DONE);
}

void _8_Puzzle::Print8_Puzzle()
{
	unsigned int i;
	for(i=0;i<3;i++)
	{
		if (this->Element[i] != 0)
			cout << "|" << this->Element[i];
		else
			cout << "| ";
	}
	cout<<"|"<<endl<<"-------"<<endl;
	for(i=3;i<6;i++)
	{
		if(this->Element[i]!=0)
			cout << "|" << this->Element[i];
		else
			cout << "| ";
	}
	cout << "|" << endl << "-------" << endl;
	for(i=6;i<9;i++)
	{
		if(this->Element[i]!=0)
			cout << "|" << this->Element[i];
		else
			cout << "| ";
	}
	cout << "| "<<endl;
}

bool _8_Puzzle::operator == (_8_Puzzle& Table)
{
	unsigned int i;
	for (i = 0; i < 9; i++)
	{
		if (this->Element[i] != Table.Element[i])
			return(false);
	}
	return(true);
}

bool _8_Puzzle::operator == (_8_Puzzle const &Table)
{
	unsigned int i;
	for (i = 0; i < 9; i++)
	{
		if (this->Element[i] != Table.Element[i])
			return(false);
	}
	return(true);
}

bool _8_Puzzle::operator != (_8_Puzzle &Table)
{
	return(!(*this == Table));
}

bool _8_Puzzle::operator != (_8_Puzzle const &Table)
{
	return(!(*this == Table));
}

unsigned int _8_Puzzle::FindZeroIn8_Puzzle(_8_Puzzle Puzzle)
{
	unsigned int i;
	for(i=0;i<9;i++)
	{
		if(Puzzle.Element[i]==0)
			return(i+1);
	}
	return(0);
}

STATUS _8_Puzzle::MoveZeroUp()
{
	unsigned int num;
	num=FindZeroIn8_Puzzle(*this);
	if(num>3)
	{
		this->Element[num-1]=this->Element[num-4];
		this->Element[num-4]=0;
		return(DONE);
	}
	else
		return(ERROR);
}

STATUS _8_Puzzle::MoveZeroDown()
{
	unsigned int num;
	num=FindZeroIn8_Puzzle(*this);
	if(num>0&&num<7)
	{
		this->Element[num-1]=this->Element[num+2];
		this->Element[num+2]=0;
		return(DONE);
	}
	else
		return(ERROR);
}
STATUS _8_Puzzle::MoveZeroLeft()
{
	unsigned int num;
	num=FindZeroIn8_Puzzle(*this);
	if(num%3!=1&&num!=0)
	{
		this->Element[num-1]=this->Element[num-2];
		this->Element[num-2]=0;
		return(DONE);
	}
	else
		return(ERROR);
}
STATUS _8_Puzzle::MoveZeroRight()
{
	unsigned int num;
	num=FindZeroIn8_Puzzle(*this);
	if(num%3!=0)
	{
		this->Element[num-1]=this->Element[num];
		this->Element[num]=0;
		return(DONE);
	}
	else
		return(ERROR);
}

unsigned int _8_Puzzle::HeuristicFunction(_8_Puzzle Target)
{
	int i, j,H=0;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (this->Element[i] != 0 && this->Element[i] == Target.Element[j])
				H = H + abs(i / 3 - j / 3) + abs(i % 3 - j % 3);
		}
	}
	return (H);
}

int _8_Puzzle::PuzzleID_1(_8_Puzzle Puzzle)
{
	unsigned int i;
	int PuzzleID=0;
	for (i = 0; i < 9; i++)
		PuzzleID = PuzzleID + Puzzle.Element[i]*pow(9, i);//6053444~381360744
	return(PuzzleID-6053444);
}

int _8_Puzzle::PuzzleID_2(_8_Puzzle Puzzle)
{
	unsigned int i;
	int PuzzleID = 0;
	for (i = 0; i < 9; i++)
		PuzzleID = PuzzleID + Puzzle.Element[i] * pow(10, i);//12345678~876543210
	return(PuzzleID);
}

bool _8_Puzzle::SearchSolution(_8_Puzzle Origin,_8_Puzzle Target, _8_Puzzle_Solution &Solution)
{
	_8_Puzzle PNext;
	queue <_8_Puzzle> open;
	queue <unsigned int>open_p;
	vector <_8_Puzzle> closed;
	vector <unsigned int> closed_p;
	while (open.empty() == false)
		open.pop();
	closed.clear();
	closed_p.clear();
	if (Origin==Target)
	{
		Solution.Solution.push_back(Origin);
		return(true);
	}
	else
	{
		open.push(Origin);
		open_p.push(0);
	}
	while (open.empty() == false)
	{
		_8_Puzzle TestSolution[4];
		int num = 0, i = 0, j = 0, p = 0, TestSolution_p[4];
		closed.push_back(open.front());
		closed_p.push_back(open_p.front());
		num = 0;
		TestSolution[num] = open.front();
		//cout << "Expanding:" << endl;
		//TestSolution[num].Print8_Puzzle();
		if (TestSolution[num].MoveZeroUp() == DONE && (find(closed.begin(), closed.end(), TestSolution[num]) == closed.end()))
		{
			TestSolution_p[num] = 1;
			if (TestSolution[num]==Target)
			{
				Solution.Solution.push_back(Target);
				PNext = open.front();
				break;
			}
			num++;
		}

		TestSolution[num] = open.front();
		if (TestSolution[num].MoveZeroDown() == DONE && (find(closed.begin(), closed.end(), TestSolution[num]) == closed.end()))
		{
			TestSolution_p[num] = 2;
			if (TestSolution[num]==Target)
			{
				Solution.Solution.push_back(Target);
				PNext = open.front();
				break;
			}
			num++;
		}

		TestSolution[num] = open.front();
		if (TestSolution[num].MoveZeroLeft() == DONE && (find(closed.begin(), closed.end(), TestSolution[num])== closed.end()))
		{
			TestSolution_p[num] = 3;
			if (TestSolution[num]==Target)
			{
				Solution.Solution.push_back(Target);
				PNext = open.front();
				break;
			}
			num++;
		}

		TestSolution[num] = open.front();
		if (TestSolution[num].MoveZeroRight() == DONE && (find(closed.begin(), closed.end(), TestSolution[num]) == closed.end()))
		{
			TestSolution_p[num] = 4;
			if (TestSolution[num]==Target)
			{
				Solution.Solution.push_back(Target);
				PNext = open.front();
				break;
			}
			num++;
		}

		for (i = 0; i < (num - 1); i++)
		{
			for (j = 0; j < (num - 1 - i); j++)
			{
				if (TestSolution[j].HeuristicFunction(Target) > TestSolution[j + 1].HeuristicFunction(Target))
				{
					_8_Puzzle Puzzle_temp;
					unsigned int p_temp;
					Puzzle_temp = TestSolution[j + 1];
					TestSolution[j + 1] = TestSolution[j];
					TestSolution[j] = Puzzle_temp;
					p_temp = TestSolution_p[j + 1];
					TestSolution_p[j + 1] = TestSolution_p[j];
					TestSolution_p[j] = p_temp;
				}
			}
		}

		for (i = 0; i < num; i++)
		{
			//TestSolution[i].Print8_Puzzle();
			//unsigned int H=TestSolution[i].HeuristicFunction(Target);
			//cout << H << endl;
			open.push(TestSolution[i]);
			open_p.push(TestSolution_p[i]);
		}
		open.pop();
		open_p.pop();
	}
	if (open.empty() == true)
		return (false);
	else
	{
		while (Origin!=PNext)
		{
			Solution.Solution.push_back(PNext);
			unsigned int i;
			for (i = 0; i < closed.size(); i++)
			{
				if (closed[i]==PNext)
				{
					switch (closed_p[i])
					{
					case 1:
						PNext.MoveZeroDown();
						break;
					case 2:
						PNext.MoveZeroUp();
						break;
					case 3:
						PNext.MoveZeroRight();
						break;
					case 4:
						PNext.MoveZeroLeft();
						break;
					}
				}
			}
		}
		Solution.Solution.push_back(PNext);
		return (true);
	}
}

void _8_Puzzle_Solution::print()
{
	int i;
	for (i = Solution.size() - 1; i >= 0; i--)
	{
		cout << "Step number :" << Solution.size() - i - 1 << endl;
		Solution[i].Print8_Puzzle();
	}
}

int _8_Puzzle_Solution::steps_in_total()
{
	return((this->Solution.size()>0) ? this->Solution.size() - 1 : 0);
}
