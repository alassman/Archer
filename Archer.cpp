#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cmath>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <cassert>
#include "Archer.h"

#define _USE_MATH_DEFINES

using namespace std;

//period is how often to read sensors
//distance/tick
//multiply 2 or 4 by gear ratio for encoder scale factor
//track=distance between two wheels

Archer::Archer(float period, float track, float encoderScaleFactor) 
	:Robot(period, track, encoderScaleFactor)
{
	//set motor left and right
	motor1 = 1;
	motor2 = 2;
	//establish connection with SDC21XX
	int status = device.Connect("/dev/ttyACM0");
	for(int i = 0; i < 3; ++i) {
		if(status != RQ_SUCCESS)
		{
			cout<<"Error connecting to device: "<<status<<"."<<endl;
			cout << "Trying again..." << endl;
			status = device.Connect("/dev/ttyACM0");
		}
		else
			break;
	}

	wheel_circumference = 50.265;



/*

	//set encoder from mot1 as feedback for channel1
	cout<<"- SetConfig(_EMOD, motor1, 18)...";
	if((status = device.SetConfig(_EMOD, motor1, 18)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	//Wait 10 ms before sending another command to device
	sleepms(10);

	//set encoder from mot2 as feedback for channel 2
	cout<<"- SetConfig(_EMOD, motor2, 34)...";
	if((status = device.SetConfig(_EMOD, motor2, 34)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	//Wait 10 ms before sending another command to device
	sleepms(10);

	//set encoder pulses per rotation from input
	cout<<"- SetConfig(_EPPR, motor1, encoderScaleFactor)...";
	if((status = device.SetConfig(_EPPR, motor1, encoderScaleFactor)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	sleepms(10);

	//set encoder from mot1 as feedback for channel1
	cout<<"- SetConfig(_EPPR, motor2, encoderScaleFactor)...";
	if((status = device.SetConfig(_EPPR, motor2, encoderScaleFactor)) != RQ_SUCCESS)
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
	cout<<"- SetConfig(_MMOD, motor1, 1)...";
	if((status = device.SetConfig(_MMOD, motor1, 1)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	//set channel 1 as closed loop speed mode
	cout<<"- SetConfig(_MMOD, motor2, 1)...";
	if((status = device.SetConfig(_MMOD, motor2, 1)) != RQ_SUCCESS)
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
	cout<<"- SetConfig(_CLERD, motor1, 0)...";
	if((status = device.SetConfig(_CLERD, motor1, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	cout<<"- SetConfig(_CLERD, motor2, 0)...";
	if((status = device.SetConfig(_CLERD, motor2, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
*/
/*

	//set Differential Gain
	cout<<"- SetConfig(_KD, motor1, differential_gain)...";
	if((status = device.SetConfig(_KD, motor1, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	cout<<"- SetConfig(_KD, motor2, differential_gain)...";
	if((status = device.SetConfig(_KD, motor2, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	sleepms(10);

	//set integral Gain
	cout<<"- SetConfig(_KI, motor1, integral_gain)...";
	if((status = device.SetConfig(_KI, motor1, 1)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	cout<<"- SetConfig(_KI, motor2, integral_gain)...";
	if((status = device.SetConfig(_KI, motor2, 1)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	sleepms(10);

	//set proportional gain
	cout<<"- SetConfig(_KP, motor1, proportional_gain)...";
	if((status = device.SetConfig(_KI, motor1, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	cout<<"- SetConfig(_KP, motor2, proportional_gain)...";
	if((status = device.SetConfig(_KI, motor2, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	*/

	cout << "Archer Robot ready!\n";
}

Archer::~Archer() {
	device.Disconnect();
}
void Archer::setActuators(vector<int> MotorSpeed) {
	assert(MotorSpeed.size() == 2 && "MotorSpeed vector malformed");
/* Question
is this the structure of the array you're looking for?
what array of chars and not ints?
*/
	//SetCommand(int commandItem, int index, int value)
	//assuming pmotorSpeed is an array of size two
	//first value is speed of motor1
	//second value is speed of motor2

	int status;
	if((status = device.SetCommand(_S, motor1, MotorSpeed[0])) != RQ_SUCCESS) {
		cout<<"motor1 speed_set failed with exit status: " << status;
		exit(1);
	}
	if((status = device.SetCommand(_S, motor2, MotorSpeed[1])) != RQ_SUCCESS) {
		cout<<"motor2 speed_set failed with exit status: " << status;
		exit(1);
	}
}

void Archer::setActuators(float speed, float rate)
{
	int counts_sec_aux[2];
	speedRate2Counts(speed, rate, counts_sec_aux);

	std::vector<int> counts_sec;
	counts_sec.push_back(counts_sec_aux[0]);
	counts_sec.push_back(counts_sec_aux[1]);	

	// Make sure that if not zero, it sets some speed
	if(!counts_sec[0] && counts_sec_aux[0]) counts_sec[0] = (counts_sec_aux[0] > 0) ? 1 : -1;
	if(!counts_sec[1] && counts_sec_aux[1]) counts_sec[1] = (counts_sec_aux[1] > 0) ? 1 : -1;

	//Send motor commands
	setActuators(counts_sec);
	cout << "EV3 SPEED RATE: " << speed << " " << rate*180/M_PI << endl;
}

//no sleep time in code
//reduciton ratio 1:71
int Archer::readSensors()
{
	// Get robot displacement from encoders
	int rel_count_1;
	int rel_count_2;
	int status;

	if((status = device.GetValue(_CR, motor1, rel_count_1)) != RQ_SUCCESS) {
		cout <<"motor1 encoder reading failed with exit status: " << status << endl;
		exit(1);
	}
	if((status = device.GetValue(_CR, motor2, rel_count_2)) != RQ_SUCCESS) {
		cout <<"motor2 encoder reading failed with exit status: " << status << endl;
		exit(1);
	}

	//Compute wheel linear displacements
	mDisplacementLeft = (rel_count_1/mEncoderScaleFactor) * wheel_circumference;


	cout << "(rel_count_1/mEncoderScaleFactor) * wheel_circumference: " << (rel_count_1/mEncoderScaleFactor) * wheel_circumference << endl; 



	mDisplacementRight = (rel_count_2/mEncoderScaleFactor) * wheel_circumference;
	
	//Compute robot average displacement and rotation
	mDisplacement = (mDisplacementLeft + mDisplacementRight) / 2.0;


	cout << "mDisplacement: " << mDisplacement << endl;



/* question
what is mTrack?
*/
	mRotation = (mDisplacementRight - mDisplacementLeft) / mTrack;

/* Question
what is mPeriod?
*/
	
	//cout << "Archer ACTUAL SPEED: " << " " << mDisplacementLeft/mEncoderScaleFactor/mPeriod << " " << mDisplacementRight/mEncoderScaleFactor/mPeriod << " " << mDisplacement << " " << (mRotation*180)/M_PI << endl;
	//return DATA_READY;
	return mDisplacement;
}
