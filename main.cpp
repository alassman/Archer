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
	//Only one robot can be created at the time
	Archer ROBOT(PERIOD, TRACK, ENCODER_SCALE_FACTOR); //Odometry only

	//Read sensors
	ROBOT.readSensors();
	//Execute the instructions
	float speed = 60;
	float rate = 10;
	ROBOT.setActuators(speed,rate);
	



	return 0;
}
