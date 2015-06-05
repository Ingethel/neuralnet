#include "FileReader.h"

FileReader::FileReader(void)
{
	dataOut = new ofstream();
}


FileReader::~FileReader(void)
{
}

void FileReader::OpenFile(string name){
	dataOut->open(name, ofstream::out);
	if (!dataOut){
		cout << "Error opening data file.\n";
		system("pause");
		exit(1);
	}
}

void FileReader::CloseFile(){
	this->dataOut->close();
}

void FileReader::WriteFile(double data, double y1, double y2){
	*dataOut << data << " " << y1 << " " << y2 << endl;
}