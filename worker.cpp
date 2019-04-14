#include <iostream>
#include <vector>
#include <fstream>
#include "StringTokenizer.h"

using namespace std;


int main()
{
	string path;
	string sensor;
	getline(cin, path);
	cin >> sensor;
	ifstream ifs(path.c_str());
	string line;
	while (getline(ifs, line))
	{
		StringTokenizer tokens(line, " ");
		if (tokens[0] == sensor)
		{
			cout << tokens[1] << endl;
			return 0;
		}
	}
	cout << -2 << endl;

}