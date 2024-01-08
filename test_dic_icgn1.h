#pragma once
#pragma once



#include "OpenCorr/oc_array.h"
#include "OpenCorr/oc_image.h"
#include "OpenCorr/oc_poi.h"
#include "OpenCorr/oc_subset.h"


	//structure for brute force searching
	//struct KeypointIndex
	//{
	//	int kp_idx; //index in keypoint queue
	//	float distance; //Euclidean distance to the POI
	//};

class test_dic_icgn1
	{
	public:


		//int subset_radius_x, subset_radius_y;
		int thread_number; //OpenMP thread number

		 test_dic_icgn1(const cv::Mat leftImage, const cv::Mat rightImage, const int windowSize);
		 ~test_dic_icgn1();

		//void setImages(Image2D& ref_img, Image2D& tar_img);
		//void setSubsetRadius(int radius_x, int radius_y);

		//virtual void prepare();
		//virtual void compute(POI2D* poi) = 0;
		//virtual void compute(std::vector<POI2D>& poi_queue) = 0;
		 bool DIC_ICGN_1st(const int x0f, const int y0f, double& x0g, double& y0g, double* deformPara);
	    //private:
		cv::Mat _LeftImage;
		cv::Mat _RightImage;
		int _windowSize;
};







