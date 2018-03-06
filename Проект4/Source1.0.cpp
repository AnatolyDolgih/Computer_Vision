#include <ctime>
#include <iostream>
#include "Source0.4_efficiency.cpp"
#include "Source0.3_%_area.cpp"
#include "Source0.2_write_coord_faces.cpp"
#include <fstream>
using namespace std;
const int 
num_of_files = 1, //кол-во файлов для подсчета от 1 до 10;
num_of_steps = 1, // кол-во шагов
num_of_neigh = 1, // кол-во соседей
area = 49; // площадь пересечения в %, больше которой считать TP++
int main()
{
	fstream results_of_find;
	double step[num_of_steps] = { 1.2 };
	int neigh[num_of_neigh] = { 2 };
	//входные параметры
	const char* ch[1];
	ch[0] = "C:/Users/Denis D/Documents/Visual Studio 2017/Projects/МоиРаботы/CV/x64/Debug/Проект4.exe;";
	for (int j = 0; j < num_of_neigh; j++)
	{
		for (int i = 0; i < num_of_steps; i++)
		{
			results_of_find.open("results_of_find.txt", ios_base::app);
			results_of_find << "step: " << step[i] << " neigh: " << neigh[j] << endl;
			results_of_find.close();
			unsigned int start_time = clock();
			f2(1, ch, step[i], neigh[j], num_of_files);
			f3(num_of_files);
			f4(num_of_files, area);
			unsigned int end_time = clock();
			results_of_find.open("results_of_find.txt", ios_base::app);
			results_of_find << "time: " << end_time - start_time << endl;
			results_of_find.close();
		}
	}
	return 0;
}