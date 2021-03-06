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

Archer::Archer(float period, float track, float encoderScaleFactor, vector<int> robotInfo) 
	:Robot(period, track, encoderScaleFactor)
{
	MAX_COMMAND_SPEED = robotInfo[0]; // [rot/min]
	COUNTS_REVOLUTION = robotInfo[1]; // [counts/rev]
	CIRCUMFERENCE = robotInfo[2]; // [MM]

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

void Archer::setActuators(vector<int> &MotorSpeed) {
	//assuming MotorSpeed is an array of size two
	//first value is speed of left_motor in [mm/sec]
	//second value is speed of right_motor in [mm/sec]

	cout << "MotorSpeed received: " << MotorSpeed[LEFT] << " / " << MotorSpeed[RIGHT] << endl;

	//convert from [mm/sec] to [rot/min]
	MotorSpeed[LEFT] *= 60 / CIRCUMFERENCE;
	MotorSpeed[RIGHT] *= 60 / CIRCUMFERENCE;

	cout << "MotorSpeed in rpm: " << MotorSpeed[LEFT] << " / " << MotorSpeed[RIGHT] << endl;

	if(MotorSpeed[LEFT] > MAX_COMMAND_SPEED) {
		MotorSpeed[LEFT] = MAX_COMMAND_SPEED;
	}
	if(MotorSpeed[RIGHT] > MAX_COMMAND_SPEED) {
		MotorSpeed[RIGHT] = MAX_COMMAND_SPEED;
	}

	bool stop = false;
	if(MotorSpeed[LEFT] == 0 && MotorSpeed[RIGHT] == 0) {
		device.SetCommand(_EX);
		stop = true;
	}
	
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

	//cout << "ARCHER SET SPEED: " << MotorSpeed[LEFT] << " " << MotorSpeed[RIGHT] << endl;

	if(stop) {
		device.SetCommand(_MG);
	}
	checkTimming();
}

void Archer::setActuators(float speed, float rate)
{
	int counts_sec_aux[2];
	cout << "about to run speedRate2Counts()..." << endl;
	speedRate2Counts(speed, rate, counts_sec_aux);
	cout <<  endl << "finished speedRate2Counts()..." << endl;
	std::vector<int> counts_sec;
	counts_sec.push_back(counts_sec_aux[0]);
	counts_sec.push_back(counts_sec_aux[1]);

	cout << endl << "counts_sec: " << counts_sec_aux[0] << " / " << counts_sec_aux[1] << endl;


	//NEED TO CONVERT FROM COUNTS/SECOND TO RPM

	// Make sure that if not zero, it sets some speed
	if(!counts_sec[0] && counts_sec_aux[0]) counts_sec[0] = (counts_sec_aux[0] > 0) ? 1 : -1;
	if(!counts_sec[1] && counts_sec_aux[1]) counts_sec[1] = (counts_sec_aux[1] > 0) ? 1 : -1;

	//convert from counts/sec to mm/sec
	counts_sec[0] *= mEncoderScaleFactor;
	counts_sec[1] *= mEncoderScaleFactor; 

	//Send motor commands
	setActuators(counts_sec);
	//cout << "ARCHER SPEED RATE: " << speed << " " << math_functions::rad2deg(rate) << endl;
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

