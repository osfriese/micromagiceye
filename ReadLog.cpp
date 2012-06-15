/*
 * ReadLog.cpp
 *
 *  Created on: 07.06.2012
 *      Author: osfriese
 */

#include "ReadLog.h"

ReadLog::ReadLog(string datei) {
	read(datei);
}

ReadLog::~ReadLog() {
}

ifstream& operator >>(ifstream& in, LOGDATA& d) {
	in >> d.sd >> d.millisec >> d.lat >> d.lon >> d.heading >> d.speed
			>> d.windDirection >> d.windSpeed >> d.accX >> d.accY >> d.accZ
			>> d.magRawX >> d.magRawY >> d.magRawZ >> d.gyroY >> d.gyroP
			>> d.gyroR >> d.kompass >> d.stampfen >> d.kraengung >> d.battery
			>> d.cd >> d.rudder >> d.main >> d.jib >> d.blink;
	return in;
}

ifstream& operator >>(ifstream& in, double& d) {
	string temp;
	in >> temp;
	stringstream conv(temp);
	conv >> d;
	return in;
}

void ReadLog::read(string datei) {
	ifstream file(datei.c_str());

	// Exception werfen bei Fehler
	if (!file.is_open()) {
		string errorMsg = datei;
		errorMsg += " konnte nicht geoeffnet werden!\n";
		throw(string) errorMsg;
	}

	LOGDATA log;
	while (file >> log) {
		logdata.push_back(log);
	}

	file.close();
}
