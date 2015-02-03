#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

int main()
{
	vector <int> stack;
	string gold;
	char *end;
	int a, l, r;
	
	while(cin >> gold)
	{
		if (gold == "+")
		{
			r = stack.back(); 
			stack.pop_back(); 
			l = stack.back(); 
			stack.pop_back();
			a = l + r;
			stack.push_back(a); 
		}
		else if (gold == "-")
		{
			r = stack.back(); 
			stack.pop_back();
			l = stack.back(); 
			stack.pop_back();
			a = l - r;
			stack.push_back(a); 
		}
		else if (gold == "*")
		{
			r = stack.back(); 
			stack.pop_back(); 
			l = stack.back();
			stack.pop_back();
			a = l * r;
			stack.push_back(a); 
		}
		else if (gold == "/")
		{
			r = stack.back(); 
			stack.pop_back(); 
			l = stack.back();
			stack.pop_back();
			a = l / r;
			stack.push_back(a);
		}
		else if (gold == ".")
		{
			break;
		}
		else
		{
			stack.push_back(strtol(gold.c_str(), &end, 10));
		}
	}
		for ( int i = 0; i < stack.size(); i++)
		{
			cout << stack[i];
		}
	return 0;
}