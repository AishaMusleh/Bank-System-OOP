#pragma once
#include "clsUtil.h"
#include "clsDate.h"
#include "clsBankUser.h"
#include "Global.h"

class clsScreen
{
protected:
	static void _DrawScreenHeader(string Title, string SubTitle = "") {
		clsUtil::Tabs(4);
		cout << "---------------------------------------------------------------\n";
		clsUtil::Tabs(7);
		cout << Title << "\n";
		if (SubTitle != "")
		{
			cout << "\n";
			clsUtil::Tabs(7);
			cout << SubTitle << "\n";
		}
		clsUtil::Tabs(4);
		cout << "---------------------------------------------------------------\n\n";

		clsUtil::Tabs(4);
		cout << "User: " << CurrentUser.UserName << endl;
		clsUtil::Tabs(4);
		cout << "Date: " << clsDate::DateToString(clsDate()) << "\n\n";
	}

	static bool _GetAccessRight(clsBankUser::enPermission Permission) {
		if (!CurrentUser.CheakAccessPermission(Permission)) {
			_DrawScreenHeader("Access Denied", "Contact your admin.");
			return false;
		}
		else {
			return true;
		}
	}
};

