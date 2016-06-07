#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cmath>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <cassert>
#include "Archer.h"
#include "MathFunctions.h"

using namespace std;

//period is how often to read sensors
//distance/tick
//multiply 2 or 4 by gear ratio for encoder scale factor
//track=distance between two wheels

Archer::Archer(float period, float track, float encoderScaleFactor) 
	:Robot(period, track, encoderScaleFactor)
{
	SPEED_FACTOR = 1.885; // [rpm]
	MAX_ACTUAL_SPEED = 40; // [rot/min]
	MAX_COMMAND_SPEED = 75; // [rot/min]
	counts_revolution = 2000; // [counts/rev]

	//set motor left_motor and right_motor
	left_motor = 1;
	right_motor= 2;
	//Set index
	LEFT = 0;
	RIGHT = 1;
	//establish connection with SDC21XX
	int status = device.Connect("/dev/ttyACM0");
	for(int i = 0; i < 10; ++i) {
		if(status != RQ_SUCCESS)
		{
			cout<<"Error connecting to device: "<<status<<"."<<endl;
			cout << "Trying again..." << endl;
			status = device.Connect("/dev/ttyACM0");
		}
		else
			break;
	}

	strcpy(mName, "Archer");
	//to initialize encoder readings because each read is relative to the last read
	readSensors();
	cout << "Archer is ready!\n";
	



/*

	//set encoder from mot1 as feedback for channel1
	cout<<"- SetConfig(_EMOD, left_motor, 18)...";
	if((status = device.SetConfig(_EMOD, left_motor, 18)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	//Wait 10 ms before sending another command to device
	sleepms(10);

	//set encoder from mot2 as feedback for channel 2
	cout<<"- SetConfig(_EMOD, right_motor, 34)...";
	if((status = device.SetConfig(_EMOD, right_motor, 34)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	//Wait 10 ms before sending another command to device
	sleepms(10);

	//set encoder pulses per rotation from input
	cout<<"- SetConfig(_EPPR, left_motor, encoderScaleFactor)...";
	if((status = device.SetConfig(_EPPR, left_motor, encoderScaleFactor)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	sleepms(10);

	//set encoder from mot1 as feedback for channel1
	cout<<"- SetConfig(_EPPR, right_motor, encoderScaleFactor)...";
	if((status = device.SetConfig(_EPPR, right_motor, encoderScaleFactor)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

		sleepms(10);
*/

	/*
	CLOSED LOOP PARAMETERS
	*/
		//set operating mode for channel
	/*
	0 : open-loop speed
	1 : closed-loop speed
	2 : closed-loop position relative 3 : closed-loop count position
	4 : closed-loop position tracking 5 : torque
	*/
	//set channel 1 as closed loop speed mode
/*	
	cout<<"- SetConfig(_MMOD, left_motor, 1)...";
	if((status = device.SetConfig(_MMOD, left_motor, 1)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	//set channel 1 as closed loop speed mode
	cout<<"- SetConfig(_MMOD, right_motor, 1)...";
	if((status = device.SetConfig(_MMOD, right_motor, 1)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
*/
	//set closed loop error detection
	/*
	0 : Detection disabled
	1 : 250ms at Error > 100 
	2 : 500ms at Error > 250 
	3 : 1000ms at Error > 500
	*/
/*
	cout<<"- SetConfig(_CLERD, left_motor, 0)...";
	if((status = device.SetConfig(_CLERD, left_motor, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	cout<<"- SetConfig(_CLERD, right_motor, 0)...";
	if((status = device.SetConfig(_CLERD, right_motor, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
*/
/*

	//set Differential Gain
	cout<<"- SetConfig(_KD, left_motor, differential_gain)...";
	if((status = device.SetConfig(_KD, left_motor, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	cout<<"- SetConfig(_KD, right_motor, differential_gain)...";
	if((status = device.SetConfig(_KD, right_motor, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	sleepms(10);

	//set integral Gain
	cout<<"- SetConfig(_KI, left_motor, integral_gain)...";
	if((status = device.SetConfig(_KI, left_motor, 1)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	cout<<"- SetConfig(_KI, right_motor, integral_gain)...";
	if((status = device.SetConfig(_KI, right_motor, 1)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	sleepms(10);

	//set proportional gain
	cout<<"- SetConfig(_KP, left_motor, proportional_gain)...";
	if((status = device.SetConfig(_KI, left_motor, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	cout<<"- SetConfig(_KP, right_motor, proportional_gain)...";
	if((status = device.SetConfig(_KI, right_motor, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	*/
}

Archer::~Archer() {
	device.SetCommand(_EX);
	sleepms(10);
	int status;
	//left_motor command
	if((status = device.SetCommand(_S, left_motor, 0)) != RQ_SUCCESS) {
		cout<<"left_motor speed_set failed with exit status: " << status;
		exit(1);
	}
	//right_motorcommand
	if((status = device.SetCommand(_S, right_motor, 0)) != RQ_SUCCESS) {
		cout<<"right_motorspeed_set failed with exit status: " << status;
		exit(1);
	}
	sleepms(10);
	device.SetCommand(_MG);
	sleepms(10);
	device.Disconnect();
	cout << "Archer Robot Closed!\n";
}

