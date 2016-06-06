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
	Archer robot(10, 14, 1800);

	vector<int> Mcommand(2,0);
	Mcommand[0] = 75;
	Mcommand[1] = 75;

	for (int i = 0; i < 40; ++i)
	{
		robot.setActuators(Mcommand);
	}




	return 0;
}