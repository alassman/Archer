#include "Archer.h"
#include <vector>
#include <string.h>
#include <iostream>

using namespace std;




int main() {
	Archer robot(0,0,0,0,1,0,300);

	vector<int> Mcommand;
	Mcommand.push_back(-100);
	Mcommand.push_back(100);

	robot.setActuators(Mcommand);









	return 0;
}