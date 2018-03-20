#include "main.h"

void main()
{
	_8_Puzzle Origin, Target;
	cout << "Set Origin:" << endl;
	Origin.USER_Set8_Puzzle();
	cout << "Set Target:" << endl;
	Target.USER_Set8_Puzzle();
	system("cls");
	cout << "Origin:" << endl;
	Origin.Print8_Puzzle();
	cout << "Target:" << endl;
	Target.Print8_Puzzle();
	cout << "Press anykey to confirm configuration and start searching for solution. " << endl;
	system("pause>nul");
	clock_t t_begin, t_end;
	t_begin = clock();
	vector<_8_Puzzle> Solution;
	Solution = _8_Puzzle::SearchSolution(Origin, Target);
	t_end = clock();
	if (Solution.empty()==false)
	{
		for (int i = 0; i < Solution.size(); i++)
		{
			cout << "Step " << i << ": " << endl;
			Solution[i].Print8_Puzzle();
		}
		cout << Solution.size()-1 << " step(s) in total. " << endl;
	}
	else
		cout << "No Solution." << endl;
	cout << "Total time elapsed: " << endl << (t_end - t_begin) << "ms" << endl;
	system("pause");
}