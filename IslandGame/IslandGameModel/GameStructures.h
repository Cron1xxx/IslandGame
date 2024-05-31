#pragma once
#include<Windows.h>
#include"Thing.h"

enum class EDirection { UP, DOWN, LEFT, RIGHT };

struct LOCATION_INFO {
	SHORT sObject;
	SHORT sAttr;
	bool  bObstacle;
	SHORT sPenalty;
};

enum class EExchangeType { MONEY, THING, NOTHING, ESCAPE, RELOCATION, HEALTH };

struct EXCHANGE_RECORD {
	EExchangeType ExchangeType;
	union {
		SHORT MoneyAmount;
		CThing* Thing;
		COORD RelocationCoord;
		SHORT Health;
	} Exchange;
};