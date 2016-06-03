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
	Archer robot(10, 14, 142);
	vector<int> Mcommand(2,0);
	Mcommand[0] = 100;
	Mcommand[1] = 100;

	float total_disp = 0;


	for (int i = 0; i < 40; ++i)
	{
		robot.setActuators(Mcommand);
		total_disp += robot.readSensors();
	}

	Mcommand[0] = 0;
	Mcommand[1] = 0;

	for (int i = 0; i < 100; ++i)
	{
		robot.setActuators(Mcommand);
		total_disp += robot.readSensors();
	}


	cout << "total displacement: " << total_disp << endl;


	return 0;
}