#include <iostream>
#include <cstring>
#include <cmath>
#include <fcntl.h>
#include <unistd.h>
#include "Archer.h"

using namespace std;

Archer::Archer(float period, float track, float encoderScaleFactor, 
	float proportional_gain, float integral_gain, float differential_gain, 
	float ppr) : Robot(period, track, encoderScaleFactor)
{
	//set motor left and right
	Lmotor = 1;
	Rmotor = 2;
	//establish connection with SDC21XX
	int status = device.Connect("/dev/ttyACM0");
	if(status != RQ_SUCCESS)
	{
		cout<<"Error connecting to device: "<<status<<"."<<endl;
		return 1;
	}
	//set encoder from mot1 as feedback for channel1
	cout<<"- SetConfig(_EMOD, Lmotor, 18)...";
	if((status = device.SetConfig(_EMOD, Lmotor, 18)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	//Wait 10 ms before sending another command to device
	sleepms(10);

	//set encoder from mot2 as feedback for channel 2
	cout<<"- SetConfig(_EMOD, Rmotor, 34)...";
	if((status = device.SetConfig(_EMOD, Rmotor, 34)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	//Wait 10 ms before sending another command to device
	sleepms(10);

	//set encoder pulses per rotation from input
	cout<<"- SetConfig(_EPPR, Lmotor, ppr)...";
	if((status = device.SetConfig(_EPPR, Lmotor, ppr)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	sleepms(10);

	//set encoder from mot1 as feedback for channel1
	cout<<"- SetConfig(_EPPR, Rmotor, ppr)...";
	if((status = device.SetConfig(_EPPR, Rmotor, ppr)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

		sleepms(10);

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
	cout<<"- SetConfig(_MMOD, Lmotor, 1)...";
	if((status = device.SetConfig(_MMOD, Lmotor, 1)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	//set channel 1 as closed loop speed mode
	cout<<"- SetConfig(_MMOD, Rmotor, 1)...";
	if((status = device.SetConfig(_MMOD, Rmotor, 1)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);

	//set closed loop error detection
	/*
	0 : Detection disabled
	1 : 250ms at Error > 100 
	2 : 500ms at Error > 250 
	3 : 1000ms at Error > 500
	*/
	cout<<"- SetConfig(_CLERD, Lmotor, 0)...";
	if((status = device.SetConfig(_CLERD, Lmotor, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	cout<<"- SetConfig(_CLERD, Rmotor, 0)...";
	if((status = device.SetConfig(_CLERD, Rmotor, 0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);


	//set Differential Gain
	cout<<"- SetConfig(_KD, Lmotor, dg)...";
	if((status = device.SetConfig(_KD, Lmotor, differential_gain)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	cout<<"- SetConfig(_KD, Rmotor, dg)...";
	if((status = device.SetConfig(_KD, Rmotor, differential_gain)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	sleepms(10);

	//set integral Gain
	cout<<"- SetConfig(_KI, Lmotor, integral_gain)...";
	if((status = device.SetConfig(_KI, Lmotor, integral_gain)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	cout<<"- SetConfig(_KI, Rmotor, integral_gain)...";
	if((status = device.SetConfig(_KI, Rmotor, integral_gain)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	sleepms(10);

	//set proportional gain
	cout<<"- SetConfig(_KP, Lmotor, proportional_gain)...";
	if((status = device.SetConfig(_KI, Lmotor, proportional_gain)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	cout<<"- SetConfig(_KP, Rmotor, proportional_gain)...";
	if((status = device.SetConfig(_KI, Rmotor, proportional_gain)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	cout << "Archer Robot ready!\n";
}

Archer::~Archer() {
	device.Disconnect();
}
void Archer::setActuators(char *pMotorSpeed) {
/* Question
is this the structure of the array you're looking for?
what array of chars and not ints?
*/
	//SetCommand(int commandItem, int index, int value)
	//assuming pmotorSpeed is an array of size two
	//first value is speed of Lmotor
	//second value is speed of Rmotor
	int status;
	if((status = device.SetCommand(_S, Lmotor, *pMotorSpeed)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(10);
	if((status = device.SetCommand(_S, Rmotor, *(pMotorSpeed+1)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleepms(100);
}

void Archer::setActuators(float speed, float rate)
{
/* Question
what is rate in this case? ... units
*/
	//convert speed into RPM
	//assuming 4 rotations = 1m
	//m/s * rot/m * s/minute = rot/minute
	float rpm = speed * 4 * 60;

	char pMotorSpeed[2];
	pMotorSpeed[0] = rpm;
	pMotorSpeed[1] = rpm;

	//Send motor commands
	setActuators(pMotorSpeed);
	cout << "Archer SPEED RATE: " << speed << " " << math_functions::rad2deg(rate) << endl;
}

int Archer::readSensors()
{
	// Get robot displacement from encoders
	float rel_count_left;
	float rel_count_right;
	cout<<"- GetValue(_CR, Lmotor, rel_count_left)...";
	if((status = device.GetValue(_CR, Lmotor, rel_count_left)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"returned --> "<<result<<endl;
	//Wait 10 ms before sending another command to device
	sleepms(10);
	cout<<"- GetValue(_CR, Rmotor, rel_count_right)...";
	if((status = device.GetValue(_CR, Rmotor, rel_count_right)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"returned --> "<<result<<endl;

	//Compute wheel linear displacements
	mDisplacementLeft = (rel_count_left) * mEncoderScaleFactor;
	mDisplacementRight = (rel_count_right) * mEncoderScaleFactor;
	
	//Compute robot average displacement and rotation
	mDisplacement = (mDisplacementLeft + mDisplacementRight) / 2.0;
/* question
what is mTrack?
*/
	mRotation = (mDisplacementRight - mDisplacementLeft) / mTrack;

	//Store last encoder state
	mLastLeftEncoderCount = new_count_left;
	mLastRightEncoderCount = new_count_right;
/* Question
what is mPeriod?
*/
	
	cout << "Archer ACTUAL SPEED: " << " " << mDisplacementLeft/mEncoderScaleFactor/mPeriod << " " << mDisplacementRight/mEncoderScaleFactor/mPeriod << " " << mDisplacement << " " << math_functions::rad2deg(mRotation) << endl;
	return DATA_READY;
}
