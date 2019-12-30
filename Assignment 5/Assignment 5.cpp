#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<iostream>
#include "GP142.H"
#include<vector>
#include<conio.h>
#include<fstream>
#include<string.h>
#include<stdio.h>
#define FALSE 0
#define TRUE  1
using namespace std;
static int i1 = 0;
void dda_line(int x1, int x2, int y1, int y2, int color)
{

	float dx, dy, len, x, y, xi, yi;

	int i;

	dx = abs(x2 - x1);

	dy = abs(y2 - y1);



	if (dx >= dy)

		len = dx;

	else

		len = dy;



	dx = (x2 - x1) / len;

	dy = (y2 - y1) / len;



	x = x1 + 0.5;

	y = y1 + 0.5;

	GP142_pixelXY(color, x1, y1);

	GP142_pixelXY(color, x2, y2);

	for (i = 0; i <= len; i++)

	{
		if (i % 9<2)

		{
		}

		else if (i % 9<6)

			GP142_pixelXY(color, x, y);

		else if (i % 9 == 7)

		{
		}

		else

			GP142_pixelXY(color, x, y);

		x += dx;

		y += dy;

	}

}

class Shape
{
protected:
	vector<GP142_point> p;
	int colour;
	int n = 0;
public:
	virtual void draw() = 0;
	virtual bool contains(GP142_point) = 0;
};
Shape** Allshapes = new Shape*[1];
Shape**decreaseBy1(Shape**arr1, int n)
{
	Shape**arr2 = new Shape*[n];
	for (int i = 0; i < n; i++)
	{
		arr2[i] = arr1[i];
	}
	delete[]arr1;
	return arr2;
}
static int n1 = 1;
Shape**extendByFactor2(Shape**arr1, int&n)
{
	Shape**arr2 = new Shape*[2 * n];
	for (int i = 0; i < n; i++)
	{
		arr2[i] = arr1[i];
	}
	n = n * 2;
	arr2 = arr1;
	arr1 = NULL;
	delete[]arr1;
	return arr2;
}

