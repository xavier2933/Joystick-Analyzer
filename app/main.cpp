/////////////////////////////////////////////////////////////////////////////////////////////
// Author: Xavier O'Keefe
//
// Purpose: Take input joystick csv file and return the nuber of times each button was 
// pressed in the form of a saved .txt file
//
// Calls joystick class, see joystick.hpp and joystickUtilities.cpp
/////////////////////////////////////////////////////////////////////////////////////////////
#include "joystick.hpp"

int main(int argc, char* argv[]) {
    // check if argc has the right # of params
    if (argc < 3)
    {
        cout << "Missing file name(s)" << endl;
        cout << "executable <in file name> <out file name>" << endl;
        return -1;
    }

    joystick joy;

    // set corresponding variables form argv
    string inFileName = argv[1];
    string outFileName = argv[2];

    // read, map, analyze, then write
    joy.readFile(inFileName);
    joy.mapValues();
    joy.writeFile(inFileName, outFileName);
}