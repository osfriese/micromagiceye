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
#include <iostream>

#include <ctime>
#include "Log.h"
#include "FrameStack.h"

using namespace std;

class ReadLog {
public:
	ReadLog(string datei);
	virtual ~ReadLog();

    void connectWithFrames(FrameStack * stack, int versatz);

    friend ifstream& operator>>(ifstream& in, Log& d);
	friend ifstream& operator>>(ifstream& in, double& d);

private:
	vector<Log> logdata;
	void read(string datei);
};

#endif /* READLOG_H_ */
