#include"stdafx.h"
#include "Player.h"
#include"Resource.h"

 Player::Player() {}

 Player::~Player() {}

 int Player::getX() { return posX; }

 int Player::getY() { return posY; }

 int Player::getScore() { return score; }

 int Player::getLife() { return life; }

 int Player::getBomb() { return bomb; }

 void Player::setInitPlayer(int x, int y, int lifeNum, int bombNum) {
	posX = x;
	posY = y;
	life = lifeNum;
	bomb = bombNum;
	score = 0;
	BulletCnt = 0;
}

 void Player::updateMap(CDC *pDC) {
	 CPngImage image;
	 CBitmap bitmap;
	 image.Load(IDB_PLAYER,AfxGetInstanceHandle());
	 bitmap.Attach(image.Detach());
	 CDC dcCompatible;
	 dcCompatible.CreateCompatibleDC(pDC);  // 创建与当前DC（pDC）兼容的DC
	 dcCompatible.SelectObject(&bitmap);
	 pDC->AlphaBlend(posY - picWidth / 2,
		 posX - picHeight / 2,
		 picWidth,
		 picHeight,
		 &dcCompatible,
		 0,
		 0,
		 102,
		 126,
		 { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

 void Player::control(char c) {
	const int moveSpeed = 5;
	switch (c) {
	case 'w':posX-= moveSpeed; break;
	case 's':posX+= moveSpeed; break;
	case 'a':posY-= moveSpeed; break;
	case 'd':posY+= moveSpeed; break;
	case 'b':addBomb(); break;
	case '1':weapon = shared_ptr<Weapon>(new Weapon); break;
	case '2':weapon = shared_ptr<Weapon>(new SuperWeapon1()); break;
	case '3':weapon = shared_ptr<Weapon>(new SuperWeapon2()); break;
	default:break;
	}
}

 void Player::checkBorder(int x1, int y1, int x2, int y2) {
	if (posX < x1 + picHeight / 2) posX = x1 + picHeight / 2;
	if (posY < y1 + picWidth / 2) posY = y1 + picWidth / 2;
	if (posX > x2 - picHeight / 2) posX = x2 - picHeight / 2;
	if (posY > y2 - picWidth / 2) posY = y2 - picWidth / 2;
}

 void Player::getDamaged() {
	life--;
}

 bool Player::checkHit(int x, int y, int height, int width) {
	if (abs(x-posX) <= (height + picHeight)/2 && abs(y - posY) <= (width + picWidth) / 2)
		return true;
	return false;
}

 void Player::addBullet() {
	 BulletCnt++;
	 if (BulletCnt >= 10) {
		 BulletCnt = 0;
		 weapon->bulletAddTo(bulletArray, posX - picHeight / 2, posY);
	 }
}

 void Player::addBomb() {
	if (bomb <= 0)
		return;
	bomb--;
	for (int i = 1; i < PLAY_WIDTH - 3; i+=10) {
		bulletArray.push_back(Bullet(posX - 1, i, 2));
	}
}

 void Player::updateBullet(list<shared_ptr<Enermy>>& enermyArray) {
	for_each(bulletArray.begin(), bulletArray.end(), [](Bullet& b)->void {
		b.move();
	});
	for (list<Bullet>::iterator it = bulletArray.begin(); it != bulletArray.end();) {
		if (it->checkBorder(1, 2, PLAY_HEIGHT - 3, PLAY_WIDTH - 3))
			it++;
		else
			it = bulletArray.erase(it);
	}
	for (list<shared_ptr<Enermy> >::iterator it2 = enermyArray.begin(); it2 != enermyArray.end();) {
		bool flag = false;
		for (list<Bullet>::iterator it = bulletArray.begin(); it != bulletArray.end();) {
			if ((*it2)->checkHit(it->getX(), it->getY(),it->getPicHeight(),it->getPicWidth())) {
				BossEnermy* be = dynamic_cast<BossEnermy*>(&*(*it2));
				if (be) {
					if (be->getLife() <= 0){
						it2 = enermyArray.erase(it2);
						score += 1000;
					}
				}	
				else {
					score++;
					it2 = enermyArray.erase(it2);
				}
				it = bulletArray.erase(it);
				flag = true;
				break;
			}
			else
				it++;
		}
		if (flag) continue;
		it2++;
	}
}

 void Player::bulletUpdateMap(CDC* pDC) {
	for_each(bulletArray.begin(), bulletArray.end(), [&](Bullet& b)->void {
		b.updateMap(pDC);
	});
}

 void Player::setPosition(int x, int y)
 {
	 posX = x;
	 posY = y;
 }
