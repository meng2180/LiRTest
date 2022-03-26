#pragma once
#include<vector>
void batch_pcd2bin(vector<string> filenameList) {
	for (vector<string>::iterator iter = filenameList.begin(); iter != filenameList.end(); iter++) {
		string filename = *iter;
		cout << filename;
		string outfilename = filename;
		outfilename.replace(outfilename.length() - 3, outfilename.length(), "bin");
		convertPCDtoBin(filename, outfilename);
	}
}
	