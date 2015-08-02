#include "Main.h"

void main()
{
	_8_Puzzle Origin, Target;
	_8_Puzzle_Solution solution;
	cout << "Set Origin:" << endl;
	Origin.USER_Set8_Puzzle();
	cout << "Set Target:" << endl;
	Target.USER_Set8_Puzzle();
	cout << "Origin:" << endl;
	Origin.Print8_Puzzle();
	cout << "Target:" << endl;
	Target.Print8_Puzzle();
	cout << "Press anykey to confirm configuration and start searching solution. " << endl;
	system("pause>nul");
	clock_t t_begin, t_end;
	t_begin = clock();
	if (_8_Puzzle::SearchSolution(Origin, Target, solution) == true)
	{
		solution.print();
		cout << solution.steps_in_total() << " step(s) in total. " << endl;
	}
	else
		cout << "No Solution." << endl;
	t_end = clock();
	cout << "Total time elapsed: " << endl << (t_end - t_begin)<<"ms"<<endl;
	system("pause");
}