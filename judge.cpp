#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	int input;
	vector<int> numbers(101, 0);
	int size;
	cin >> size;
	for (int i = 0; i < size; i++)
	{
		cin >> input;
		if (input == -1)
			continue;
		numbers[input]++;
	}
	int index = 0;
	int max = 0;
	for (int i = 0; i < numbers.size(); i++)
	{
		if (numbers[i] > max)
		{
			max = numbers[i];
			index = i;
		}
	}
	cout << index << endl;
}