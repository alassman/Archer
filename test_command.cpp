#include <iostream>
#include <stdio.h>
#include <string.h>

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
		int com_status1 = device.SetCommand(_G, 1, 1000);
		if(com_status1) {
			cout << "ERROR: " << com_status1 << endl;
		}
		int com_status2 = device.SetCommand(_G, 2, 1000);
		if(com_status2) {
			cout << "ERROR: " << com_status2 << endl;
		}
		cout << i << endl;
	}	

	device.Disconnect();
	return 0;
}
