#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <unistd.h>
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
	Archer robot(0.1, 14, 1800);

	vector<int> Mcommand(2,0);
	Mcommand[0] = 80;
	Mcommand[1] = 80;

	for (int i = 0; i < 100; ++i)
	{
		robot.setActuators(Mcommand);
		robot.readSensors();
	}

	cout << "done" << endl;




	return 0;
}