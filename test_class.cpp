#include "Archer.h"
#include "MathFunctions.h"
#include <vector>

using namespace std;

//Platform measurements
const float TRACK = 110.0; // [mm]
const int COUNTS_REVOLUTION = 2000; // [count/rev]
const float WHEEL_DIAMETER = 150; // [mm]
const float ENCODER_SCALE_FACTOR = PI * WHEEL_DIAMETER / COUNTS_REVOLUTION; // [mm/count]

//factor difference between reported RPM from MC and actual rpm
const float SPEED_FACTOR = 1.885; // [rpm]
const int MAX_ACTUAL_SPEED = 40; // [rot/min]
const int MAX_COMMAND_SPEED = 75; // [rot/min]

// Runtime constant
const float PERIOD = 0.1; // [sec]


int main()
{
	//Only one robot can be created at the time
	Archer robot(PERIOD, TRACK, ENCODER_SCALE_FACTOR); //Odometry only

	//Read sensors
	robot.readSensors();

	//Execute the instructions
	vector<int> command(2,75);
	for(int i = 0; i < 100; ++i) {
		robot.setActuators(command);
		if(i%2) {
			robot.readSensors();
		}
	}

	return 0;
}
