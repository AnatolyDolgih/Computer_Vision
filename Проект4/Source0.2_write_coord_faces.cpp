#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay(Mat, double, int);

/** Global variables */
String face_cascade_name;
CascadeClassifier face_cascade;
ofstream write1;

/** @function main */
void f2(int argc, const char* argv[], double step, int neigh, int num_of_files)
{
	setlocale(LC_ALL, "Russian");
	CommandLineParser parser(argc, argv,
		"{face_cascade|C:/Users/Denis D/Desktop/С++/opencv/build/etc/haarcascades/haarcascade_frontalface_alt.xml|}");

	face_cascade_name = parser.get<string>("face_cascade");

	//-- 1. Load the cascades
	if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); cout<< -1; };

	// файл для записи
	write1.open("results.txt");

	// файл для чтения
	ifstream read;

	// хранение адреса файла FDDB-fold-0i.txt, который открываем
	string str1;

	// хранение адреса картинки, считанной из файла
	string str2;

	for (int i = 1; i < num_of_files + 1; i++)
	{
		str1 = "FDDB-fold-0" + to_string(i) + ".txt";
		read.open(str1);
		if (!read.is_open())
		{
			cout << "Файл не может быть открыт!\n";
			cout<<-1;
		}
		while (!read.eof())
		{
			read >> str2;
			write1 << str2 << " ";
			Mat frame;

			//полный адрес картинки
			string image_adress = "C:/Users/Denis D/Desktop/С++/БДфото/" + str2 + ".jpg";

			frame = imread(image_adress, IMREAD_COLOR);

			//проверка на пустоту
			if (frame.empty())
			{
				cout << "Could not open or find the image" << endl;
				cout<< -1;
			}

			detectAndDisplay(frame,step,neigh);
			
		}
		read.close();
	}
	write1.close();
}

/** @function detectAndDisplay */
void detectAndDisplay(Mat frame, double step, int neigh)
{
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	//equalizeHist(frame_gray, frame_gray); // эквилизация
	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, step, neigh, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	// подсчет общего кол-ва лиц
	write1 << faces.size()<<" ";
	for (int i = 0; i < faces.size(); i++)
	{
		write1 << faces[i].x << " ";
		write1 << faces[i].y << " ";
		write1 << faces[i].width << " ";
		write1 << faces[i].height << " ";
	}
}