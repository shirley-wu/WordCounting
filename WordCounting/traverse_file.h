#pragma once
#include <fstream>
#include <string>
#include <stack>
#include <io.h>


class TraverseFile {

private:
	std::string root;
	std::string path;
	_finddata_t file_info;
	long handle;
	std::stack<std::pair<std::string, int>> s;

	long findfirst(std::string path, _finddata_t* ptr);
	void moveto_leaf();

public:
	TraverseFile(std::string dir);
	bool begun();
	bool valid();
	std::string get_filepath();
	void begin();
	void next();

};