#pragma once
#include <atlstr.h>

class CThing {
public:
	CString mName;
	CString mDescription;

	CThing(CString name, CString description) {
		mName = name;
		mDescription = description;
	}

	bool operator == (const CThing& t) {
		if (mName == t.mName) {
			return true;
		} else {
			return false;
		}
	}
};