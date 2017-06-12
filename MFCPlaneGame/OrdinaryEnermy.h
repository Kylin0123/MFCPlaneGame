#pragma once
#include "Enermy.h"
#include<list>
#include<memory>
class OrdinaryEnermy :
	public Enermy
{
public:
	OrdinaryEnermy(int x, int y, int s, int ss);
	~OrdinaryEnermy();
	virtual void updateMap(CDC* pDC);
	virtual void shoot(list<shared_ptr<Enermy> > &enermyArray);
	virtual void move();
	virtual bool checkHit(int x, int y, int height, int width);
protected:
	int shootSpeed;
	int shootSpeedCnt;
private:
	const int picHeight = 57;
	const int picWidth = 43;
};

