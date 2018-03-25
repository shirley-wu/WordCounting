#include "traverse_file.h"

using namespace std;


TraverseFile::TraverseFile(string dir) {
	root = dir;
	path = "";
	handle = -2;
}


bool TraverseFile::begun() {
	return handle != -2;
}


bool TraverseFile::valid() {
	return handle >= 0;
}


string TraverseFile::get_filepath() {
	return valid() ? path + '\\' + file_info.name : "";
}


long TraverseFile::findfirst(string path, _finddata_t* ptr) {
	long handle, k;
	handle = _findfirst((path + "\\*").c_str(), ptr);
	k = _findnext(handle, ptr);
	k = _findnext(handle, ptr);
	return k == -1 ? -1 : handle;
}


void TraverseFile::moveto_leaf() {
	if (!valid()) return;
	while (handle != -1 && file_info.attrib == _A_SUBDIR) {
		s.push(make_pair(path, handle));
		path = path + "\\" + file_info.name;
		handle = findfirst(path, &file_info);
	}
}


void TraverseFile::begin() {
	if (begun()) return;
	
	path = root;
	handle = findfirst(path, &file_info);
	moveto_leaf();

	if (handle == -1) {
		while (!s.empty()) s.pop();
	}
}


void TraverseFile::next(){
	if (!valid()) return;

	int status;
	status = _findnext(handle, &file_info);
	while(status == -1 && !s.empty()) {
		path = s.top().first;
		handle = s.top().second;
		s.pop();
		status = _findnext(handle, &file_info);
	}

	if (status != -1) moveto_leaf();
	else handle = -1;
}