#pragma once
#include<Windows.h>

enum class EDirection { UP, DOWN, LEFT, RIGHT };
enum class EThingType {THING_1, THING_2, THING_3};
enum class EExchangeType {MONEY, THING, NOTHING, ESCAPE};

struct LOCATION_INFO {
	SHORT sObject;
	SHORT sAttr;
	bool  bObstacle;
	SHORT sPenalty;
};

struct EXCHANGE_RECORD {
	EExchangeType ExchangeType;
	union {
		SHORT MoneyAmount;
		EThingType ThingType;
	} Exchange;
};