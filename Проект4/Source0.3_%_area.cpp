#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
// Площадь общего пересечения двух прямоугольников
float S(float, float, float, float, float, float, float, float);
struct Coord_Rect
{
	float X0;// Нижний левый угол
	float Y0;//
	float X1;// Верхний правый угол
	float Y1;//
};
using namespace std;
void f3(int num_of_files)
{
	ifstream our, annot;
	ofstream face;
	our.open("results.txt");
	for (int i = 1; i < num_of_files + 1; i++)
	{	
		face.open("face0" + to_string(i) + ".txt");
		annot.open("FDDB-fold-0" + to_string(i) + "-ellipseList.txt");
		string str;
		while (!annot.eof())
		{
			int n1, n2;
			annot >> str;
			face << str << " ";
			our >> str;
			annot >> n1;
			face << n1 << " ";
			our >> n2;
			face << n2 << " ";

			// Массив координат аннотированных прямоуг.
			Coord_Rect* face_coord = new Coord_Rect[n1];
			for (int i = 0; i < n1; i++)
			{
				float R1, R2, X, Y;//R1 - радиус длины лица(по y), R2 - радиус ширины лица(по х), х,у - коорд. центра прямоуг.

				annot >> R1;
				annot >> R2;
				annot >> str;
				annot >> X;
				annot >> Y;

				face_coord[i].X0 = X - R2;
				face_coord[i].Y0 = Y + R1;
				face_coord[i].X1 = X + R2;
				face_coord[i].Y1 = Y - R1;

				annot >> str;
			}

			// Массив координат наших прямоуг.
			Coord_Rect* our_coord = new Coord_Rect[n2];
			for (int i = 0; i < n2; i++)
			{
				float X, Y, W, H;//координаты верхнего левого угла, ширина, высота

				our >> X;
				our >> Y;
				our >> W;
				our >> H;

				our_coord[i].X0 = X;
				our_coord[i].Y0 = Y + H;
				our_coord[i].X1 = X + W;
				our_coord[i].Y1 = Y;

			}

			// Запись для аннотированных лиц
			for (int i = 0; i < n1; i++)
			{
				for (int j = 0; j < n2; j++)
				{

					face << i + 1 << " " << j + 1 << " " << S(face_coord[i].X0, face_coord[i].Y0, face_coord[i].X1, face_coord[i].Y1, our_coord[j].X0, our_coord[j].Y0, our_coord[j].X1, our_coord[j].Y1) << " ";
				}
			}
			delete[] face_coord;
			delete[] our_coord;
		}
		face.close();
		annot.close();
	}
	our.close();
}
float S(float X0, float Y0, float X1, float Y1, float X2, float Y2, float X3, float Y3)
{
	vector<float> X(4);
	vector<float> Y(4);

	X[0] = X0;
	X[1] = X1;
	X[2] = X2;
	X[3] = X3;
	Y[0] = Y0;
	Y[1] = Y1;
	Y[2] = Y2;
	Y[3] = Y3;

		float S_annot = (X[1] - X[0])*(Y[0] - Y[1]);
		if (X[0] >= X[3] || X[2] >= X[1] || Y[3] >= Y[0] || Y[1] >= Y[2])//значит не пересекаются
		{
			return 0;
		}
		else
		{//Если пересекаются - тогда найдем площадь
			sort(X.begin(), X.end());
			sort(Y.begin(), Y.end());
			float S = (X[2] - X[1])*(Y[2] - Y[1]);//Координаты внутреннего прямоугольника - будут 2 и 3 по величине	
			return S*100/S_annot;
		}
}