#include <iostream>

#include "traverse_file.h"

using namespace std;


TraverseFile::TraverseFile(string dir) {
	path = dir;
	handle = -2;
}


bool TraverseFile::valid() {
	return handle != -1;
}


string TraverseFile::get_filepath() {
	return valid() ? path + '\\' + file_info.name : "";
}


long TraverseFile::findfirst(string path, long& local_handle, _finddata_t* ptr) {
	long status;
	local_handle = _findfirst((path + "\\*").c_str(), ptr);
	status = _findnext(local_handle, ptr);
	status = _findnext(local_handle, ptr);
	return status;
}


void TraverseFile::traverse(){
	if (!valid()) return;

	long status;

	if (handle == -2) status = findfirst(path, handle, &file_info);
	else status = _findnext(handle, &file_info);
	while( 1 ) {
		if (status == 0) {
			if (file_info.attrib == _A_SUBDIR) {
				s.push(make_pair(path, handle));
				path = path + "\\" + file_info.name;
				status = findfirst(path, handle, &file_info);
			}
			else break;
		}
		else if (s.empty()) {
			handle = -1;
			return;
		}
		else{
			path = s.top().first;
			handle = s.top().second;
			s.pop();
			status = _findnext(handle, &file_info);
		}
	}

	if (status == -1) handle = -1;
}