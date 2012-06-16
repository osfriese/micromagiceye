/*
 * Log.h
 *
 *  Created on: 16.06.2012
 *      Author: osfriese
 */

#ifndef LOG_H_
#define LOG_H_

#include "opencv2/core/core.hpp"

using namespace cv;

class Log {
public:
	Log();
	char sd[2];
	long long millisec;
	int milli;
	double lat, lon, heading, speed, windDirection, windSpeed, accX, accY, accZ,
			magRawX, magRawY, magRawZ, gyroY, gyroP, gyroR, kompass, stampfen,
			kraengung, battery;
	char cd[2];
	double rudder, main, jib;
	bool blink;

	// Überladung für FileStorage
	void write(FileStorage& fs) const;
};

#endif /* LOG_H_ */
