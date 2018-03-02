// площадь пересечения в %
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
ifstream face;
fstream results_of_find;

void f4(int num_of_files, int area)
{
	//объявление и определение счетчиков
	int summ_of_img, summ_of_all_faces, summ_of_all_frames, TP, TN, FP, DB;
	summ_of_img = 0;
	summ_of_all_faces = 0;
	summ_of_all_frames = 0;
	TP = 0;
	TN = 0;
	FP = 0;
	DB = 0;
	string garb, hard_case_img;
	results_of_find.open("results_of_find.txt",ios_base::app);
	for (int i = 1; i < num_of_files + 1; i++)
	{
		// to read
		face.open("face0" + to_string(i) + ".txt");

		while (getline(face,hard_case_img,' '))
		{
			summ_of_img++;
			int summ_of_faces, summ_of_frames;

			getline(face, garb, ' ');
			summ_of_faces = atoi(garb.c_str());
			getline(face, garb, ' ');
			summ_of_frames = atoi(garb.c_str());

			summ_of_all_faces += summ_of_faces;
			summ_of_all_frames += summ_of_frames;

			if ((summ_of_faces == 0) && (summ_of_frames == 0))continue;
			else
			{
				if (summ_of_faces == 0) FP += summ_of_frames;
				else
				{
					if (summ_of_frames==0) TN += summ_of_faces;
					else
					{
						// создание таблицы [i][j] i-face j-frame
						float** Matrix = new float*[summ_of_faces];
						for (int j = 0; j < summ_of_faces; j++) Matrix[j] = new float[summ_of_frames];
						// забив таблицы
						for (int j = 0; j < summ_of_faces; j++)
						{
							for (int k = 0; k < summ_of_frames; k++)
							{

								getline(face, garb, ' ');
								getline(face, garb, ' ');
								getline(face, garb, ' ');
							    Matrix[j][k]=atoi(garb.c_str());
							}
						}

						//////////////////////////
						/// Основной алгоритм ///
						////////////////////////

						//1.FP and TP	// если площадь пересечения < 50 FP++ else TP++ // проход по рамкам
						for (int j = 0; j < summ_of_frames; j++)
						{
							int counter = 0;
							for (int k = 0; k < summ_of_faces; k++)
							{
								if (Matrix[k][j] < area) counter++;
							}
							if (counter == summ_of_faces) FP++;
							else TP = TP + (summ_of_faces - counter);
						}
						//2.TN and DB // проход по лицам
						for (int j = 0; j < summ_of_faces; j++)
						{
							int counter = 0;
							for (int k = 0; k < summ_of_frames; k++)
							{
								if (Matrix[j][k] < area) counter++;
							}
							if (counter == summ_of_frames) TN++;
							else
							{
								if ((summ_of_frames - counter) == 1) continue;
								else DB++;
							}
						}
					}
				}
			}
		}
	face.close();
	}
	results_of_find << "Всего изображений: " << summ_of_img << endl << "Всего аннотированно лиц на изображениях: " << summ_of_all_faces << endl << "Всего поставлено рамок: " << summ_of_all_frames << endl << "TN: " << TN << endl << "FP: " << FP << endl << "TP: " << TP << endl << "DB: " << DB << endl;
	cout << "Всего изображений: " << summ_of_img << endl << "Всего аннотированно лиц на изображениях: " << summ_of_all_faces << endl << "Всего поставлено рамок: " << summ_of_all_frames << endl << "TN: " << TN << endl << "FP: " << FP << endl << "TP: " << TP << endl << "DB: " << DB << endl;
	results_of_find.close();
}