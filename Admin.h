#pragma once
#include "CMyRole.h"
#include "Bullet.h"
#include "Boom.h"
#include "CEnemy.h"
#include <vector>
class Admin
{
public:
	CString saveAnyThing(AnyThing a);
	void save(int credits, int level);
	void load(int& credits, int& level);
	void save(CMyRole a);
	void save(std::vector<CEnemy> a);
	void load(CMyRole &a);
	void load(std::vector<CEnemy>& a);
	int  loadEnemy();
};

