#pragma once
#include<Windows.h>

enum class EDirection { UP, DOWN, LEFT, RIGHT };


struct LOCATION_INFO {
	SHORT sObject;
	SHORT sAttr;
	bool  bObstacle;
	SHORT sPenalty;
};