#include "NavigationRobot.h"

int main() {
	Space a('A', 1);
	Space b('A', 3);
	NavigationRobot r(a, b, "left");
	r.traverse();
	
	return 0;
}