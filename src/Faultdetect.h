#include <cmath>
#include <iostream>
using namespace std;
#include <vector>
#include <random>
#include "ssconfig.hpp"

extern vector<double> vVel;
extern vector<double> vKamount;
extern vector<double> vNoiseTs;
extern vector<double> vNoiseK;
class Faultdetect
{
public:
	
	Faultdetect()
		: r_eu(-1, 1)
	{

	}
	void loadTxt(const char * fileName);
	double norm(double x, double y)
	{
		return (sqrt(x*x + y*y));
	}

	bool faultsdetect(vector<vector<double>> positionr,int type)
	{


		//fopen
		vector<double> positionr_x;
		vector<double> positionr_y;
		vector<double> position_x;
		vector<double> position_y; 
		int length = positionr[0].size();
		positionr_x.resize(length);
		positionr_y.resize(length);
		position_x.resize(length);
		position_y.resize(length);

		positionr_x = positionr[0];
		positionr_y = positionr[1];

		position_x[0] = positionr_x[0];
		position_y[0] = positionr_y[0];

		int time;
		double time_step = 0.1;
		int step;
		int integral_ux;
		int integral_uy;
		int rg_k = vNoiseK[type-1];
		vector<double> controlamount;
		vector<double> controlamount_x;
		vector<double> controlamount_y;
		vector<double> node_x;
		vector<double> node_y;
		vector<double> noder_x;
		vector<double> noder_y;
		

		double node_distance;
		double velocity= vVel[type-1];//智能体速度
		for (int i = 1; i < length; i++)
		{
			//controlamount_x[0] = 0;
			//controlamount_y[0] = 0;
			//integral_ux = 0;
			//integral_uy = 0;
			node_distance = norm(positionr_x[i] - positionr_x[i-1], positionr_y[i] - positionr_y[i-1]);
			time = node_distance / velocity;
			step = floor(time / time_step)+1;
			controlamount.resize(step + 1);
			controlamount_x.resize(step + 1);
			controlamount_y.resize(step + 1);
			node_x.resize(step + 1);
			node_y.resize(step + 1);
			noder_x.resize(step + 1);
			noder_y.resize(step + 1);
		

			node_x[0] = position_x[i-1];
			node_y[0] = position_y[i-1];

			noder_x[0] = positionr_x[i-1];
			noder_y[0] = positionr_y[i-1];
			for (int h = 1; h <= step; h++)
			{
				noder_x[h] = (positionr_x[i] - positionr_x[i - 1])/step*h + positionr_x[i-1];
				noder_y[h] = (positionr_y[i] - positionr_y[i - 1])/step*h + positionr_y[i-1];
			}
			for (int j = 1; j <= step; j++)
			{
				//integral_ux = integral_ux + controlamount_x[j - 1] * time_step;
				//integral_uy = integral_uy + controlamount_y[j - 1] * time_step;
				//node_x[j] = integral_ux + controlamount_x[j] * time_step;
				//node_y[j] = integral_uy + controlamount_y[j] * time_step;

				controlamount_x[j-1] = vKamount[type-1]*(noder_x[j-1] - node_x[j-1]) + (noder_x[j]-noder_x[j-1])/time_step + rg_k*r_eu(r_eg);//+噪声
				controlamount_y[j-1] = vKamount[type-1] *(noder_y[j-1] - node_y[j-1]) + (noder_y[j]-noder_y[j-1])/time_step + rg_k*r_eu(r_eg);
				node_x[j] = node_x[j-1] + controlamount_x[j-1] * time_step;
				node_y[j] = node_y[j-1] + controlamount_y[j-1] * time_step;
			}
			position_x[i] = node_x.back();
			position_y[i] = node_y.back();
			
			double err = norm(position_x[i] - positionr_x[i], position_y[i] - positionr_y[i]);
			if (err > vNoiseTs[type-1])
			{
				return false;
			}
		}
		return true;
	}

	std::default_random_engine r_eg;
	std::uniform_real_distribution<double> r_eu;


};
