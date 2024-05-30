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

enum class EExchangeType { MONEY, THING, NOTHING, ESCAPE, RELOCATION };

struct EXCHANGE_RECORD {
	EExchangeType ExchangeType;
	union {
		SHORT MoneyAmount;
		CThing* Thing;
		COORD RelocationCoord;
	} Exchange;
	
	bool operator == (const EXCHANGE_RECORD& s) {
		if (ExchangeType == s.ExchangeType) {
			if (ExchangeType == EExchangeType::NOTHING || ExchangeType == EExchangeType::ESCAPE) {
				return true;
			} else {
				if (ExchangeType == EExchangeType::MONEY && Exchange.MoneyAmount == s.Exchange.MoneyAmount) {
					return true;
				} else if (ExchangeType == EExchangeType::THING && Exchange.Thing == s.Exchange.Thing) {
					return true;
				} else if (ExchangeType == EExchangeType::RELOCATION 
							&& Exchange.RelocationCoord.Y == s.Exchange.RelocationCoord.Y 
							&& Exchange.RelocationCoord.X == s.Exchange.RelocationCoord.X) {
					return true;
				}
			}
		} 
		return false;
	}
};