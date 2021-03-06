#pragma once

#include <omp.h>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>

#include <pcl/io/pcd_io.h>
#include <pcl/common/common_headers.h>

#include <sys/stat.h>

#include <pcl/io/boost.h>
#include <boost/program_options.hpp>

#include <fstream>



void convertPCDtoBin(std::string &in_file, std::string& out_file)
{
	pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>);

	if (pcl::io::loadPCDFile<pcl::PointXYZI>(in_file, *cloud) == -1) //* load the file
	{
		std::string err = "Couldn't read file " + in_file;
		PCL_ERROR(err.c_str());
		return;// (-1);
	}
	std::cout << "Loaded "
		<< cloud->width * cloud->height
		<< " data points from "
		<< in_file
		<< " with the following fields: "
		<< std::endl;

	std::ofstream myFile(out_file.c_str(), std::ios::out | std::ios::binary);
	for (int j = 0; j < cloud->size(); j++) {

		myFile.write((char*)& cloud->at(j).x, sizeof(cloud->at(j).x));
		myFile.write((char*)& cloud->at(j).y, sizeof(cloud->at(j).y));
		myFile.write((char*)& cloud->at(j).z, sizeof(cloud->at(j).z));
		myFile.write((char *)& cloud->at(j).intensity, sizeof(cloud->at(j).intensity));
		//myFile << cloud->at(j).x << " " << cloud->at(j).y << " " << cloud->at(j).z << endl;
	}
	myFile.close();
}





