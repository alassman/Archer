#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "Archer.h"

using namespace std;



int main() {
/*
	//Archer(float period, float track, float encoderScaleFactor);
	track = 14", 35.5cm
	gear ratio = 1:71
		4*71 = 284
	period = 10hz
*/
	Archer robot(10, 14, 284);
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