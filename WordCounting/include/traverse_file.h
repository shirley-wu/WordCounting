#pragma once
#include <fstream>
#include <string>
#include <stack>
#include <io.h>


class TraverseFile {

private:
	std::string path;
	_finddata_t file_info;
	long handle;
	std::stack<std::pair<std::string, int>> s;

	long findfirst(std::string path, long& local_handle, _finddata_t* ptr);

public:
	TraverseFile(std::string dir);
	bool valid();
	std::string get_filepath();
	void traverse();

};