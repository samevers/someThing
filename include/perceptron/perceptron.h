#ifndef PERCEPTRON_HEAD__
#define PERCEPTRON_HEAD__
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <gary_common/gary_string.h>
#include <math.h>
using namespace std;


class line_exp{
public:
	line_exp(int n);
	~line_exp();
	vector<double> w;//(4,0.0);
	vector<double> prew;//(4,0.0);
	double b;
};



#endif
