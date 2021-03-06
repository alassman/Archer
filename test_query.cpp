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
		int com_status2 = device.SetCommand(_S, 2, -100);
		if(com_status2) {
			cout << "ERROR: " << com_status2 << endl;
		}
		//Check RPM

		int rpm1;
		if((status = device.GetValue(_S, 1, rpm1)) != RQ_SUCCESS)
			cout<<"failed --> "<<status<<endl;
		//Wait 10 ms before sending another command to device
		sleepms(10);

		int rpm2;
		if((status = device.GetValue(_S, 2, rpm2)) != RQ_SUCCESS)
			cout<<"failed --> "<<status<<endl;



		cout << "RPM = " << rpm1 << " : " << rpm2 << endl;



		//Wait 10 ms before sending another command to device
		sleepms(10);
	}	

	cout << "will print if amperage on motor1 or motor 2 exceeds 5 amps" << endl;
	for(int i = 0; i < 500; ++i) {
		int com_status1 = device.SetCommand(_S, 1, 100);
		if(com_status1) {
			cout << "1ERROR: " << com_status1 << endl;
		}
		sleepms(10);
		int com_status2 = device.SetCommand(_S, 2, 100);
		if(com_status2) {
			cout << "2ERROR: " << com_status1 << endl;
		}
		sleepms(10);
		int A1;
		if((status = device.GetValue(_A, 1, A1)) != RQ_SUCCESS)
			cout<<"failed --> "<<status<<endl;
		else {
			if(A1 > 5) {
				cout << "MOTOR 1 amperage: " << A1 << endl;
			}
		}
		sleepms(10);
		int A2;
		if((status = device.GetValue(_A, 2, A2)) != RQ_SUCCESS)
			cout<<"failed --> "<<status<<endl;
		else {
			if(A2 > 5) {
				cout << "MOTOR 2 amperage: " << A2 << endl;
			}
		}
		sleepms(10);
	}

	device.Disconnect();
	return 0;
}
