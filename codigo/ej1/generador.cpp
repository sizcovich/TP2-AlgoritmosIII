#include <vector>
#include <random>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	srand(time(0));
	int cantTrabajos = atoi(argv[1]);
	cout << cantTrabajos << endl;
	for (int i = 1; i <= cantTrabajos; ++i)
	{
		for (int j = 1; j <= i; ++j)
		{
			cout << rand() % 150 << " ";
		}
		cout << endl;
	}
	cout << 0 << endl;
	return 0;
}