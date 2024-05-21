#pragma once

enum class EViewType{MENU_VIEW, SCENE_VIEW, EXIT};
enum class EFrameType{DOUBLE, SINGLE};
enum class EMenuScroll{UP, DOWN};
enum class EAlignment{CENTER, LEFT};
enum class EDirection{UP, DOWN, LEFT, RIGHT};



struct NEXT_VIEW_INFO {
	EViewType mViewType;
};

