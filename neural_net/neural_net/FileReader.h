#pragma once

/*write in files the set of input-outputs*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class FileReader
{
public:
	FileReader(void);
	~FileReader(void);
	void WriteFile(double data, double y1, double y2);
	void OpenFile(string name);
	void CloseFile(void);
	ofstream *dataOut;
};



