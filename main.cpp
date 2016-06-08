#include "Archer.h"
#include "MathFunctions.h"
#include <vector>
#include <iostream>

using namespace std;

//Platform measurements
const float TRACK = 347.0; // [mm]
const int COUNTS_REVOLUTION = 568; // [count/rev] (71*8)
const float WHEEL_DIAMETER = 155; // [mm]
const float ENCODER_SCALE_FACTOR = PI * WHEEL_DIAMETER / COUNTS_REVOLUTION; // [mm/count]

//factor difference between reported RPM from MC and actual rpm
const int MAX_COMMAND_SPEED = 75; // [rot/min]

// Runtime constant
const float PERIOD = 0.1; // [sec]


int main()
{
	vector<int> robotInfo(3);
	robotInfo[0] = MAX_COMMAND_SPEED;
	robotInfo[1] = COUNTS_REVOLUTION;
	robotInfo[2] = PI * WHEEL_DIAMETER;
	//Only one robot can be created at the time
	Archer device(PERIOD, TRACK, ENCODER_SCALE_FACTOR, robotInfo); //Odometry only

	//Read sensors
	device.readSensors();
	//Execute the instructions
	float speed = 500; // [mm/sec]
	float rate = math_functions::deg2rad(10.0);
	for (int i = 0; i < 100; ++i)
	{
		device.setActuators(speed,rate);
	}
	



	return 0;
}
