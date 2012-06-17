/*
 * FrameAnalyser.cpp
 *
 *  Created on: 04.06.2012
 *      Author: osfriese
 */

#include "FrameAnalyser.h"

FrameAnalyser::~FrameAnalyser() {
    // TODO Auto-generated destructor stub
}

FrameAnalyser::FrameAnalyser(String windowName, FrameStack * stack) {
	myStack = stack;
	ausgabe.open(windowName.append(".analyse").c_str(), ios::out);
	cout << "1: Horizont falsch" << endl << "2: gelbe Bojen nah falsch" << endl
			<< "3: gelbe Boje fern falsch" << endl << "4: rote Bojen nah falsch"
			<< endl << "5: rote Boje fern falsch" << endl
			<< "6: Schiff nah falsch" << endl << "7: Schiff fern falsch" << endl
			<< "8: Hindernis falsch" << endl;
}

void FrameAnalyser::analyse()
{
    Frame temp = myStack->getActualFrame();
    analyse(temp);
}

void FrameAnalyser::analyse(Frame frame) {
    show(frame);

	static int n = 0;
	char filename[200];

	for (int i = 0; i < 8; i++)
		d[i] = 1;

	char c = 0;
	while (c != 32) {
		c = waitKey(0);
		if (c > 50 && c < 60)
			d[(int) c - 50] = 0;
		else
			switch ((char) c) {
			case 's':
				sprintf(filename, "img/Original%.3d.jpg", n);
                imwrite(filename, frame.getFrame());
				sprintf(filename, "img/Image%.3d.jpg", n);
                imwrite(filename, frame.getImage());
				sprintf(filename, "img/Canny%.3d.jpg", n);
                imwrite(filename, frame.getCanny());
				cout << "Saved " << endl;
				n++;
				break;
			}
	}

	for (int i = 0; i < 8; i++) {
//		cout << d[i] << "\t";
		ausgabe << d[i] << "\t";
	}
//	cout << endl;
    ausgabe << endl;
}

void FrameAnalyser::analyseStack()
{
    for (int var = 0; var < myStack->size(); var++) {
        analyse(myStack->getFrame(var));
    }

}

void FrameAnalyser::show(Frame frame) {
	imshow("Original Frame", frame.getFrame());
	imshow("Computed Image", frame.getImage());
	imshow("Canny", frame.getCanny());
//	imshow("Horizont Mask", frame.getHorizontMask());

}

