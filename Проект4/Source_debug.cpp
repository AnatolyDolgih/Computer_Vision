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
	

	// ���� ��� ������
	write1.open("results221.txt");

	// ���� ��� ������
	ifstream read;

	// �������� ������ ����� FDDB-fold-0i.txt, ������� ���������
	string str1;

	// �������� ������ ��������, ��������� �� �����
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