class Circle : public Shape
{
	int fillcolor;
	GP142_point e;
	double rad;
public:
	Circle(int color, GP142_point a, GP142_point b)
	{
		e = a;
		n = 2;
		p.push_back(a);
		p.push_back(b);
		colour = color;
		int radius = sqrt((b.y - a.y)*(b.y - a.y) + (b.x - a.x)*(b.x - a.x));
		rad = radius;
	}
	void draw()
	{
		GP142_circleP(colour, e, rad);
	}
	bool contains(GP142_point a)
	{
		int dx = abs(a.x - e.x);
		int dy = abs(a.y - e.y);
		int	R = rad;
		if (dx > R)
			return false;
		else if (dy > R)
			return false;

		else if (dx + dy <= R)
			return true;
		else if (dx ^ 2 + dy ^ 2 <= R ^ 2)
			return true;
		else
			return false;
	}
};
class Openshape : public Shape
{
protected:
	bool style;
};
class Polygo : public Shape
{
	//vector<Line*> d;
protected:
	int fillcolor;
public:
	//Polygo(int color,vector<Line*> h,int num)
	//{
	//	d = h;
	//	colour = color;
	//	for (int i = 0; i < num; i++)
	//	{
	//		d[i]->draw();
	//	}
	//}
	Polygo()
	{
		
	}
	void draw()
	{

	}
	bool contains(GP142_point a)
	{
		////check the intersections
		//if (((polyK.Y > currentPoint.Y) != (polyJ.Y > currentPoint.Y)) &&(currentPoint.X< (polyJ.X - polyK.X) * (currentPoint.Y - polyK.Y) / (polyJ.Y - polyK.Y) + polyK.X))
		//	oddNodes = !oddNodes;
		//if (oddNodes)
		//{
		//	//mouse point is inside the Polygo
		//	isSelected = true;
		//}
		//else //if even number of intersections
		//{
		//	//mouse point is outside the Polygo so deselect the Polygo
		//	isSelected = false;
		//}
		return true;
	}
};
class Text : public Shape
{
	GP142_point b;
	char t;
public:
	Text(int color, GP142_point a, char text)
	{
		b = a;
		t = text;
		p.push_back(a);
		n++;
		colour = color;
		GP142_printfP(color, b, 15, "%lc", text); //keep on working until 'x' is pressed
	}
	void draw()
	{

	}
	bool contains(GP142_point a)
	{
		if (b.x - 10 <= a.x&&b.x + 10 >= a.x&&b.y - 10 <= a.y&&b.y + 10 >= a.y)
		{
			return true;
		}
		return false;
	}
};
class Line : public Openshape
{
	GP142_point s, t;
public:
	Line(int color, GP142_point a, GP142_point b, bool flag)
	{
		s = a;
		t = b;
		n = 2;
		style = flag;
		p.push_back(a);
		p.push_back(b);
		colour = color;

	}
	void draw()
	{
		if (style == true)
		{
			GP142_lineP(colour, s, t, 5);
		}
		else
			dda_line(s.x, t.x, s.y, t.y, colour);
	}
	bool contains(GP142_point p)
	{
		//vector<GP142_point> v = vect;
		int slope = (t.y - s.y) / (t.x - s.x);
		if (((p.y - s.y) / (p.x - s.x) - slope)>-1 && ((p.y - s.y) / (p.x - s.x) - slope)<1)
			return true;
		else
			return false;

	}
};
class Triangle : public Polygo
{
	GP142_point s;
	GP142_point t;
	GP142_point q;
public:
	Triangle(int color, GP142_point a, GP142_point b, GP142_point c)
	{
		s = a;
		t = b;
		q = c;
		fillcolor;
		n = 3;
		p.push_back(a);
		p.push_back(b);
		p.push_back(c);
		colour = color;
	}
	void draw()
	{
		GP142_triangleP(colour, s, t, q, 5);
	}
	bool contains(GP142_point a)
	{
			int as_x = a.x - s.x;
			int as_y = a.y - s.y;

			bool s_ab = (t.x - s.x)*as_y - (t.y - s.y)*as_x > 0;

			if ((q.x - s.x)*as_y - (q.y - s.y)*as_x > 0 == s_ab)
				return false;

			else if ((q.x - t.x)*(a.y - t.y) - (q.y - t.y)*(a.x - t.x) > 0 != s_ab)
				return false;

			return true;
	}
};
class Rectangl : public Polygo
{
	GP142_point s;
	GP142_point t;
public:
	Rectangl(int color, GP142_point a, GP142_point b)
	{
		s = a;
		t = b;
		fillcolor;
		n = 2;
		p.push_back(a);
		p.push_back(b);
		colour = color;
	}
	void draw()
	{
		GP142_rectangleP(colour, s, t, 5);
	}
	bool contains(GP142_point a)
	{
		{
			int width = sqrt((t.x - s.x)*(t.x - s.x));
			int height = sqrt((t.y - s.y)*(t.y - s.y));
			int pointX = a.x;
			int pointY = a.y;
			if (pointX >= s.x && pointX <= s.x + width &&pointY >= t.y && pointY <= t.y + height)
				return true;
			else
				return false;
		}
	}
};

