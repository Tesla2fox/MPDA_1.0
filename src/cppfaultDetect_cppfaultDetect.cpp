//#include "cppfaultDetect_faultdetect.h"
#include "cppfaultDetect_cppfaultDetect.h"
#include "Faultdetect.h"
#include <iostream>
#include <vector>
#include "ssconfig.hpp"

JNIEXPORT jint JNICALL Java_cppfaultDetect_cppfaultDetect_fault_1detect
(JNIEnv *env, jclass, jcharArray fname_char_array, jobjectArray position_array, jint k) {
	jchar *jchar_pointer = env->GetCharArrayElements(fname_char_array, NULL);
	int len = env->GetArrayLength(fname_char_array);
	char * buf = new char[len + 1];
	for (int i = 0; i < len; i++) {
		buf[i] = jchar_pointer[i];
	}
	buf[len] = '\0';
	Faultdetect they;
	they.loadTxt(buf);

	std::cout << "[faultDetect] input type is " << k++ << endl;
	//std::cout <<"vel [7]"<<vVel[7]<<std::endl;
	//std::cout << "vK [7]"<<vKamount[7] << std::endl;
	//std::cout << vNoise[7] << std::endl;

	//jint *position_pointer = env->GetDoubleArrayElements(position_array, NULL);


	jsize arryCount = env->GetArrayLength(position_array);

	//std::cout << "0-0" << arryCount << endl;
	jdoubleArray xArry = jdoubleArray(env->GetObjectArrayElement(position_array, 0));
	jdouble * jdouble_xPtr = env->GetDoubleArrayElements(xArry, NULL);
	int len_x = env->GetArrayLength(xArry);
	
	jdoubleArray yArry = jdoubleArray(env->GetObjectArrayElement(position_array, 1));
	jdouble * jdouble_yPtr = env->GetDoubleArrayElements(yArry, NULL);
	int len_y = env->GetArrayLength(yArry);

	vector<vector<double>> position;
	vector<double> vx;
	vector<double> vy;
	for (size_t i = 0; i < len_x; i++)
	{
		vx.push_back(jdouble_xPtr[i]);
		vy.push_back(jdouble_yPtr[i]);
		//std::cout << "x  = " << vx.back()
		//	<< "y = " << vy.back()
		//	<< endl;
	}
	position.push_back(vx);
	position.push_back(vy);
	delete(buf);
//	cout << "readSuccess" << endl;
	auto	answer = they.faultsdetect(position, k);
	if (answer)
	{
		return 1;
	}
	else
	{
	//	std::cout << "faultdetect" << endl;
		return 0;
	}

	return 0;


}