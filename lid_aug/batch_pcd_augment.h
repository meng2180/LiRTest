#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h> 
#include <boost/random.hpp> 
#include <fstream>  
#include <string>  
#include <vector> 
#include <pcl/features/integral_image_normal.h>
#include <pcl/features/normal_3d.h>
#include <pcl/compression/octree_pointcloud_compression.h>
#include <direct.h>
#include <string>
#include "one_pcd_augment.h"

using namespace std;
int init[20] = {0,1,2,3,4,5,6,7,8,9,10 };
void batch_pcd_augment(vector<string> filenameList, string type,int step) {
	int parameter = 0;
	string file_= "00";
	for (int i = 1; i <= step; i++)
	{
		int a1 = i % 10;
		int b1 = i / 10;
		file_[1] = char(a1+'0');
		file_[0] = char(b1+'0');
		parameter = init[i];
		int num = 1;
		for (vector<string>::iterator iter = filenameList.begin(); iter != filenameList.end(); ++iter)
		{
			cout << "index:";
			cout << num << endl;
			num++;
			const char* filename = iter->c_str();
			string s1 = "E:\\augmentation\\" + (*iter);
			//Open a corresponding pcd file according to the pcd file name in the pcd file list
			pcl::PointCloud<pcl::PointXYZI>::Ptr original_pcd(new pcl::PointCloud<pcl::PointXYZI>);
			if (pcl::io::loadPCDFile<pcl::PointXYZI>(s1, *original_pcd) == -1)
			{
				PCL_ERROR("Couldn't read file pcd\n");
			}		
			pcl::PointCloud<pcl::PointXYZI>::Ptr augment_pcd = one_pcd_augment(original_pcd, type, parameter,(*iter));//one pcd augmentation

			string defaultPath = "E:\\augmentation res\\"+type;
			if (0 != _access(defaultPath.c_str(), 0))_mkdir(defaultPath.c_str());   //One folder for each step
			string folderPath = defaultPath +"\\"+ file_;
			if (0 != _access(folderPath.c_str(), 0))_mkdir(folderPath.c_str());  //Modify the augmentation file name
			string s2= defaultPath + "\\" + file_+"\\"+(*iter);
			s2.replace(s2.length() - 4, s2.length(), "++.bin");

			std::ofstream myFile(s2.c_str(), std::ios::out | std::ios::binary);
			for (int j = 0; j < augment_pcd->size(); j++) {

				myFile.write((char*)& augment_pcd->at(j).x, sizeof(augment_pcd->at(j).x));
				myFile.write((char*)& augment_pcd->at(j).y, sizeof(augment_pcd->at(j).y));
				myFile.write((char*)& augment_pcd->at(j).z, sizeof(augment_pcd->at(j).z));
				myFile.write((char *)& augment_pcd->at(j).intensity, sizeof(augment_pcd->at(j).intensity));
			}
			//system("pause");
			cout << "bin has generated" << endl;
			//system("pause");
			
		}
	}
}

