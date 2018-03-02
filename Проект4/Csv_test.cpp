#include <iostream>
#include "csvparser.h"
#include <fstream>
#include <string>
using namespace std;
int main()
{
	fstream write1;
	write1.open("Csv_test.csv", ios_base::app);
	write1 << endl << "C1"+to_string(5) << ";" << 432 << ";" << 13;
	write1.close();
	write1.open("Csv_test.csv", ios_base::app);
	return 0;
}