/////////////////////////////////////////////////////////////////////////////////////////////
// Author: Xavier O'Keefe
//
// Purpose: header file for joystick class
/////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

class joystick {
    public:
        int numOccurences(int);
        void mapValues();
        void readFile(string);
        void writeFile(string, string); 
        pair<int, int> driveCounter(int);  
        vector<vector<double> > result;
        unordered_map<int, string> joyMap;
        unordered_map<int, int> axesIndicesMap; // stores indices of axes that we're interested in
};