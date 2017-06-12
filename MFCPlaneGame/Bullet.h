#pragma once
#include<vector>
using namespace std;
class Bullet
{
public:
	Bullet(int x, int y, int s);
	int getX();
	int getY();
	int getPicHeight() { return picHeight; }
	int getPicWidth() { return picWidth; }
	void updateMap(CDC* pDC);
	void move();
	bool checkBorder(int x1, int y1, int x2, int y2);
	bool checkHit(int x, int y);
	~Bullet();
private:
	int posX, posY;
	int speed;
	int cnt;
private:
	const int picWidth = 5*2;
	const int picHeight = 11*2;
};

