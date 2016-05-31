#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "RoboteqDevice.h"
#include "ErrorCodes.h"
#include "Constants.h"

// A symbolic link to this file must be created, tipically /dev/ttyACM0
// Must be ROOT to run
char DEVICE_NAME[] ="rate_table";
int const MAX_TIME = 30; // [sec] Time on every rate
int const POWER_MOTOR[] = {0,200,400,600,800}; //is a percentage of power in openloop [1-1000]%
using namespace std;

int main(int argc, char *argv[])
{
	RoboteqDevice device;
	int status = device.Connect(DEVICE_NAME);

	if(status != RQ_SUCCESS)
	{
		cout<<"Error connecting to device: "<<status<<"."<<endl;
		cout<<"Create symbolic link to rate_table"<<endl;
		return 1;
	}

	//Wait 10 ms before sending another command to device
	sleepms(10);

	if((status = device.SetCommand(_C, 1, 0)) != RQ_SUCCESS)
		cout<<"SET ECNODER COMMAND failed --> "<<status<<endl;

	int result;
	timeval time;
	int rates = 0;
	int seconds;
	int last_second;
	int motor_power;

	//Determine the number of rates used in the calibration
	int max_rates = sizeof(POWER_MOTOR)/sizeof(int);
	cout << "SIZE "<<max_rates<<endl;

	//Wait 10 ms before sending another command to device
	sleepms(10);
	
	while(rates<max_rates)
	{
		//Initialize cycle
		gettimeofday(&time,NULL);
		last_second = time.tv_sec;
		seconds = 0;
		motor_power = (motor_power>0)?-POWER_MOTOR[rates]:POWER_MOTOR[rates];

		while(seconds<MAX_TIME)
		{
			cout << "Time: "<<seconds << " Cycle: "<<rates+1<<endl;
			if((status = device.SetCommand(_G, 1, motor_power)) != RQ_SUCCESS)
				cout<<"SPEED COMMAND failed --> "<<status<<endl;
		
			//Wait 10 ms before sending another command to device
			sleepms(10);
			
			//Read encoders
			if((status = device.GetValue(_C, 1, result)) != RQ_SUCCESS)
				cout<<"ENCODER failed --> "<<status<<endl;
			else
				cout<<"ENC "<<result<<endl;
			
			//Read system time
			gettimeofday(&time,NULL);
			
			//Wait 10 ms before sending another command to device
			sleepms(10);

			//Read RPM value
			if((status = device.GetValue(_S, 1, result)) != RQ_SUCCESS)
				cout<<"RPM failed --> "<<status<<endl;
			else
				cout<<"RPM "<<result<<endl;
			cout << "TIME "<<time.tv_usec<<endl;
			if(last_second != time.tv_sec)
			{
				seconds++;
				last_second = time.tv_sec;
			}
			sleepms(100);
		}

		//Deccelarate until stopping
		while(result)
		{
			if((status = device.SetCommand(_G, 1, 0)) != RQ_SUCCESS)
				cout<<"SPEED COMMAND failed --> "<<status<<endl;
			//Wait 10 ms before sending another command to device
			sleepms(10);
			//Read RPM value
			if((status = device.GetValue(_S, 1, result)) != RQ_SUCCESS)
				cout<<"RPM failed --> "<<status<<endl;
			sleepms(100);
		}
	
		rates += (motor_power<0 || rates==0);
	}
	device.Disconnect();
	return 0;
}
