/*
 * Robot Navigation Program
 * www.robotnav.com
 *
 * (C) Copyright 2016 - 2017 Adam Lassman
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ARCHER_H
#define ARCHER_H

#include "Robot.h"
#include "RoboteqDevice.h"
#include "ErrorCodes.h"
#include "Constants.h"

class Archer : public Robot
{
	protected:
		RoboteqDevice device;
		MOTORDATA *pMotorData;
		int Lmotor;
		int Rmotor;
		float mLastLeftEncoderCount;
		float mLastRightEncoderCount;
	public:
		Archer(float period, float track, float encoderScaleFactor, char *pMotorInfo, char *sensorInfo = 0);
		virtual ~Archer();
		virtual int readSensors();
		virtual void setActuators(char *pMotorSpeed);
		virtual void setActuators(float speed, float rate);
};

#endif