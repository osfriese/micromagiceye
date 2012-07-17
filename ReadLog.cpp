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

void ReadLog::connectWithFrames(FrameStack *stack, int versatz)
{
    int size = stack->size();
    int logIterator = 0;

    cout << "Logaten werden zugeordnen";

    while((logdata[logIterator].milli - versatz) < 0)
        logIterator++;

    for (int stackIterator = size -1; stackIterator > 0; stackIterator--) {
        if((logdata[logIterator].milli - versatz) < stack->getFrame(stackIterator).getID())
            logIterator++;
        stack->getFrame(stackIterator).setLog(logdata[logIterator]);
        cout << ".";
    }
    cout << endl << "Erfolgreich" << endl;


}

ifstream& operator >>(ifstream& in, Log& d) {
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
    try {
        ifstream file(datei.c_str());

        // Exception werfen bei Fehler
        if (!file.is_open()) {
            string errorMsg = datei;
            errorMsg += " konnte nicht geoeffnet werden!\n";
            throw(string) errorMsg;
        }

        Log log;
        try {
            while (file >> log) {
                logdata.push_back(log);
            }
        } catch (...) {
            throw "Falsches Dateiformat";
        }


        long long millisec = logdata[0].millisec;
        for (unsigned int var = 0; var < logdata.size(); ++var) {
            logdata[var].milli = (int) logdata[var].millisec - millisec;
        }

        file.close();
    } catch (...) {
        cout << "Logdatei hat falsches Dateiformat" << endl;
    }

}
