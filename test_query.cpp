#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "RoboteqDevice.h"
#include "ErrorCodes.h"
#include "Constants.h"

using namespace std;

int main(int argc, char *argv[])
{
	string response = "";
	RoboteqDevice device;
	int status = device.Connect("/dev/ttyACM0");

	if(status != RQ_SUCCESS)
	{
		cout<<"Error connecting to device: "<<status<<"."<<endl;
		return 1;
	}

	//Wait 10 ms before sending another command to device
	sleepms(10);
	for(int i = 0; i < 50; ++i) {
		int com_status1 = device.SetCommand(_S, 1, 100);
		if(com_status1) {
			cout << "ERROR: " << com_status1 << endl;
		}
		int com_status2 = device.SetCommand(_S, 2, 100);
		if(com_status2) {
			cout << "ERROR: " << com_status2 << endl;
		}
		//Check RPM

		int rpm1;
		if((status = device.GetValue(_S, 1, rpm1)) != RQ_SUCCESS)
			cout<<"failed --> "<<status<<endl;
		else
			cout << "rpm for motor 1: " << rpm1 << endl;

		//Wait 10 ms before sending another command to device
		sleepms(10);

		int rpm2;
		if((status = device.GetValue(_S, 2, rpm2)) != RQ_SUCCESS)
			cout<<"failed --> "<<status<<endl;
		else
			cout << "rpm for motor 2: " << rpm2 << endl;

		//Wait 10 ms before sending another command to device
		sleepms(10);
	}	
	for(int i = 0; i < 100; ++i) {
		int com_status1 = device.SetCommand(_S, 1, -100);
		if(com_status1) {
			cout << "ERROR: " << com_status1 << endl;
		}
		int com_status2 = device.SetCommand(_S, 2, -100);
		if(com_status2) {
			cout << "ERROR: " << com_status2 << endl;
		}
		//Check RPM

		int rpm1;
		if((status = device.GetValue(_S, 1, rpm1)) != RQ_SUCCESS)
			cout<<"failed --> "<<status<<endl;
		else
			cout << "rpm for motor 1: " << rpm1 << endl;

		//Wait 10 ms before sending another command to device
		sleepms(10);

		int rpm2;
		if((status = device.GetValue(_S, 2, rpm2)) != RQ_SUCCESS)
			cout<<"failed --> "<<status<<endl;
		else
			cout << "rpm for motor 2: " << rpm2 << endl;

		//Wait 10 ms before sending another command to device
		sleepms(10);
	}	
	cout << "will print if amperage on motor1 or motor 2 exceeds 1 amp" << endl;
	for(int i = 0; i < 500; ++i) {
		int com_status1 = device.SetCommand(_S, 1, 100);
		if(com_status1) {
			cout << "ERROR: " << com_status1 << endl;
		}
		float A1;
		if((status = device.GetValue(_A, 1, A1)) != RQ_SUCCESS)
			cout<<"failed --> "<<status<<endl;
		else {
			if(A1 > 1) {
				// cout << "Amps for motor1 exceeds 1 amp" << endl;
				// cout << "Amperage: " << A1 << endl;
				cout << "************************" << endl;
			}
			cout << "Amperage: " << A1 << endl;
		}
		int com_status2 = device.SetCommand(_S, 2, 100);
		if(com_status2) {
			cout << "ERROR: " << com_status1 << endl;
		}
		float A2;
		if((status = device.GetValue(_A, 2, A2)) != RQ_SUCCESS)
			cout<<"failed --> "<<status<<endl;
		else {
			if(A2 > 1) {
				// cout << "Amps for motor2 exceeds 1 amp" << endl;
				// cout << "Amperage: " << A2 << endl;
				cout << "************************" << endl;
			}
			cout << "Amperage: " << A2 << endl;
		}

	}

	device.Disconnect();
	return 0;
}
