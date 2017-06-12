#pragma once
#include<vector>
using namespace std;
class Enermy
{
public:
	Enermy(int x, int y, int s);
	~Enermy();
	int getX() { return posX; }
	int getY() { return posY; }
	int getPicWidth() { return picWidth; }
	int getPicHeight() { return picHeight; }
	virtual void updateMap(CDC* pDC);
	virtual void move();
	bool checkBorder(int x1, int y1, int x2, int y2);
	virtual bool checkHit(int x, int y, int height, int width);
protected:
	int posX, posY;
	int speed;
	int cnt;
private:
	const int picWidth = 5*2;
	const int picHeight = 11*2;
};

