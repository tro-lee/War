#pragma warning(disable : 4996)
#include "pch.h"
#include "Admin.h"
#include "AnyThing.h"
#include <vector>

CString Admin::saveAnyThing(AnyThing a) {
	CString c;
	c.Format("%d %d %d %d %d", a.GetPosX(), a.GetPosY(), a.GetSpeedX(),
		a.GetSpeedY(), a.uid);
	return c;
}

void Admin::save(CMyRole a)
{
	//XY ËÙ¶ÈXY ¾ØÐÎXYXY Í¼Æ¬ uid
	CFile file;
	file.Open("./me.txt", CFile::modeCreate | CFile::modeWrite, NULL);

	CString c = saveAnyThing(a);

	file.Write(c, c.GetLength());
	file.Close();
}

void Admin::load(CMyRole &a)
{
	CFileFind finder;
	BOOL bWorking = (bool)finder.FindFile("./me.txt");
	if (!bWorking) {
		CFile file;
		file.Open("./me.txt", CFile::modeCreate | CFile::modeWrite, NULL);
		CString c = "625 800 0 0 133";
		file.Write(c, c.GetLength());
		file.Close();
	}

	CFile file;
	file.Open("./me.txt", CFile::modeReadWrite, NULL);
	int len = file.GetLength();
	char* b1 = new char[len + 1];
	file.Read(b1, len);
	file.Close();
	
	CString strSrc = b1;
	CString strTmp;
	std::vector<CString> vecString;
	int n = -1;
	n = strSrc.Find(' ');
	while (n != -1)
	{
		strTmp = strSrc.Left(n);
		vecString.push_back(strTmp);
		strSrc = strSrc.Right(strSrc.GetLength() - n - 1);
		n = strSrc.Find(' ');
	}
	a.setPosX(_ttoi(_T(vecString[0])));
	a.setPosY(_ttoi(_T(vecString[1])));
}

void Admin::save(std::vector<CEnemy> a)
{
	CFile file;
	file.Open("./enemy.txt", CFile::modeCreate | CFile::modeWrite, NULL);

	CString c;

	for (size_t i = 0; i < a.size(); i++)
	{
		CString b;
		b.Format("%dA%dA%dA%dA%dA%dA%dA%dA%dA%dB", i, a[i].GetPosX(), a[i].GetPosY(), a[i].GetSpeedX(), a[i].GetSpeedY(), a[i].uid, a[i].hp, a[i].size, a[i].credit, a[i].boss);
		c = c + b;
	}

	file.Write(c, c.GetLength());
	file.Close();
}

void Admin::load(std::vector<CEnemy>& a)
{
	CFile file;
	file.Open("./enemy.txt", CFile::modeReadWrite, NULL);
	int len = file.GetLength();
	char* b1 = new char[len + 1];
	file.Read(b1, file.GetLength());
	file.Close();
	
	CString strSrc = b1;
	CString strTmp;
	std::vector<CString> vecString;

	int n = -1;
	int i = 0;
	n = strSrc.Find('A');
	int step = 0;
	while (n != -1 && step != len + 1)
	{
		strTmp = strSrc.Left(n);
		vecString.push_back(strTmp);
		strSrc = strSrc.Right(strSrc.GetLength() - n - 1);
		n = strSrc.Find('A');

		if (strSrc[1] == 'B') {
			a[i].Init(_ttoi(_T(vecString[5])), _ttoi(_T(vecString[3])), _ttoi(_T(vecString[4])), _ttoi(_T(vecString[6])), _ttoi(_T(vecString[7])), _ttoi(_T(vecString[8])), false, _ttoi(_T(vecString[1])), _ttoi(_T(vecString[2])));
			
			vecString.clear();
			strSrc = strSrc.Right(strSrc.GetLength());
			i++;
		}

		step++;
	}
}

int Admin::loadEnemy() {
	CFileFind finder;
	BOOL bWorking = (bool)finder.FindFile("./enemy.txt");
	if (!bWorking) {
		CFile file;
		file.Open("./enemy.txt", CFile::modeCreate | CFile::modeWrite, NULL);
		CString c = "";
		file.Write(c, c.GetLength());
		file.Close();
	}

	CFile file;
	file.Open("./enemy.txt", CFile::modeReadWrite, NULL);
	int len = file.GetLength();
	char* b1 = new char[len + 1];
	file.Read(b1, file.GetLength());
	file.Close();

	CString strSrc = b1;
	int n = -1;
	int i = 0;
	n = strSrc.Find('A');
	while (n != -1)
	{
		strSrc = strSrc.Right(strSrc.GetLength() - n - 1);
		n = strSrc.Find('A');
		if(strSrc[1] == 'B')
		i++;
	}

	int p = sizeof(b1);
	b1 = NULL;
	delete b1;
	return i;
}

void Admin::save(int credits, int level) {
	CFile file;
	file.Open("./others.txt", CFile::modeCreate | CFile::modeWrite, NULL);
	CString c;
	c.Format("%d %d", credits, level);

	file.Write(c, c.GetLength());
	file.Close();
}

void Admin::load(int &credits, int &level)
{
	CFileFind finder;
	BOOL bWorking = (bool)finder.FindFile("./others.txt");
	if (!bWorking) {
		CFile file;
		file.Open("./others.txt", CFile::modeCreate | CFile::modeWrite, NULL);
		CString c = "0 1";
		file.Write(c, c.GetLength());
		file.Close();
	}

	CFile file;
	file.Open("./others.txt", CFile::modeReadWrite, NULL);
	int len = file.GetLength();
	char* b1 = new char[len + 1];
	file.Read(b1, file.GetLength());
	file.Close();

	CString strSrc = b1;
	CString strTmp;
	std::vector<CString> vecString;

	int n = strSrc.Find(' ');
	strTmp = strSrc.Left(n);
	credits = _ttoi(_T(strTmp));
	level = _ttoi(_T(strSrc.Right(strSrc.GetLength() - n - 1)));
}
