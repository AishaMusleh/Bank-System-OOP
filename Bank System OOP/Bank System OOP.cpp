#include <iostream>
#include "clsLoginScreen.h"
#include "Global.h"

using namespace std;

int main()
{
	while (true) {
		if (!clsLoginScreen::LoginScreen())
			break;
	}
}
