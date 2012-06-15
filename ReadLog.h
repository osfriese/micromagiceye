/*
 * ReadLog.h
 *
 *  Created on: 07.06.2012
 *      Author: osfriese
 */

#ifndef READLOG_H_
#define READLOG_H_

#include <fstream>
#include <sstream>
#include <vector>

#include <ctime>

using namespace std;

struct LOGDATA {
	char sd[2];
	long long millisec;
	double lat, lon, heading, speed, windDirection, windSpeed, accX, accY, accZ,
			magRawX, magRawY, magRawZ, gyroY, gyroP, gyroR, kompass, stampfen,
			kraengung, battery;
	char cd[2];
	double rudder, main, jib;
	bool blink;
};

class ReadLog {
public:
	ReadLog(string datei);
	virtual ~ReadLog();
	friend ifstream& operator>>(ifstream& in, LOGDATA& d);
	friend ifstream& operator>>(ifstream& in, double& d);
private:
	vector<LOGDATA> logdata;

	void read(string datei);
};

#endif /* READLOG_H_ */
