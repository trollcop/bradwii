/* 
Copyright 2013 Brad Quick

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "config.h"
#include "lib_digitalio.h"
#include "output.h"

// This file takes the settings from config.h and creates all of the definitions needed for the rest of the code.

// set control board dependant defines here
#define GYRO_TYPE MPU6050       // gyro
#define GYRO_ORIENTATION(VALUES,X, Y, Z) {VALUES[ROLLINDEX] =  Y; VALUES[PITCHINDEX] = -X; VALUES[YAWINDEX] = -Z;}
#define ACCELEROMETER_TYPE MPU6050      // accelerometer
#define ACC_ORIENTATION(VALUES,X, Y, Z)  {VALUES[ROLLINDEX]  = -X; VALUES[PITCHINDEX]  = -Y; VALUES[YAWINDEX]  =  Z;}
#ifndef COMPASS_TYPE
#define COMPASS_TYPE HMC5883  // compass
#endif
#define COMPASS_ORIENTATION(VALUES,X, Y, Z)  {VALUES[ROLLINDEX]  =  X; VALUES[PITCHINDEX]  = Y; VALUES[YAWINDEX]  = -Z;}
#ifndef BAROMETER_TYPE
#define BAROMETER_TYPE MS5611
#endif
#ifndef MULTIWII_CONFIG_SERIAL_PORTS
#define MULTIWII_CONFIG_SERIAL_PORTS SERIALPORT0+SERIALPORT3
#endif
#define GPS_TYPE SERIAL_GPS
#define GPS_SERIAL_PORT 2
#define GPS_BAUD 38400

#define RXNUMCHANNELS 8

// LED Outputs
#define LED1_OUTPUT (DIGITALPORTB | 3)
#ifndef LED1_ON
#define LED1_ON DIGITALON
#endif
#define LED2_OUTPUT (DIGITALPORTB | 4)
#ifndef LED2_ON
#define LED2_ON DIGITALON
#endif

// default to QUADX if no configuration was chosen
#ifndef AIRCRAFT_CONFIGURATION
#define AIRCRAFT_CONFIGURATION QUADX
#endif
// set aircraft type dependant defines here
#if (AIRCRAFT_CONFIGURATION==QUADX)
#define NUMMOTORS 4
#endif
// set configuration port baud rates to defaults if none have been set
#if (MULTIWII_CONFIG_SERIAL_PORTS & SERIALPORT0)
#ifndef SERIAL_0_BAUD
#define SERIAL_0_BAUD 115200
#endif
#endif
#if (MULTIWII_CONFIG_SERIAL_PORTS & SERIALPORT1)
#ifndef SERIAL_1_BAUD
#define SERIAL_1_BAUD 115200
#endif
#endif
#if (MULTIWII_CONFIG_SERIAL_PORTS & SERIALPORT2)
#ifndef SERIAL_2_BAUD
#define SERIAL_2_BAUD 115200
#endif
#endif
#if (MULTIWII_CONFIG_SERIAL_PORTS & SERIALPORT3)
#ifndef SERIAL_3_BAUD
#define SERIAL_3_BAUD 115200
#endif
#endif
#if (GPS_TYPE==SERIAL_GPS)
#ifndef GPS_SERIAL_PORT
#define GPS_SERIAL_PORT 2
#endif
#ifndef GPS_BAUD
#define GPS_BAUD 115200
#endif
#endif
// use default values if not set anywhere else
#ifndef ARMED_MIN_MOTOR_OUTPUT
#define ARMED_MIN_MOTOR_OUTPUT 1067     // motors spin slowly when armed
#endif
#ifndef THROTTLE_TO_MOTOR_OFFSET
#define THROTTLE_TO_MOTOR_OFFSET 0      // motors spin slowly when armed
#endif
// by default don't allow the motors to stop when armed if not in acro or semi acro mode
#ifndef MOTORS_STOP
#define MOTORS_STOP NO
#endif
// default low pass filter
#ifndef GYRO_LOW_PASS_FILTER
#define GYRO_LOW_PASS_FILTER 0
#endif
// default gain scheduling
#ifndef GAIN_SCHEDULING_FACTOR
#define GAIN_SCHEDULING_FACTOR 1.0
#endif
