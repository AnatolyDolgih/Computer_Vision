#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;
ofstream write1;
int main(int argc, const char** argv)
{
	setlocale(LC_ALL, "Russian");
	

	// файл для записи
	write1.open("results221.txt");

	// файл для чтения
	ifstream read;

	// хранение адреса файла FDDB-fold-0i.txt, который открываем
	string str1;

	// хранение адреса картинки, считанной из файла
	string str2;
	
	for (int i = 1; i < 2; i++)
	{
		str1 = "FDDB-fold-0" + to_string(i) + ".txt";
		read.open(str1);
		
		while (read.eof() == 0)
		{
			read >> str2;
			cout << str2 << endl;
		}
		read.close();
	}
	write1.close();
	system("pause");
	return 0;
}