#pragma once
#include<Windows.h>

enum class EViewType{MENU_VIEW, SCENE_VIEW, INTRO_VIEW, EXIT};
enum class EFrameType{DOUBLE, SINGLE};
enum class EMenuScroll{UP, DOWN};
enum class EAlignment{CENTER, LEFT};


struct NEXT_VIEW_INFO {
	EViewType mViewType;
};

