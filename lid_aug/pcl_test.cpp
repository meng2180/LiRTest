#include <pcl/visualization/cloud_viewer.h>
#include <string>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <fstream>  
#include <vector> 
#include "pcd2bin.h" 
#include <pcl/features/integral_image_normal.h>
#include <pcl/features/normal_3d.h>
#include "batch_bin2pcdR.h"
#include "batch_pcd_augment.h"
#include"batch_pcd2bin.h"

using namespace pcl;
using namespace io;

int main()
{

	vector<string> ori_pcd_file;// pcd format file to be augmented
	vector<string> ori_bin_file;//bin format file for original dataset
	ifstream in("txt filepath");
	string line;
	string type;
	if (in) 
	{
		getline(in, line);
		type = line;//rain,snow,fog,symmetry,translation,scale,rotation
		while (getline(in, line))
		{
			ori_bin_file.push_back("D:/kitti/data_object_velodyne/data_object_velodyne/training/velodyne/" + line + ".bin");//original training dataset
			ori_pcd_file.push_back(line+".pcd");
		}
	}
	else 
	{
		cout << "no such file" << endl;
		system("pause");
		return 0;
	}

	int step = 1;
	batch_pcd_augment(ori_pcd_file, type,step);
	return 0;
}