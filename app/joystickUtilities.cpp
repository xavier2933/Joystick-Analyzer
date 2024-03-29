/////////////////////////////////////////////////////////////////////////////////////////////
// Author: Xavier O'Keefe
//
// Purpose: fucntion definitions for joystick class
/////////////////////////////////////////////////////////////////////////////////////////////
#include "joystick.hpp"

using namespace std;

void joystick::mapValues()
{
    unordered_map<int, string> buttonNames; // So button names can be easily changed
    buttonNames[1] = "Arm x";
    buttonNames[2] = "Arm y";
    buttonNames[3] = "Up button";
    buttonNames[12] = "Down button";
    buttonNames[4] = "A button";
    buttonNames[5] = "B button";
    buttonNames[6] = "Arm down (left trigger)";
    buttonNames[7] = "Arm up (right trigger)";
    buttonNames[8] = "Wrist left (left bumper)";
    buttonNames[9] = "Wrist right (right bumper)";
    buttonNames[10] = "Drive forward";
    buttonNames[11] = "turn right/left";
    buttonNames[190353254] = "Incompatible joystick";

    int size = result[0].size();
    if(size == 19) // Wired controller
    {
        // axes
        joyMap[3] = buttonNames[1];
        joyMap[4] = buttonNames[2];
        joyMap[7] = buttonNames[3];
        // buttons
        joyMap[8] = buttonNames[4];
        joyMap[9] = buttonNames[5];
        joyMap[11] = buttonNames[6];
        joyMap[12] = buttonNames[7];
        joyMap[13] = buttonNames[8];
        joyMap[14] = buttonNames[9];
        joyMap[100] = "Wired Controller";

    } 
    else if(size == 23) // Old wireless controller
    {
        joyMap[2] = buttonNames[1];
        joyMap[3] = buttonNames[2];
        joyMap[7] = buttonNames[3];
        // buttons
        joyMap[8] = buttonNames[4];
        joyMap[9] = buttonNames[5];
        joyMap[13] = buttonNames[6];
        joyMap[14] = buttonNames[7];
        joyMap[15] = buttonNames[8];
        joyMap[16] = buttonNames[9];
        joyMap[100] = "Old wireless controller";
    }
    else if(size == 24) // Xbox one wireless controller
    {
        // TODO: joyMap 7 is arm up/down, need to change 
        // axes
        joyMap[0] = buttonNames[10]; 
        axesIndicesMap[0] = 1; // wtf is this??
        joyMap[1] = buttonNames[11];
        axesIndicesMap[1] = 1;
        joyMap[2] = buttonNames[1];
        axesIndicesMap[2] = 1;
        joyMap[3] = buttonNames[2];
        axesIndicesMap[3] = 1;
        joyMap[7] = buttonNames[3];
        joyMap[5] = buttonNames[6];
        joyMap[4] = buttonNames[7];
        // buttons
        joyMap[9] = buttonNames[4];
        joyMap[10] = buttonNames[5];
        joyMap[15] = buttonNames[8];
        joyMap[16] = buttonNames[9];
        joyMap[100] = "New wireless controller";
        
    }
    else { // return joyMap -1 if joystick isnt recognized
        joyMap[-1] = buttonNames[190353254];
    }
}

// reads data from file and stores it in results vector
void joystick::readFile(string name)
{
    ifstream file;
    file.open(name);

    int count = 0;
    string line;
    string value;

    getline(file, line); // skips first line

    // insert each line into stringstream object s
    while (getline (file, line)) {
        vector<double> row;
        stringstream s (line);

        // read each element delimited by a comma, else go to next line
        while (getline (s, value, ','))
        {
            if (count < 4) {
                count++;
                continue;
            } else {
                count++;     
                double valueDouble = stod(value);
                row.push_back(valueDouble);
            }
        }
        result.push_back(row);
        count = 0;
    }

    file.close();
}

// counts number of times button is pressed
int joystick::numOccurences(int index)
{
    // check if index has been joyMapped (to see if we care about this button)
    if(joyMap.count(index) == 0) 
    {
        return -1;
    } else {
        int count = 0;
        double temp = 0;
        double prev = 0;
        double baseState = result[1][index];
        for(int i = 1; i < result.size(); i++) 
        {
            prev = result[i-1][index];
            temp = result[i][index];
            if(temp!=baseState)
            {
                // Skip if value is not base state
                continue;
            }
            if(temp != prev) // IF consecutive values are different, increment count
            {
                count++;
            }
        }
        return count;
    }
    
}

pair<int, int> joystick::driveCounter(int index)
{
    int pos = 0;
    int neg = 0;
    double temp = 0;
    double prev = 0;
    int j = 0;
    int tempcount = 0;
    pair<int, int> numz;
    for(int i = 1; i < result.size(); i++) 
    {
        temp = result[i][index];
        prev = result[j][index];
        // count number of times button is pressed
        if(!(temp == 0.0 || temp == -0.0))
        {
            // Skip if value is not a verified state, reduces overcounting
            // Also skips j, leaving it as a pointer to the last regular val
            continue;
        }
        if((temp == -prev || temp == prev) && result[i-1][index] > 0) // IF values consecutive values are different, increment count
        {
            pos++;
            j=i; // allows j to "catch up" again
            continue;
        }
        if((temp == -prev || temp == prev) && result[i-1][index] < 0) // IF values consecutive values are different, increment count
        {
            neg++;
            j=i; // allows j to "catch up" again
            continue;
        }
        j++;
    }
    // pos = pos/2;
    // neg = neg/2;
    numz.first = pos;
    numz.second = neg;
    return numz; // 
    
}

// writes data to file and command line, calls numOccurances to get data to write
void joystick::writeFile(string inName, string outName)
{
    ofstream file;
    file.open(outName);
    int temp = 0;
    int pos,neg;

    // print where data came from
    file << "##### Generated from " << inName  << " #####" << endl;
    file << "Using controller: " << joyMap[100] << endl;
    cout << "Using controller: " << joyMap[100] << endl;

    for(int i = 0; i < result[0].size(); i++)
    {
        temp = numOccurences(i);
        if(temp == -1) // this happens when value isnt joyMapped (we dont care about that button)
        {
            continue;
        } 
        else if (joyMap.count(-1) == 1) { 
            cout << "Incompatible joystick" << endl;
            break;   
        } 
        else if ((joyMap.count(0) == 1 || joyMap.count(1) == 1) && (axesIndicesMap.count(i) == 1)) 
        {
            pair<int, int> result;
            result = driveCounter(i);
            cout << joyMap[i] << " was positive " << result.first << " times ";
            cout << " and negative " << result.second << " times." << endl;
        }
        else {
            cout << joyMap[i] << " was pressed " << temp << " times. " << endl;
            file << joyMap[i] << " was pressed " << temp << " times. " << endl;
        }    
    }

    file.close();
}
