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
#include "Log.h"

using namespace std;

class ReadLog {
public:
	ReadLog(string datei);
	virtual ~ReadLog();
	friend ifstream& operator>>(ifstream& in, Log& d);
	friend ifstream& operator>>(ifstream& in, double& d);
private:
	vector<Log> logdata;
	void read(string datei);
};

#endif /* READLOG_H_ */
