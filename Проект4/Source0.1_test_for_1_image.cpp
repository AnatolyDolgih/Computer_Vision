#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay(Mat frame);


/** Global variables */
String face_cascade_name;
CascadeClassifier face_cascade;
String window_name = "Capture - Face detection";
ofstream write;
/** @function main */
int main(int argc, const char** argv)
{
	CommandLineParser parser(argc, argv,
		"{help h||}"
		"{face_cascade|C:/Users/Denis D/Desktop/С++/opencv/build/etc/haarcascades/haarcascade_frontalface_alt.xml|}"
		"{eyes_cascade|C:/Users/Denis D/Desktop/С++/opencv/build/etc/haarcascades/haarcascade_eye_tree_eyeglasses.xml|}");

	cout << "\nThis program demonstrates using the cv::CascadeClassifier class to detect objects (Face + eyes) in a video stream.\n"
		"You can use Haar or LBP features.\n\n";
	parser.printMessage();

	face_cascade_name = parser.get<string>("face_cascade");
	//адрес фото, для которого требуется определить лицо
	String imageName("C:/Users/Denis D/Desktop/С++/БДфото/2002/08/26/big/img_265.jpg");

	Mat frame;

	frame = imread(imageName, IMREAD_COLOR);

	//-- 1. Load the cascades
	if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return -1; };

	//проверка на пустоту
	if (frame.empty())                    
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	detectAndDisplay(frame);

	imshow(window_name, frame);

	waitKey(0);
	return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	 
	for (size_t i = 0; i < faces.size(); i++)
	{
		// красный - аннотированный, розовый - найденный нами
		Rect rec1,rec12,rec13, rec2;
		rec1.x = 61;
		rec1.y = 20;
		rec1.width = 88;	
		rec1.height = 134;

		rec12.x = 157;
		rec12.y = 88;
		rec12.width = 54;
		rec12.height = 82;

		rec13.x = 297;
		rec13.y = -53;
		rec13.width = 86;
		rec13.height = 342;

		rec2.x = faces[i].x;
		rec2.y = faces[i].y;
		rec2.width = faces[i].width;
		rec2.height = faces[i].height;
		rectangle(frame, rec1, Scalar(0, 0, 255), 1, LINE_8, 0);
		rectangle(frame, rec12, Scalar(0, 0, 255), 1, LINE_8, 0);
		rectangle(frame, rec13, Scalar(0, 0, 255), 1, LINE_8, 0);
		rectangle(frame, rec2, Scalar(255, 0, 255), 1, LINE_8, 0);
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);


		cout << "x" << faces[i].x << endl;
		cout << "y" << faces[i].y << endl;
		cout << "width" << faces[i].width << endl;
		cout << "height" << faces[i].height << endl;
	}
	//-- Show what you got
	
	imshow(window_name, frame);
}

