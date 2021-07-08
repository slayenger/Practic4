#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const double g = 9.8;

struct image {
	int mx;
	int my;
	int* points;
};

void coordinates(double t, double h, double v1, double* hnewx, double* hnewy) {
	if (h > (g * t * t) / 2) {
		(*hnewy) = h - ((g * t * t) / 2);
		(*hnewx) = v1 * t;
	}
	if (h - (g * t * t) / 2 < 0.001) {
		(*hnewy) = 0;
		(*hnewx) = v1 * t;
	}
}

void createlmage(image* img, int tmx, int tmy) {
	img->mx = tmx;     //j
	img->my = tmy;       //i
	img->points = new int[tmy * tmx];
	for (int i = 0; i < tmy * tmx; i++) {
		img->points[i] = 0;
	}
}

void showimage(image* img) {
	for (int i = 0; i < img->my; i++) {
		for (int j = 0; j < img->mx; j++) {
			cout << img->points[img->mx * img->my - img->mx * (i + 1) + j];
		}
		cout << endl;
	}
}

void setPointImage(image* img, int y, int x, int color) {
	if (x > 0 && y > 0) img->points[(y - 1) * (img->mx) + x - 1] = color;
	if (x == 0) img->points[img->mx * img->my - img->mx * (img->my - y + 1)] = color;
}

void saveToPnmFile(image* img, const string filename)
{
	fstream out;
	out.open(filename, fstream::out);
	out << "P1" << endl;
	out << img->mx << " " << img->my << endl;

	for (int i = 0; i < img->my; i++)
	{
		for (int j = 0; j < img->mx; j++)
		{
			out << img->points[img->mx * img->my - img->mx * (i + 1) + j] << " ";
		}
		out << endl;
	}

	out.close();
}


int main()
{
	image img;
	int mx, my, x, y, color;
	mx = 800;                     //j
	my = 400;                       //i
	createlmage(&img, mx, my);
	cout.precision(6);
	double h, t = 0, hnewy, hnewx = 0, v1;
	double deltaT = 0.0001;
	cout << "Enter the height in meters: ";
	cin >> h;
	cout << "Enter initial speed in meters per second: ";
	cin >> v1;
	hnewy = h;
	while ((((int)hnewy) % 400 != 0) && (((int)hnewx) < 79)) {
		coordinates(t, h, v1, &hnewx, &hnewy);
		setPointImage(&img, ((int)hnewy) % 400, ((int)hnewx) % 800, 1);
		cout << ((int)hnewy) % 400 << ' ' << ((int)hnewx) % 800 << ' ' << t << endl;
		t = t + deltaT;
	}
	saveToPnmFile(&img, "F1.pnm");
}