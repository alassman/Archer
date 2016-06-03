#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "Archer.h"

using namespace std;



int main() {
	//Archer(float period, float track, float encoderScaleFactor);
	Archer robot(10, 2, 300);
	vector<int> Mcommand;
	Mcommand.push_back(-100);
	Mcommand.push_back(100);


	for (int i = 0; i < 100; ++i)
	{
		robot.setActuators(Mcommand);
			robot.readSensors();


	}





	return 0;
}