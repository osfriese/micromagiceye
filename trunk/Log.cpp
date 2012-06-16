/*
 * Log.cpp
 *
 *  Created on: 16.06.2012
 *      Author: osfriese
 */

#include "Log.h"

Log::Log() {
	millisec = 0;
}

void Log::write(FileStorage& fs) const {
	fs << "{";
	fs << "Millisec" << milli;
	fs << "Lat" << lat;
	fs << "Lat" << lon;
	fs << "Heading" << heading;
	fs << "Speed" << speed;
	fs << "WindDirection" << windDirection;
	fs << "WindSpeed" << windSpeed;
	fs << "accX" << accX;
	fs << "accY" << accY;
	fs << "accZ" << accZ;
	fs << "magRawX" << magRawX;
	fs << "magRawY" << magRawY;
	fs << "magRawZ" << magRawZ;
	fs << "gyroY" << gyroY;
	fs << "gyroP" << gyroP;
	fs << "gyroR" << gyroR;
	fs << "Kompass" << kompass;
	fs << "Stampfen" << stampfen;
	fs << "Kraengung" << kraengung;
	fs << "Battery" << battery;
	fs << "Rudder" << rudder;
	fs << "Main" << main;
	fs << "Jib" << jib;
	fs << "Blink" << blink;
	fs << "}";
}
