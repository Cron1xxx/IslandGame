#pragma once
#include<string>
#include"Structures.h"

class IView {
public:
	virtual NEXT_VIEW_INFO show() = 0;
};

