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
	for(int i = 0; i < 100; ++i) {
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
	sleepms(10);
	// for(int i = 0; i < 500; ++i) {
	// 	int com_status1 = device.SetCommand(_S, 1, 100);
	// 	if(com_status1) {
	// 		cout << "ERROR: " << com_status1 << endl;
	// 	}
	// 	int com_status2 = device.SetCommand(_S, 2, 100);
	// 	if(com_status2) {
	// 		cout << "ERROR: " << com_status2 << endl;
	// 	}
	// 	cout << i << endl;
	// }	

	device.Disconnect();
	return 0;
}
