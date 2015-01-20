#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	ifstream wrong;
	ofstream right;
	wrong.open(argv[1]);
	if (wrong.fail())
	{
		cout << "Unable to open " << argv[1] << endl;
		return 1;
	}
	right.open("output.txt");
	if (right.fail())
	{
		cout << "Unable to open " << "output.txt" << endl;
		return 1;
	}
	right << "x\tx^2\tCurrent Sum" << endl;
	right << "=\t===\t===========" << endl;
	int num, sum = 0;
	while (wrong >> num)
	{
		right << num << "\t" << num*num << "\t" << (sum += num) << endl;
	}
	wrong.close();
	right.close();
	
	return 0;
}