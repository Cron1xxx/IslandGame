#pragma once
#include<Windows.h>

enum class EViewType{MENU_VIEW, SCENE_VIEW, EXIT};
enum class EFrameType{DOUBLE, SINGLE};
enum class EMenuScroll{UP, DOWN};
enum class EAlignment{CENTER, LEFT};
enum class EDirection{UP, DOWN, LEFT, RIGHT};


struct LOCATION_INFO {
	SHORT sObject;
	SHORT sAttr;
	bool  bObstacle; 
	SHORT sPenalty;
};

struct NEXT_VIEW_INFO {
	EViewType mViewType;
};