int main(void)
{

	int quit;
	int event;
	int mouse_x, mouse_y;
	char key_pressed;
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0, count9 = 0;
	int x1, y1, x2, y2, x, y;
	int color = 1;
	vector<Line*> h;
	int h1=0;
	ifstream fin("file.pb");
	ofstream fout;

	/* Open a blank GP142 graphics window.*/
	GP142_open();
	GP142_point mbullet3s;
	mbullet3s.x = -250;
	mbullet3s.y = 120;
	GP142_point mbullet3e;
	mbullet3e.x = -240;
	mbullet3e.y = 110;
	GP142_point mbullet4s;
	mbullet4s.x = -250;
	mbullet4s.y = 90;
	GP142_point mbullet4e;
	mbullet4e.x = -240;
	mbullet4e.y = 80;
	GP142_rectangleP(11, mbullet3s, mbullet3e, 10);
	GP142_rectangleP(11, mbullet4s, mbullet4e, 10);
	GP142_textXY(1, -230, 100, 25, "N");
	GP142_textXY(1, -210, 100, 25, "E");
	GP142_textXY(1, -192, 100, 25, "W");
	GP142_textXY(1, -230, 70, 25, "L");
	GP142_textXY(1, -220, 70, 25, "O");
	GP142_textXY(1, -200, 70, 25, "A");
	GP142_textXY(1, -185, 70, 25, "D");

	GP142_textXY(1, -240, 170, 25, "W");
	GP142_textXY(1, -215, 170, 25, "h");
	GP142_textXY(1, -200, 170, 25, "a");
	GP142_textXY(1, -185, 170, 25, "t");
	GP142_textXY(1, -170, 170, 25, "d");
	GP142_textXY(1, -155, 170, 25, "o");
	GP142_textXY(1, -135, 170, 25, "y");
	GP142_textXY(1, -125, 170, 25, "o");
	GP142_textXY(1, -110, 170, 25, "u");
	GP142_textXY(1, -85, 170, 25, "w");
	GP142_textXY(1, -65, 170, 25, "a");
	GP142_textXY(1, -50, 170, 25, "n");
	GP142_textXY(1, -35, 170, 25, "t");
	GP142_textXY(1, -20, 170, 25, "t");
	GP142_textXY(1, -13, 170, 25, "o");
	GP142_textXY(1, 10, 170, 25, "d");
	GP142_textXY(1, 23, 170, 25, "o");
	GP142_textXY(1, 50, 170, 25, "?");
	event = GP142_await_event(&mouse_x, &mouse_y, &key_pressed);
	GP142_lineXY(0, -1000, 1000, 1000, -1000, 1000);
	if ((-250 <= mouse_x&&mouse_x <= -240) && (80 <= mouse_y&&mouse_y <= 90))
	{
		while (!fin.eof())
		{
				char temp[50];
				while (fin.getline(temp, 50))
				{
					int a[10];
					int b = 0;
					if (temp[0] == 'c')
					{
						char*token = strtok(temp, ",");
						while (token != nullptr)
						{
							a[b] = atoi(token);
							token = strtok(nullptr, ",");
							b++;
						}
						if (temp[0] == 'c')
						{
							GP142_point c;
							c.x = a[2];
							c.y = a[3];
							GP142_point d;
							d.x = a[4];
							d.y = a[5];
							Circle z(a[1], c, d);
							fout << "c" << "," << a[1] << "," << c.x << "," << c.y << "," << d.x << "," << d.y << endl;
							z.draw();
							Allshapes[i1] = &z;
							i1++;
						}
					}
					if (temp[0] == 's')
					{
						char*token = strtok(temp, ",");
						while (token != nullptr)
						{
							a[b] = atoi(token);
							token = strtok(nullptr, ",");
							b++;
						}
						if (temp[0] == 's')
						{
							GP142_point c;
							c.x = a[2];
							c.y = a[3];
							GP142_point d;
							d.x = a[4];
							d.y = a[5];
							Line z(a[1], c, d,true);
							fout << "s" << "," << a[1] << "," << c.x << "," << c.y << "," << d.x << "," << d.y << endl;
							z.draw();
							Allshapes[i1] = &z;
							i1++;
						}
					}
					if (temp[0] == 'd')
					{
						char*token = strtok(temp, ",");
						while (token != nullptr)
						{
							a[b] = atoi(token);
							token = strtok(nullptr, ",");
							b++;
						}
						if (temp[0] == 'd')
						{
							GP142_point c;
							c.x = a[2];
							c.y = a[3];
							GP142_point d;
							d.x = a[4];
							d.y = a[5];
							Line z(a[1], c, d, false);
							fout << "d" << "," << a[1] << "," << c.x << "," << c.y << "," << d.x << "," << d.y << endl;
							z.draw();
							Allshapes[i1] = &z;
							i1++;
						}
					}
					if (temp[0] == 'r')
					{
						char*token = strtok(temp, ",");
						while (token != nullptr)
						{
							a[b] = atoi(token);
							token = strtok(nullptr, ",");
							b++;
						}
						if (temp[0] == 'r')
						{
							GP142_point c;
							c.x = a[2];
							c.y = a[3];
							GP142_point d;
							d.x = a[4];
							d.y = a[5];
							Rectangl z(a[1], c, d);
							fout << "r" << "," << a[1] << "," << c.x << "," << c.y << "," << d.x << "," << d.y << endl;
							z.draw();
							Allshapes[i1] = &z;
							i1++;
						}
					}
					if (temp[0] == 'x')
					{
						char*h;
						char*token = strtok(temp, ",");
						while (token != nullptr)
						{
							if (b!=4)
							{
								a[b] = atoi(token);
							}
							else
							{
								h = token;
							}
							token = strtok(nullptr, ",");
							b++;
						}
						if (temp[0] == 'x')
						{
							GP142_point c;
							c.x = a[2];
							c.y = a[3];
							
							Text z(a[1], c, *h);//keep on working until 'x' is pressed
							fout << "x" << "," << a[1] << "," << c.x << "," << c.y << "," << *h<< endl;
							Allshapes[i1] = &z;
							i1++;
						}
					}
					if (temp[0] == 't')
					{
						char*token = strtok(temp, ",");
						while (token != nullptr)
						{
							a[b] = atoi(token);
							token = strtok(nullptr, ",");
							b++;
						}
						if (temp[0] == 't')
						{
							GP142_point c;
							c.x = a[2];
							c.y = a[3];
							GP142_point d;
							d.x = a[4];
							d.y = a[5];
							GP142_point e;
							e.x = a[6];
							e.y = a[7];
							Triangle z(a[1], c, d,e);
							fout << "t" << "," << a[1] << "," << c.x << "," << c.y << "," << d.x << "," << d.y <<","<<e.x<<","<<e.y<< endl;
							z.draw();
							Allshapes[i1] = &z;
							i1++;
						}
					}
			}
		}
	}
	else
	{
		fout.open("file.pb");
	}
	quit = FALSE;
	GP142_point menus;
	menus.x = -670;
	menus.y = -500;
	GP142_point menue;
	menue.x = -300;
	menue.y = 300;
	GP142_point bullet1s;
	bullet1s.x = -650;
	bullet1s.y = 280;
	GP142_point bullet1e;
	bullet1e.x = -640;
	bullet1e.y = 270;
	GP142_point subbullet1s;
	subbullet1s.x = -550;
	subbullet1s.y = 250;
	GP142_point subbullet1e;
	subbullet1e.x = -540;
	subbullet1e.y = 240;
	GP142_point subbullet2s;
	subbullet2s.x = -550;
	subbullet2s.y = 220;
	GP142_point subbullet2e;
	subbullet2e.x = -540;
	subbullet2e.y = 210;
	GP142_point bullet2s;
	bullet2s.x = -650;
	bullet2s.y = 190;
	GP142_point bullet2e;
	bullet2e.x = -640;
	bullet2e.y = 180;
	GP142_point bullet3s;
	bullet3s.x = -650;
	bullet3s.y = 160;
	GP142_point bullet3e;
	bullet3e.x = -640;
	bullet3e.y = 150;
	GP142_point bullet4s;
	bullet4s.x = -650;
	bullet4s.y = 130;
	GP142_point bullet4e;
	bullet4e.x = -640;
	bullet4e.y = 120;
	GP142_point bullet5s;
	bullet5s.x = -650;
	bullet5s.y = 100;
	GP142_point bullet5e;
	bullet5e.x = -640;
	bullet5e.y = 90;
	GP142_point bullet6s;
	bullet6s.x = -650;
	bullet6s.y = 70;
	GP142_point bullet6e;
	bullet6e.x = -640;
	bullet6e.y = 60;
	GP142_point bullet7s;
	bullet7s.x = -650;
	bullet7s.y = 40;
	GP142_point bullet7e;
	bullet7e.x = -640;
	bullet7e.y = 30;
	GP142_point bullet8s;
	bullet8s.x = -650;
	bullet8s.y = 10;
	GP142_point bullet8e;
	bullet8e.x = -640;
	bullet8e.y = 0;
	GP142_point bullet9s;
	bullet9s.x = -650;
	bullet9s.y = -20;
	GP142_point bullet9e;
	bullet9e.x = -640;
	bullet9e.y = -30;
	GP142_point bullet10s;
	bullet10s.x = -650;
	bullet10s.y = -50;
	GP142_point bullet10e;
	bullet10e.x = -640;
	bullet10e.y = -60;
	GP142_point cbullet1s;
	cbullet1s.x = -650;
	cbullet1s.y = -130;
	GP142_point cbullet1e;
	cbullet1e.x = -640;
	cbullet1e.y = -140;
	GP142_point cbullet2s;
	cbullet2s.x = -650;
	cbullet2s.y = -160;
	GP142_point cbullet2e;
	cbullet2e.x = -640;
	cbullet2e.y = -170;
	GP142_point cbullet3s;
	cbullet3s.x = -650;
	cbullet3s.y = -190;
	GP142_point cbullet3e;
	cbullet3e.x = -640;
	cbullet3e.y = -200;
	GP142_point cbullet4s;
	cbullet4s.x = -650;
	cbullet4s.y = -220;
	GP142_point cbullet4e;
	cbullet4e.x = -640;
	cbullet4e.y = -230;
	GP142_point cbullet5s;
	cbullet5s.x = -650;
	cbullet5s.y = -250;
	GP142_point cbullet5e;
	cbullet5e.x = -640;
	cbullet5e.y = -260;
	GP142_point cbullet6s;
	cbullet6s.x = -650;
	cbullet6s.y = -280;
	GP142_point cbullet6e;
	cbullet6e.x = -640;
	cbullet6e.y = -290;
	GP142_point cbullet7s;
	cbullet7s.x = -650;
	cbullet7s.y = -310;
	GP142_point cbullet7e;
	cbullet7e.x = -640;
	cbullet7e.y = -330;
	while (!quit) {

		if (n1 == i1)
		{
			extendByFactor2(Allshapes, n1);
		}

		GP142_rectangleP(1, menus, menue, 1);
		GP142_rectangleP(11, bullet1s, bullet1e, 10);
		GP142_textXY(1, -620, 260, 25, "L");
		GP142_textXY(1, -605, 260, 25, "i");
		GP142_textXY(1, -600, 260, 25, "n");
		GP142_textXY(1, -585, 260, 25, "e");
		GP142_rectangleP(11, bullet2s, bullet2e, 10);
		GP142_textXY(1, -630, 170, 25, "T");
		GP142_textXY(1, -615, 170, 25, "R");
		GP142_textXY(1, -595, 170, 25, "I");
		GP142_textXY(1, -585, 170, 25, "A");
		GP142_textXY(1, -570, 170, 25, "N");
		GP142_textXY(1, -555, 170, 25, "G");
		GP142_textXY(1, -538, 170, 25, "L");
		GP142_textXY(1, -525, 170, 25, "E");
		GP142_rectangleP(11, bullet3s, bullet3e, 10);
		GP142_textXY(1, -630, 140, 25, "R");
		GP142_textXY(1, -615, 140, 25, "E");
		GP142_textXY(1, -600, 140, 25, "C");
		GP142_textXY(1, -585, 140, 25, "T");
		GP142_textXY(1, -570, 140, 25, "A");
		GP142_textXY(1, -555, 140, 25, "N");
		GP142_textXY(1, -540, 140, 25, "G");
		GP142_textXY(1, -523, 140, 25, "L");
		GP142_textXY(1, -510, 140, 25, "E");
		GP142_rectangleP(11, bullet4s, bullet4e, 10);
		GP142_textXY(1, -630, 110, 25, "C");
		GP142_textXY(1, -610, 110, 25, "I");
		GP142_textXY(1, -600, 110, 25, "R");
		GP142_textXY(1, -585, 110, 25, "C");
		GP142_textXY(1, -568, 110, 25, "L");
		GP142_textXY(1, -555, 110, 25, "E");
		GP142_rectangleP(11, bullet5s, bullet5e, 10);
		GP142_textXY(1, -630, 80, 25, "P");
		GP142_textXY(1, -615, 80, 25, "O");
		GP142_textXY(1, -595, 80, 25, "L");
		GP142_textXY(1, -585, 80, 25, "Y");
		GP142_textXY(1, -570, 80, 25, "G");
		GP142_textXY(1, -553, 80, 25, "O");
		GP142_textXY(1, -537, 80, 25, "N");
		GP142_rectangleP(11, bullet6s, bullet6e, 10);
		GP142_textXY(1, -630, 50, 25, "C");
		GP142_textXY(1, -615, 50, 25, "U");
		GP142_textXY(1, -595, 50, 25, "R");
		GP142_textXY(1, -580, 50, 25, "V");
		GP142_textXY(1, -565, 50, 25, "E");
		GP142_rectangleP(11, bullet7s, bullet7e, 10);
		GP142_textXY(1, -630, 20, 25, "T");
		GP142_textXY(1, -615, 20, 25, "E");
		GP142_textXY(1, -600, 20, 25, "X");
		GP142_textXY(1, -580, 20, 25, "T");
		GP142_rectangleP(11, bullet8s, bullet8e, 10);
		GP142_textXY(1, -630, -10, 25, "E");
		GP142_textXY(1, -615, -10, 25, "R");
		GP142_textXY(1, -600, -10, 25, "A");
		GP142_textXY(1, -585, -10, 25, "S");
		GP142_textXY(1, -570, -10, 25, "E");
		GP142_textXY(1, -553, -10, 25, "R");
		GP142_rectangleP(11, bullet9s, bullet9e, 10);
		GP142_textXY(1, -630, -40, 25, "B");
		GP142_textXY(1, -615, -40, 25, "U");
		GP142_textXY(1, -600, -40, 25, "C");
		GP142_textXY(1, -585, -40, 25, "K");
		GP142_textXY(1, -570, -40, 25, "E");
		GP142_textXY(1, -555, -40, 25, "T");
		GP142_textXY(1, -530, -40, 25, "F");
		GP142_textXY(1, -515, -40, 25, "I");
		GP142_textXY(1, -510, -40, 25, "L");
		GP142_textXY(1, -495, -40, 25, "L");
		GP142_rectangleP(11, bullet10s, bullet10e, 10);
		GP142_textXY(1, -630, -70, 25, "S");
		GP142_textXY(1, -615, -70, 25, "A");
		GP142_textXY(1, -600, -70, 25, "V");
		GP142_textXY(1, -585, -70, 25, "E");

		GP142_textXY(5, -570, -120, 40, "C");
		GP142_textXY(5, -545, -120, 40, "O");
		GP142_textXY(5, -515, -120, 40, "L");
		GP142_textXY(5, -495, -120, 40, "O");
		GP142_textXY(5, -465, -120, 40, "R");
		GP142_textXY(5, -440, -120, 40, "S");
		GP142_rectangleP(2, cbullet1s, cbullet1e, 10);
		GP142_textXY(1, -630, -150, 25, "R");
		GP142_textXY(1, -615, -150, 25, "E");
		GP142_textXY(1, -600, -150, 25, "D");
		GP142_rectangleP(2, cbullet2s, cbullet2e, 10);
		GP142_textXY(1, -630, -180, 25, "B");
		GP142_textXY(1, -615, -180, 25, "L");
		GP142_textXY(1, -600, -180, 25, "U");
		GP142_textXY(1, -585, -180, 25, "E");
		GP142_rectangleP(2, cbullet3s, cbullet3e, 10);
		GP142_textXY(1, -630, -210, 25, "Y");
		GP142_textXY(1, -615, -210, 25, "E");
		GP142_textXY(1, -600, -210, 25, "L");
		GP142_textXY(1, -585, -210, 25, "L");
		GP142_textXY(1, -570, -210, 25, "O");
		GP142_textXY(1, -555, -210, 25, "W");
		GP142_rectangleP(2, cbullet4s, cbullet4e, 10);
		GP142_textXY(1, -630, -240, 25, "W");
		GP142_textXY(1, -605, -240, 25, "H");
		GP142_textXY(1, -590, -240, 25, "I");
		GP142_textXY(1, -585, -240, 25, "T");
		GP142_textXY(1, -570, -240, 25, "E");
		GP142_rectangleP(2, cbullet5s, cbullet5e, 10);
		GP142_textXY(1, -630, -270, 25, "O");
		GP142_textXY(1, -615, -270, 25, "R");
		GP142_textXY(1, -595, -270, 25, "A");
		GP142_textXY(1, -580, -270, 25, "N");
		GP142_textXY(1, -565, -270, 25, "G");
		GP142_textXY(1, -550, -270, 25, "E");
		GP142_rectangleP(2, cbullet6s, cbullet6e, 10);
		GP142_textXY(1, -630, -300, 25, "G");
		GP142_textXY(1, -615, -300, 25, "R");
		GP142_textXY(1, -600, -300, 25, "E");
		GP142_textXY(1, -585, -300, 25, "E");
		GP142_textXY(1, -570, -300, 25, "N");
		GP142_rectangleP(2, cbullet7s, cbullet7e, 10);
		GP142_textXY(1, -630, -330, 25, "B");
		GP142_textXY(1, -615, -330, 25, "L");
		GP142_textXY(1, -600, -330, 25, "A");
		GP142_textXY(1, -585, -330, 25, "C");
		GP142_textXY(1, -570, -330, 25, "K");
		GP142_rectangleP(3, subbullet1s, subbullet1e, 10);
		GP142_textXY(1, -530, 230, 25, "D");
		GP142_textXY(1, -515, 230, 25, "O");
		GP142_textXY(1, -500, 230, 25, "T");
		GP142_textXY(1, -485, 230, 25, "T");
		GP142_textXY(1, -470, 230, 25, "E");
		GP142_textXY(1, -455, 230, 25, "D");
		GP142_rectangleP(3, subbullet2s, subbullet2e, 10);
		GP142_textXY(1, -530, 200, 25, "S");
		GP142_textXY(1, -515, 200, 25, "O");
		GP142_textXY(1, -495, 200, 25, "L");
		GP142_textXY(1, -480, 200, 25, "I");
		GP142_textXY(1, -470, 200, 25, "D");
		/* Get the next event */
		event = GP142_await_event(&mouse_x, &mouse_y, &key_pressed);

		/* Decide what kind of event we got */
		switch (event) {
		case GP142_QUIT:
			/* The user asked to quit by selecting "Quit" from the "Run   */
			/* menu or by hitting ctrl-Q.                                 */
			quit = TRUE;
			break;

		case GP142_MOUSE:
			if ((-650 <= mouse_x&&mouse_x <= -640) && (-140 <= mouse_y&&mouse_y <= -130))
			{
				color = 2;
			}
			if ((-650 <= mouse_x&&mouse_x <= -640) && (-170 <= mouse_y&&mouse_y <= -160))
			{
				color = 4;
			}
			if ((-650 <= mouse_x&&mouse_x <= -640) && (-200 <= mouse_y&&mouse_y <= -190))
			{
				color = 5;
			}
			if ((-650 <= mouse_x&&mouse_x <= -640) && (-230 <= mouse_y&&mouse_y <= -220))
			{
				color = 1;
			}
			if ((-650 <= mouse_x&&mouse_x <= -640) && (-260 <= mouse_y&&mouse_y <= -250))
			{
				color = 13;
			}
			if ((-650 <= mouse_x&&mouse_x <= -640) && (-290 <= mouse_y&&mouse_y <= -280))
			{
				color = 3;
			}
			if ((-650 <= mouse_x&&mouse_x <= -640) && (-320 <= mouse_y&&mouse_y <= -310))
			{
				color = 0;
			}
			if ((-550 <= mouse_x&&mouse_x <= -540) && (210 <= mouse_y&&mouse_y <= 230) && count1 == 0)
			{
				count1 = 1;
				break;
			}
			if (count1 == 1)
			{
				x1 = mouse_x;
				y1 = mouse_y;
				count1 = 2;
				break;
			}
			if (count1 == 2 || count2 == 2)
			{
				if (count1 == 2)
				{
					GP142_point a, b;
					a.x = x1;
					a.y = y1;
					b.x = mouse_x;
					b.y = mouse_y;
					Line c(color, a, b, true);
					fout << "sl" <<","<< color << "," << a.x << "," << a.y << "," << b.x << "," << b.y << endl;
					Allshapes[i1] = &c;
					Allshapes[i1]->draw();
					i1++;
				}
				else
				{
					GP142_point a, b;
					a.x = x1;
					a.y = y1;
					b.x = mouse_x;
					b.y = mouse_y;
					Line c(color, a, b, false);
					fout << "dl" << "," << color << "," << a.x << "," << a.y << "," << b.x << "," << b.y << endl;
					Allshapes[i1] = &c;
					Allshapes[i1]->draw();
					i1++;
				}
				count2 = 0;
				count1 = 0;
			}
			if ((-550 <= mouse_x&&mouse_x <= -540) && (240 <= mouse_y&&mouse_y <= 260) && count2 == 0)
			{
				count2 = 1;
				break;
			}
			if (count2 == 1)
			{
				x1 = mouse_x;
				y1 = mouse_y;
				count2 = 2;
				break;
			}
			if ((-655 <= mouse_x&&mouse_x <= -635) && (175 <= mouse_y&&mouse_y <= 195) && count3 == 0)
			{
				count3 = 1;
				break;
			}
			if (count3 == 1)
			{
				x1 = mouse_x;
				y1 = mouse_y;
				count3 = 2;
				break;
			}
			if (count3 == 2)
			{
				x2 = mouse_x;
				y2 = mouse_y;
				count3 = 3;
				break;
			}
			if (count3 == 3)
			{
				GP142_point a, b, c;
				a.x = x1;
				a.y = y1;
				b.x = x2;
				b.y = y2;
				c.x = mouse_x;
				c.y = mouse_y;
				Triangle x(color, a, b, c);
				fout << "t" << "," << color << "," << a.x << "," << a.y << "," << b.x << "," << b.y <<","<< c.x << "," << c.y << endl;
				Allshapes[i1] = &x;
				Allshapes[i1]->draw();
				i1++;
				count3 = 0;
				break;
			}
			if ((-655 <= mouse_x&&mouse_x <= -635) && (145 <= mouse_y&&mouse_y <= 165) && count4 == 0)
			{
				count4 = 1;
				break;
			}
			if (count4 == 1)
			{
				x1 = mouse_x;
				y1 = mouse_y;
				count4 = 2;
				break;
			}
			if (count4 == 2)
			{
				GP142_point a, b;
				a.x = x1;
				a.y = y1;
				b.x = mouse_x;
				b.y = mouse_y;
				Rectangl c(color, a, b);
				fout << "r" << "," << color << "," << a.x << "," << a.y << "," << b.x << "," << b.y << endl;
				Allshapes[i1] = &c;
				Allshapes[i1]->draw();
				i1++;
				count4 = 0;
				break;
			}
			if ((-665 <= mouse_x&&mouse_x <= -625) && (110 <= mouse_y&&mouse_y <= 145) && count5 == 0)
			{
				count5 = 1;
				break;
			}
			if (count5 == 1)
			{
				x1 = mouse_x;
				y1 = mouse_y;
				count5 = 2;
				break;
			}
			if (count5 == 2)
			{
				GP142_point a;
				a.x = x1;
				a.y = y1;
				GP142_point b;
				b.x = mouse_x;
				b.y = mouse_y;
				Circle c(color, a, b);
				fout << "c" << "," << color << "," << a.x << "," << a.y << "," << b.x << "," << b.y << endl;
				Allshapes[i1] = &c;
				Allshapes[i1]->draw();
				i1++;
				count5 = 0;
				break;
			}
			if ((-655 <= mouse_x&&mouse_x <= -635) && (90 <= mouse_y&&mouse_y <= 110) && count6 == 0)
			{
				count6 = 9;
				break;
			}
			if (count6 == 9)
			{
				x = mouse_x;
				y = mouse_y;
				x1 = mouse_x;
				y1 = mouse_y;
				count6 = 2;
				break;
			}
			if (count6 == 1)
			{
				GP142_point p;
				x1 = mouse_x;
				y1 = mouse_y;
				p.x = mouse_x;
				p.y = mouse_y;
				count6 = 2;
				break;
			}
			if (GetAsyncKeyState(VK_RBUTTON))
			{
				if (count6 == 2)
				{
					GP142_point a, b;
					a.x = x;
					a.y = y;
					b.x = x1;
					b.y = y1;
					Line c(color, a, b, 5);
					fout << "sl" << "," << color << "," << a.x << "," << a.y << "," << b.x << "," << b.y << endl;
					h.push_back(&c);
					h1++;
					//Polygo g(color, h, h1);
					h.clear();
					h1 = 0;
					Allshapes[i1] = &c;
					Allshapes[i1]->draw();
					i1++;
					count6 = 0;
				}

				if (count7 == 2)
				{
					count7 = 0;
				}
				if (count8 == 2)
				{
					count8 = 0;
				}
			}
			if (count6 == 2 && GP142_MOUSE != VK_RBUTTON)
			{
				GP142_point a, b;
				a.x = x1;
				a.y = y1;
				b.x = mouse_x;
				b.y = mouse_y;
				Line c(color, a, b, true);
				fout << "sl" << "," << color << "," << a.x << "," << a.y << "," << b.x << "," << b.y << endl;
				Allshapes[i1] = &c;
				Allshapes[i1]->draw();
				i1++;
				h.push_back(&c);
				h1++;
				x1 = mouse_x;
				y1 = mouse_y;
				count6 = 2;
				break;
			}
			if ((-655 <= mouse_x&&mouse_x <= -635) && (50 <= mouse_y&&mouse_y <= 90) && count7 == 0)
			{
				count7 = 1;
				break;
			}
			if (count7 == 1)
			{
				x1 = mouse_x;
				y1 = mouse_y;
				count7 = 2;
				break;
			}
			else if (count7 == 2 && GP142_MOUSE != VK_RBUTTON)
			{
				GP142_point a, b;
				a.x = x1;
				a.y = y1;
				b.x = mouse_x;
				b.y = mouse_y;
				Line c(color, a, b, 5);
				fout << "sl" << "," << color << "," << a.x << "," << a.y << "," << b.x << "," << b.y << endl;
				Allshapes[i1] = &c;
				Allshapes[i1]->draw();
				i1++;
				x1 = mouse_x;
				y1 = mouse_y;
				count7 = 2;
				break;
			}
			if ((-655 <= mouse_x&&mouse_x <= -635) && (20 <= mouse_y&&mouse_y <= 50) && count8 == 0)
			{
				count8 = 1;
				break;
			}
			if (count8 == 1)
			{
				x1 = mouse_x;
				y1 = mouse_y;
				count8 = 2;
				break;
			}
			if ((-655 <= mouse_x&&mouse_x <= -635) && (-20 <= mouse_y&&mouse_y <= 20) && count9 == 0)
			{
				count9 = 1;
				break;
			}
			if (count9 == 1)
			{
				GP142_point a;
				a.x = mouse_x;
				a.y = mouse_y;
				int h = color;
				for (int i = 0; i < i1; i++)
				{
					if (Allshapes[i]->contains(a))
					{
						Allshapes[i] = Allshapes[i1 - 1];
						i1--;
						GP142_lineXY(0, -1000, 1000, 1000, -1000, 1000);
						for (int j = 0; j < i1; j++)
						{
							Allshapes[i]->draw();
						}
					}
				}
				count9 = 0;
				break;
			}
			break;
		case GP142_KBD:
			if (count8 == 2)
			{
				GP142_point a;
				a.x = x1;
				a.y = y1;
				Text c(color, a, key_pressed);
				fout << "x" << "," << color << "," << a.x << "," << a.y << "," << key_pressed << endl;

				Allshapes[i1] = &c;
				i1++;
				x1 = x1 + 10;
			}

			break;


		default:
			/* Ignore all other events, such as keystrokes, mouse clicks, */
			/* and periodic events.                                       */
			break;
		}

	}  /* end event loop */

	/* Close the graphics window and exit */
	GP142_close();
}

