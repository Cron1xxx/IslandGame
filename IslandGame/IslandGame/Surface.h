#pragma once
#include <Windows.h>

class CSurface {
public:
	CSurface(SIZE size);
	~CSurface();
	void print();
	void fill(char ch);
	void drawRect(_RECTL);
private:
	SIZE mSize;
	char **mSurface;
};

