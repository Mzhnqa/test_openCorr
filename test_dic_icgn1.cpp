#include "test_dic_icgn1.h"
#include "OpenCorr/opencorr.h"
#include <fstream>
#include<vector>


using namespace opencorr;
using namespace std;
test_dic_icgn1::test_dic_icgn1(const cv::Mat leftImage, const cv::Mat rightImage, const int windowSize)
{
	_LeftImage = leftImage;
	_RightImage = rightImage;
}

test_dic_icgn1::~test_dic_icgn1()
{

}
bool test_dic_icgn1::DIC_ICGN_1st(const int x0f, const int y0f, double& x0g, double& y0g, double* deformPara)
{
	//cv::Mat imgRef = _LeftImage;//mat类型，Image2D类型的需要地址或者大小，是否重载Image2D
	//cv::Mat imgSech = _RightImage;
	string ref_image_path = ".../oht_cfrp_0.bmp"; 
	string tar_image_path = ".../oht_cfrp_4.bmp"; 
	Image2D ref_img(ref_image_path);
	Image2D tar_img(tar_image_path);

	int templSize = _windowSize;
	int HalfSize = templSize / 2;
	int xStart = x0f - HalfSize;  // 子区左上角
	int yStart = y0f - HalfSize;  // 子区左上角

	//create instances to read and write csv files
	string file_path;
	string delimiter = ",";
	ofstream csv_out; //instance for output calculation time
	IO2D in_out; //instance for input and output DIC data
	in_out.setDelimiter(delimiter);
	in_out.setHeight(ref_img.height);
	in_out.setWidth(ref_img.width);

	//set OpenMP parameters
	int cpu_thread_number = omp_get_num_procs() - 1;
	omp_set_num_threads(cpu_thread_number);

	//set DIC parameters
	int subset_radius_x = 16;
	int subset_radius_y = 16;
	int max_iteration = 10;
	float max_deformation_norm = 0.001f;
	vector<POI2D> poi_queue;


	////set POIs  
	//Point2D upper_left_point(xStart, yStart);
	//vector<POI2D> poi_queue;
	//int poi_number_x = 100;
	//int poi_number_y = 300;
	//int grid_space = 2;//网格间距

	////store POIs in a queue
	//for (int i = 0; i < poi_number_y; i++)
	//{
	//	for (int j = 0; j < poi_number_x; j++)
	//	{
	//		Point2D offset(j * grid_space, i * grid_space);
	//		Point2D current_point = upper_left_point + offset;
	//		POI2D current_poi(current_point);
	//		poi_queue.push_back(current_poi);
	//	}
	//}//单点的话不用这么多感兴趣点

	//选择一个点
	POI2D poi= POI2D(x0f,y0f);
	poi_queue.push_back(poi);
	
	//ICGN with the 1st order shape function
	ICGN2D1* icgn1 = new ICGN2D1(subset_radius_x, subset_radius_y, max_deformation_norm, max_iteration, cpu_thread_number);
	icgn1->setImages(ref_img, tar_img);
	icgn1->prepare();
	icgn1->compute(poi_queue);

	//save the calculated dispalcements  
	file_path = tar_image_path.substr(0, tar_image_path.find_last_of(".")) + "_fftcc_icgn1_r16.csv";
	in_out.setPath(file_path);
	in_out.saveTable2D(poi_queue);

	//save the full deformation vector  
	file_path = tar_image_path.substr(0, tar_image_path.find_last_of(".")) + "_fftcc_icgn1_r16_deformation.csv";
	in_out.setPath(file_path);
	in_out.saveDeformationTable2D(poi_queue);

	//save the map of u-component   
	file_path = tar_image_path.substr(0, tar_image_path.find_last_of(".")) + "_fftcc_icgn1_r16_u.csv";
	in_out.setPath(file_path);
	char var_char = 'u';
	in_out.saveMap2D(poi_queue, var_char);

	//save the map of v-component  
	file_path = tar_image_path.substr(0, tar_image_path.find_last_of(".")) + "_fftcc_icgn1_r16_v.csv";
	in_out.setPath(file_path);
	var_char = 'v';
	in_out.saveMap2D(poi_queue, var_char);

	delete icgn1;


}

int main()
{
	string ref_image_path = "D:/cv/DIC/OpenCorr-main/samples/oht_cfrp_0.bmp";
	string tar_image_path = "D:/cv/DIC/OpenCorr-main/samples/oht_cfrp_4.bmp";
	Image2D ref_img(ref_image_path);
	Image2D tar_img(tar_image_path);

	//int _windowSize;
	int x0f = 30;
	int y0f = 30;


	//int templSize = _windowSize;
	//int HalfSize = templSize / 2;
	//int xStart = x0f - HalfSize;  // 子区左上角
	//int yStart = y0f - HalfSize;  // 子区左上角

	//create instances to read and write csv files
	string file_path;
	string delimiter = ",";
	ofstream csv_out; //instance for output calculation time
	IO2D in_out; //instance for input and output DIC data
	in_out.setDelimiter(delimiter);
	in_out.setHeight(ref_img.height);
	in_out.setWidth(ref_img.width);

	//set OpenMP parameters
	int cpu_thread_number = omp_get_num_procs() - 1;
	omp_set_num_threads(cpu_thread_number);

	//set DIC parameters
	int subset_radius_x = 16;
	int subset_radius_y = 16;
	int max_iteration = 10;
	float max_deformation_norm = 0.001f;
	vector<POI2D> poi_queue;
	//选择一个点
	POI2D poi = POI2D(x0f, y0f);
	poi_queue.push_back(poi);

	//ICGN with the 1st order shape function
	ICGN2D1* icgn1 = new ICGN2D1(subset_radius_x, subset_radius_y, max_deformation_norm, max_iteration, cpu_thread_number);
	icgn1->setImages(ref_img, tar_img);
	icgn1->prepare();
	icgn1->compute(poi_queue);

	//save the calculated dispalcements  
	file_path = tar_image_path.substr(0, tar_image_path.find_last_of(".")) + "_icgn1_r16.csv";
	in_out.setPath(file_path);
	in_out.saveTable2D(poi_queue);

	//save the full deformation vector  
	file_path = tar_image_path.substr(0, tar_image_path.find_last_of(".")) + "_icgn1_r16_deformation.csv";
	in_out.setPath(file_path);
	in_out.saveDeformationTable2D(poi_queue);

	//save the map of u-component   
	file_path = tar_image_path.substr(0, tar_image_path.find_last_of(".")) + "_icgn1_r16_u.csv";
	in_out.setPath(file_path);
	char var_char = 'u';
	in_out.saveMap2D(poi_queue, var_char);

	//save the map of v-component  
	file_path = tar_image_path.substr(0, tar_image_path.find_last_of(".")) + "_icgn1_r16_v.csv";
	in_out.setPath(file_path);
	var_char = 'v';
	in_out.saveMap2D(poi_queue, var_char);

	//vector<Point2D> loadPoint2D(string file_path);
	delete icgn1;
}