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


	robot.read_encoders();
	cout << robot.read_encoders() << endl;

	sleep(10);

	cout << robot.read_encoders() << endl;





/*
	vector<int> Mcommand(2,0);
	Mcommand[0] = 100;
	Mcommand[1] = 100;

	double total_disp = 0;
	robot.readSensors();

	for (int i = 0; i < 40; ++i)
	{
		robot.setActuators(Mcommand);
		total_disp += robot.readSensors();
		cout << total_disp << endl;
	}

	Mcommand[0] = 0;
	Mcommand[1] = 0;

	for (int i = 0; i < 150; ++i)
	{
		robot.setActuators(Mcommand);
		total_disp += robot.readSensors();
		cout << total_disp << endl;

	}


	cout << "total displacement: " << total_disp << endl;
*/


	return 0;
}