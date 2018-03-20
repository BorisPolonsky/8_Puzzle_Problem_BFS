#include "8_Puzzle.h"

_8_Puzzle::_8_Puzzle()
{
	unsigned int i;
	for (i = 0; i < 9; i++)
		Element[i] = i;
}

_8_Puzzle::_8_Puzzle(initializer_list<unsigned int> flatten_array)
{
	if (flatten_array.size() != 9)
	{
		throw(flatten_array);
	}
	unsigned int *p = this->Element;
	for (auto q = flatten_array.begin(); q != flatten_array.end(); p++, q++)
	{
		*p = *q;
	}
}

_8_Puzzle::STATUS _8_Puzzle::USER_Set8_Puzzle()
{
	unsigned int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			cout << "Row:" << i + 1 << endl << "Column:" << j + 1 << endl << "'0' represents a void." << endl << endl << "Enter a number(0-8). " << endl;
			cin >> (this->Element[3 * i + j]);
		}
	}
	return(_8_Puzzle::DONE);
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

_8_Puzzle::STATUS _8_Puzzle::MoveZeroUp()
{
	unsigned int num;
	num=FindZeroIn8_Puzzle(*this);
	if(num>3)
	{
		this->Element[num-1]=this->Element[num-4];
		this->Element[num-4]=0;
		return(_8_Puzzle::DONE);
	}
	else
		return(_8_Puzzle::ERROR);
}

_8_Puzzle::STATUS _8_Puzzle::MoveZeroDown()
{
	unsigned int num;
	num=FindZeroIn8_Puzzle(*this);
	if(num>0&&num<7)
	{
		this->Element[num-1]=this->Element[num+2];
		this->Element[num+2]=0;
		return(_8_Puzzle::DONE);
	}
	else
		return(_8_Puzzle::ERROR);
}
_8_Puzzle::STATUS _8_Puzzle::MoveZeroLeft()
{
	unsigned int num;
	num=FindZeroIn8_Puzzle(*this);
	if(num%3!=1&&num!=0)
	{
		this->Element[num-1]=this->Element[num-2];
		this->Element[num-2]=0;
		return(_8_Puzzle::DONE);
	}
	else
		return(_8_Puzzle::ERROR);
}
_8_Puzzle::STATUS _8_Puzzle::MoveZeroRight()
{
	unsigned int num;
	num=FindZeroIn8_Puzzle(*this);
	if(num%3!=0)
	{
		this->Element[num-1]=this->Element[num];
		this->Element[num]=0;
		return(_8_Puzzle::DONE);
	}
	else
		return(_8_Puzzle::ERROR);
}

_8_Puzzle::STATUS _8_Puzzle::Move(_8_Puzzle::MOVE param)
{
	switch (param)
	{
	case 0:
		return(this->MoveZeroUp());
	case 1:
		return(this->MoveZeroDown());
	case 2:
		return(this->MoveZeroLeft());
	case 3:
		return(this->MoveZeroRight());
	default:
		return _8_Puzzle::ERROR;
	}
}
int _8_Puzzle::Encode(_8_Puzzle &Puzzle)
{
	unsigned int i;
	int PuzzleID = 0;
	int order = 1;
	for (i = 0; i < 9; i++)
	{
		PuzzleID = PuzzleID + Puzzle.Element[i] * order;
		order *= 10;
	}
	return(PuzzleID);//12345678~876543210
}

_8_Puzzle _8_Puzzle::Decode(SERIAL serial)
{
	_8_Puzzle decode;
	for (int i = 0; i < 9; i++)
	{
		decode.Element[i] = serial % 10;
		serial = serial / 10;
	}
	return(decode);
}

vector<_8_Puzzle> _8_Puzzle::SearchSolution(_8_Puzzle &Origin, _8_Puzzle &Target)
{
	vector<_8_Puzzle> Solution;
	if (Origin == Target)
	{
		Solution.push_back(Target);
		return(Solution);
	}
	queue <int> open;
	unordered_map<SERIAL,SERIAL> closed;
	const _8_Puzzle::SERIAL TargetSerial=Encode(Target);
	open.push(Encode(Origin));
	closed[Encode(Origin)] = 0;//closed[NodeSerial]=[ParentNodeSerial]
	bool SolutionExistence = false;
	while (SolutionExistence == false && open.empty() == false)
	{
		_8_Puzzle Node = Decode(open.front()), NewNode;
		for (int move_i = 0; move_i < 4; move_i++)
		{
			NewNode = Node;
			if (NewNode.Move(move_i) == _8_Puzzle::DONE)
			{
				int NewSerial = Encode(NewNode);
				if (closed.find(NewSerial) == closed.end())
				{
					closed[NewSerial] = open.front();
					open.push(NewSerial);
				}
				if (NewNode == Target)
				{
					SolutionExistence = true;
					break;
				}
			}
		}
		open.pop();
	}
	if (SolutionExistence == false)
		return Solution;
	_8_Puzzle::SERIAL SolutionTrajectory = TargetSerial;
	while (SolutionTrajectory!=0)
	{
		Solution.insert(Solution.begin(), Decode(SolutionTrajectory));
		SolutionTrajectory = closed[SolutionTrajectory];
	}
	return(Solution);
}
