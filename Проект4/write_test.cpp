#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
	ifstream read1;
	ofstream write1;
	read1.open("FDDB-fold-01-ellipseList.txt");
	write1.open("test_write.txt");
	string str;
	while(!read1.eof())
	{
		read1 >> str;
		write1 << str << endl;

	}
	setlocale(LC_ALL, "Russian");
	system("pause");
	return 0;
}