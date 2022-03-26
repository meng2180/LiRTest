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
#include<random>
#include<ctime>
#include "changelabel.h"
#include "changecalib.h"

#define PI 3.1415926
using namespace std;

string CauculatebinTolabelOutput(string filename)
{
	filename.replace(filename.length() - 4, filename.length(), "++.txt");
	return filename;
}
string CauculatebinTolabelInput(string filename)
{
	filename.replace(filename.length() - 4, filename.length(), ".txt");
	return filename;
}

pcl::PointCloud<pcl::PointXYZI>::Ptr one_pcd_augment(pcl::PointCloud<pcl::PointXYZI>::Ptr cloud, string type,int parameter, string filename) {
	cout << "one pcd augment" << endl;
	double h = 0, w = 0, l = 0, x = 0, y = 0, z = 0, ry = 0;//Label Variation
	string labin = CauculatebinTolabelInput(filename);
	string labout = CauculatebinTolabelOutput(filename);
	string labelPath1 = "E:\\label_2\\" + labin;//Label input path
	string labelPath2 = "E:\\augmentation res\\" + type+"\\label_2\\" + labout;//Label output path
	string calibPath1 = "E:\\calib\\" + labin;//Calibration input path
	string calibPath2 = "E:\\augmentation res\\" + type + "\\calib\\" + labout;//Calibration output path
	string logPath = "E:\\augmentation res\\" + type +"\\"+ "log.txt";//Record point cloud transformation parameters
	ofstream outlog(logPath, ios::app);
	pcl::PointCloud<pcl::PointXYZI>::Ptr cloudfiltered(new pcl::PointCloud<pcl::PointXYZI>());
	size_t cloudfilteredSize;
	pcl::copyPointCloud(*cloud, *cloudfiltered);
	if (type == "rain") {
		double quantity[20] = { 2,4,6,8,10,12,14,16,18,20 };
		double changerate[20] = { 0.95,0.9,0.85,0.8,0.75,0.7,0.65,0.6,0.55,0.5};
		srand(time(0));
		int ran = rand() % 10;
		cloudfilteredSize = cloud->points.size() * changerate[ran]; 

		boost::mt19937 rng;
		rng.seed(static_cast<int>(time(0)));
		boost::uniform_int<> real(0, cloud->points.size() - 1);
		boost::variate_generator<boost::mt19937&, boost::uniform_int<>> var_nor(rng, real);

		std::vector<int> indexs;
		while (indexs.size() < cloudfilteredSize) {
			indexs.push_back(var_nor());
		}

		pcl::copyPointCloud(*cloud, indexs, *cloudfiltered);

		double result = 0, x = 0, y = 0, z = 0, d = 0, resparameter = 0;
		resparameter = pow(quantity[ran], 0.6);
		for (int point_i = 0; point_i < cloudfiltered->points.size(); ++point_i)
		{
			x = cloudfiltered->points[point_i].x;
			y = cloudfiltered->points[point_i].y;
			z = cloudfiltered->points[point_i].z;
			d = sqrt(x*x + y * y + z * z);
			result = exp(-0.02*resparameter*d);
			cloudfiltered->points[point_i].intensity = result * cloudfiltered->points[point_i].intensity;
		}
		changelabel(labelPath1, labelPath2, type, h, w, l, x, y, z, ry);
		changecalib(calibPath1, calibPath2, type, h, w, l, x, y, z, ry);
		outlog << labout << " " << changerate[ran] << " "<< quantity[ran] << endl;
	}
	else if (type == "snow") {
		double quantity[20] = { 2,4,6,8,10,12,14,16,18,20 };
		double changerate[20] = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5 };

		srand(time(0));
		int ran = rand() % 10;
		cloudfilteredSize = cloud->points.size() * changerate[ran];

		pcl::PointXYZI minP;
		pcl::PointXYZI maxP;
		pcl::getMinMax3D(*cloud, minP, maxP);


		boost::mt19937 rng;
		rng.seed(static_cast<unsigned int>(time(0)));

		cloudfiltered->points.resize(cloud->points.size() + cloudfilteredSize);
		cloudfiltered->header = cloud->header;
		cloudfiltered->width = cloud->width + cloudfilteredSize;
		cloudfiltered->height = cloud->height;

		int density =8;

		float para_nd_x = max(abs(minP.x), abs(maxP.x))*max(abs(minP.x), abs(maxP.x))/9 / density / density;
		float para_nd_y = max(abs(minP.y), abs(maxP.y))*max(abs(minP.y), abs(maxP.y))/9 / density / density;
		float para_nd_z = max(abs(minP.z), abs(maxP.z))*max(abs(minP.z), abs(maxP.z))/9 / density / density;

		boost::normal_distribution<> nd_x(0, para_nd_x);  //Normal distribution
		boost::normal_distribution<> nd_y(0, para_nd_y);
		boost::normal_distribution<> nd_z(0, para_nd_z);
		boost::variate_generator<boost::mt19937&, boost::normal_distribution<>> var_nor_x(rng, nd_x);
		boost::variate_generator<boost::mt19937&, boost::normal_distribution<>> var_nor_y(rng, nd_y);
		boost::variate_generator<boost::mt19937&, boost::normal_distribution<>> var_nor_z(rng, nd_z);

		// Create a KdTree object
		pcl::KdTreeFLANN<pcl::PointXYZI> kdtree;

		kdtree.setInputCloud(cloud);

		int K = 5;

		// Create two vectors to store the index value of the neighbor and the center distance of the neighbor respectively
		std::vector<int> pointIdxNKNSearch(K);
		std::vector<float> pointNKNSquaredDistance(K);

		for (size_t point_i = cloud->points.size(); point_i < cloud->points.size() + cloudfilteredSize;)
		{
			float x=static_cast<float> (var_nor_x());
			float y = static_cast<float> (var_nor_y());
			float z = static_cast<float> (var_nor_z());
			if (x<minP.x || x>maxP.x || y<minP.y || y>maxP.y||z<0||z>maxP.z)continue;
			cloudfiltered->points[point_i].x = x;
			cloudfiltered->points[point_i].y = y;
			cloudfiltered->points[point_i].z = z;

			if (kdtree.nearestKSearch(cloudfiltered->points[point_i], K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
			{
				float sumintensity = 0;
				for (size_t i = 0; i < pointIdxNKNSearch.size(); ++i)
				{
				
					sumintensity += cloudfiltered->points[pointIdxNKNSearch[i]].intensity;
				}
				cloudfiltered->points[point_i].intensity = sumintensity /5;
				/*cout << cloudfiltered->points[point_i].intensity << endl;*/
			}
			pointIdxNKNSearch.clear();
			pointNKNSquaredDistance.clear();
			++point_i;
		}

		double result = 0, x = 0, y = 0, z = 0, d = 0, resparameter = 0;
		resparameter = pow(quantity[ran], 0.5);
		for (int point_i = 0; point_i < cloudfiltered->points.size(); ++point_i)
		{
			x = cloudfiltered->points[point_i].x;
			y = cloudfiltered->points[point_i].y;
			z = cloudfiltered->points[point_i].z;
			d = sqrt(x*x + y * y + z * z);
			result = exp(-0.01*resparameter*d);
			cloudfiltered->points[point_i].intensity = result * cloudfiltered->points[point_i].intensity;
		}
		changelabel(labelPath1, labelPath2, type, h, w, l, x, y, z, ry);
		changecalib(calibPath1, calibPath2, type, h, w, l, x, y, z, ry);
		outlog << labout << " " << changerate[ran] << " " << quantity[ran] << endl;
	}
	else if (type == "fog") {
		double quantity[20] = { 2,4,6,8,10,12,14,16,18,20 };
		double changerate[20] = { 10,20,30,40,50,60,70,80,90,100 };//Density in the z-direction of the cylinder
		srand(time(0));
		int ran = rand() % 10;
		float R = 1.35;
		int H = 3;
		double density = changerate[ran];
		cloudfilteredSize = 360*(density);

		boost::mt19937 rng;
		rng.seed(static_cast<unsigned int>(time(0)));

		cloudfiltered->points.resize(cloud->points.size() + cloudfilteredSize);//Reset the number of augmentaion points
		cloudfiltered->header = cloud->header;
		cloudfiltered->width = cloud->width + cloudfilteredSize;
		cloudfiltered->height = cloud->height;

		boost::uniform_int<> angle(0, 361);	//Random number for the angle
		boost::variate_generator<boost::mt19937&, boost::uniform_int<>> var_ang(rng, angle);

		pcl::KdTreeFLANN<pcl::PointXYZI> kdtree;

		// Input the random point cloud as a KdTree
		kdtree.setInputCloud(cloud);

		int K = 5;
		
		// Create two vectors to store the index value of the neighbor and the center distance of the neighbor respectively
		std::vector<int> pointIdxNKNSearch(K);
		std::vector<float> pointNKNSquaredDistance(K);

		for (size_t point_i = cloud->points.size(); point_i < cloud->points.size() + cloudfilteredSize;)
		{
			//Simulate a cylinder with a base radius of R and a height of 2H
			float ang_ran = static_cast<float> (var_ang());
			float x = R*cos(ang_ran*PI/ 180.0f);
			float y = R*sin(ang_ran*PI / 180.0f);
				for (float i = 0; i < H&&(point_i < cloud->points.size() + cloudfilteredSize); i += (H/density))
				{
					float z = i;
					cloudfiltered->points[point_i].x = x;
					cloudfiltered->points[point_i].y = y;
					cloudfiltered->points[point_i].z = z;
					/*std::cout << "K nearest neighbor search at (" << cloudfiltered->points[point_i].x
						<< " " << cloudfiltered->points[point_i].y
						<< " " << cloudfiltered->points[point_i].z
						<< ") with K=" << K << std::endl;*/
					if (kdtree.nearestKSearch(cloudfiltered->points[point_i], K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
					{
						float sumintensity = 0;
						for (size_t m = 0; m < pointIdxNKNSearch.size(); ++m)
						{
							sumintensity += cloudfiltered->points[pointIdxNKNSearch[m]].intensity;
						}
						cloudfiltered->points[point_i].intensity = sumintensity / 5;
					}
					pointIdxNKNSearch.clear();
					pointNKNSquaredDistance.clear();
					++point_i;
				}
		}

		double result = 0, x = 0, y = 0, z = 0, d = 0, resparameter = 0;
		resparameter = pow(quantity[ran], 0.7);
		for (int point_i = 0; point_i < cloudfiltered->points.size(); ++point_i)
		{
			x = cloudfiltered->points[point_i].x;
			y = cloudfiltered->points[point_i].y;
			z = cloudfiltered->points[point_i].z;
			d = sqrt(x*x + y * y + z * z);
			result = exp(-0.03*resparameter*d);
			cloudfiltered->points[point_i].intensity = result * cloudfiltered->points[point_i].intensity;
		}
		changelabel(labelPath1, labelPath2, type, h, w, l, x, y, z, ry);
		changecalib(calibPath1, calibPath2, type, h, w, l, x, y, z, ry);
		outlog << labout << " " << changerate[ran] << " " << quantity[ran] << endl;
	}
	else if (type == "symmetry")
	{
		for (int point_i = 0; point_i < cloud->points.size(); ++point_i)
		{
			cloudfiltered->points[point_i].x = cloud->points[point_i].x;
			cloudfiltered->points[point_i].y = -cloud->points[point_i].y;
			cloudfiltered->points[point_i].z = cloud->points[point_i].z;
			cloudfiltered->points[point_i].intensity = cloud->points[point_i].intensity;
		}
		changelabel(labelPath1, labelPath2,type,h,w,l,x,y,z,ry);
		changecalib(calibPath1, calibPath2, type, h, w, l, x, y, z, ry);
		outlog << labout << " " << h << " " << w << " " << l << " " << x << " " << -1 << " " << z << " " << ry<<endl;
    }
	else if (type == "translation")
	{
		double quantity1[20] = { -2,-4,-6,-8,2,4,6,8 };
		double quantity2[20] = { -1,-2,-3,-4,1,2,3,4 };
		srand(time(0));
		int ran1 = rand() % 8;
		int ran2 = rand() % 8;
		cloudfilteredSize = cloud->points.size();
		for (int point_i = 0; point_i < cloud->points.size(); ++point_i)
		{
			cloudfiltered->points[point_i].x = cloud->points[point_i].x+quantity1[ran1];
			cloudfiltered->points[point_i].y = cloud->points[point_i].y+quantity2[ran2];
			cloudfiltered->points[point_i].z = cloud->points[point_i].z;
			cloudfiltered->points[point_i].intensity = cloud->points[point_i].intensity;
		}
		x = -quantity2[ran2];
		z = quantity1[ran1];
		changelabel(labelPath1, labelPath2, type, h, w, l, x, y, z, ry);
		changecalib(calibPath1, calibPath2, type, h, w, l, quantity1[ran1], quantity2[ran2], z, ry);
		outlog << labout << " " << h << " " << w << " " << l << " " << quantity1[ran1] << " " << quantity2[ran2] << " " << 0 << " " << ry << endl;
	}
	else if (type == "scale")
	{
		double quantity[20] = {1.05,1.1,1.15,1.2,1.25};
		srand(time(0));
		int ran = rand() % 5;
		cloudfilteredSize = cloud->points.size();
		for (int point_i = 0; point_i < cloud->points.size(); ++point_i)
		{
			cloudfiltered->points[point_i].x = cloud->points[point_i].x*quantity[ran];
			cloudfiltered->points[point_i].y = cloud->points[point_i].y*quantity[ran];
			cloudfiltered->points[point_i].z = cloud->points[point_i].z*quantity[ran];
			cloudfiltered->points[point_i].intensity = cloud->points[point_i].intensity;
		}
		h = quantity[ran];
		w= quantity[ran];
		l= quantity[ran];
		x= quantity[ran];
		y= quantity[ran];
		z= quantity[ran];
		changelabel(labelPath1, labelPath2, type, h, w, l, x, y, z, ry);
		changecalib(calibPath1, calibPath2, type, h, w, l, x, y, z, ry);
		outlog << labout << " " << quantity[ran] << " " << quantity[ran] << " " << quantity[ran] << " " << quantity[ran] << " " << quantity[ran] << " " << quantity[ran] << " " << ry << endl;
	}
	else if (type == "rotation")
	{
		double quantity[20] = { -PI / 8 ,-PI / 6, -PI / 4 ,PI / 8 ,PI / 6, PI / 4 };
		srand(time(0));
		int ran = rand() % 6;
		cloudfilteredSize = cloud->points.size();
		double yaw = quantity[ran];
		for (int point_i = 0; point_i < cloud->points.size(); ++point_i)
		{
			cloudfiltered->points[point_i].x = cloud->points[point_i].x * cos(yaw)+ cloud->points[point_i].y*sin(yaw);
			cloudfiltered->points[point_i].y = cloud->points[point_i].y*cos(yaw)-cloud->points[point_i].x * sin(yaw);
			cloudfiltered->points[point_i].z = cloud->points[point_i].z;
			cloudfiltered->points[point_i].intensity = cloud->points[point_i].intensity;
		}
		ry = yaw;
		changelabel(labelPath1, labelPath2, type, h, w, l, x, y, z, ry);
		changecalib(calibPath1, calibPath2, type, h, w, l, x, y, z, ry);
		outlog << labout << " " << h << " " << w << " " << l << " " << x << " " << y << " " << z << " " << ry << endl;
	}
	outlog.close();
	return cloudfiltered;
}