//no sleep time in code
//reduciton ratio 1:71
int Archer::readSensors()
{
	// Get robot displacement from encoders
	int rel_count_1;
	int rel_count_2;
	int status;

	if((status = device.GetValue(_CR, left_motor, rel_count_1)) != RQ_SUCCESS) {
		cout <<"left_motor encoder reading failed with exit status: " << status << endl;
		exit(1);
	}
	if((status = device.GetValue(_CR, right_motor, rel_count_2)) != RQ_SUCCESS) {
		cout <<"right_motorencoder reading failed with exit status: " << status << endl;
		exit(1);
	}

	//read RPM values
	//Read RPM value
	int result = -10;
	if((status = device.GetValue(_S, left_motor, result)) != RQ_SUCCESS)
		cout<<"RPM 1 failed --> "<<status<<endl;
	else
		cout<<"motor 1 RPM "<<result<<endl;
	if((status = device.GetValue(_S, right_motor, result)) != RQ_SUCCESS)
		cout<<"RPM 2 failed --> "<<status<<endl;
	else
		cout<<"motor 2 RPM "<<result<<endl;



	//Compute wheel linear displacements
	mDisplacementLeft = rel_count_1 * mEncoderScaleFactor;
	mDisplacementRight= rel_count_2 * mEncoderScaleFactor;
	
	//Compute robot average displacement and rotation
	mDisplacement = (mDisplacementLeft + mDisplacementRight) / 2.0;
	mRotation = (mDisplacementRight - mDisplacementLeft) / mTrack;
	



	cout << "ARCHER ACTUAL SPEED: " << " " << mDisplacementLeft/mEncoderScaleFactor/mPeriod << " " << mDisplacementRight/mEncoderScaleFactor/mPeriod << " " << mDisplacement << " " << math_functions::rad2deg(mRotation) << endl;
	return DATA_READY;
}

void Archer::setActuators(vector<int> MotorSpeed) {
	assert(MotorSpeed.size() == 2 && "MotorSpeed vector malformed");
	//SetCommand(int commandItem, int index, int value)
	//assuming pmotorSpeed is an array of size two
	//first value is speed of left_motor
	//second value is speed of right_motor

	MotorSpeed[LEFT] *= SPEED_FACTOR;
	MotorSpeed[RIGHT] *= SPEED_FACTOR;

	if(MotorSpeed[LEFT] > MAX_COMMAND_SPEED || MotorSpeed[RIGHT] > MAX_COMMAND_SPEED) {
		MotorSpeed[LEFT] = MAX_COMMAND_SPEED;
		MotorSpeed[RIGHT] = MAX_COMMAND_SPEED;
	}


	if(MotorSpeed[LEFT] == 0 && MotorSpeed[RIGHT] == 0) {
		device.SetCommand(_EX);
		setActuators(MotorSpeed);
		device.SetCommand(_MG);
	}
	else {
		int status;
		//left_motor command
		if((status = device.SetCommand(_S, left_motor, MotorSpeed[LEFT])) != RQ_SUCCESS) {
			cout<<"left_motor speed_set failed with exit status: " << status;
			exit(1);
		}
		//right_motorcommand
		if((status = device.SetCommand(_S, right_motor, MotorSpeed[RIGHT])) != RQ_SUCCESS) {
			cout<<"right_motorspeed_set failed with exit status: " << status;
			exit(1);
		}

		cout << "ARCHER SET SPEED: " << MotorSpeed[LEFT] << " " << MotorSpeed[RIGHT] << endl;
	}
	checkTimming();
}

void Archer::setActuators(float speed, float rate)
{
	int counts_sec_aux[2];
	speedRate2Counts(speed, rate, counts_sec_aux);

	std::vector<int> counts_sec;
	counts_sec.push_back(counts_sec_aux[0]);
	counts_sec.push_back(counts_sec_aux[1]);	

	//NEED TO CONVERT FROM COUNTS/SECOND TO RPM

	// Make sure that if not zero, it sets some speed
	if(!counts_sec[0] && counts_sec_aux[0]) counts_sec[0] = (counts_sec_aux[0] > 0) ? 1 : -1;
	if(!counts_sec[1] && counts_sec_aux[1]) counts_sec[1] = (counts_sec_aux[1] > 0) ? 1 : -1;

	//convert from counts/sec to rpm
	counts_sec[0] = 1/counts_revolution * 60;
	counts_sec[1] = 1/counts_revolution * 60; 

	//Send motor commands
	setActuators(counts_sec);
	cout << "ARCHER SPEED RATE: " << speed << " " << math_functions::rad2deg(rate) << endl;
}

int Archer::read_encoders() {
	int rel_count_1;
	int status;

	if((status = device.GetValue(_CR, left_motor, rel_count_1)) != RQ_SUCCESS) {
		cout <<"left_motor encoder reading failed with exit status: " << status << endl;
		exit(1);
	}
	

	return rel_count_1;
}

