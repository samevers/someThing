#include "perceptron.h"
line_exp::line_exp(int n)
{
	for(int i = 0;i < n ; i++)
	{
		w.push_back(0.0);
		prew.push_back(0.0);
	}
}
line_exp::~line_exp()
{
}
int distDotLine(vector<double>& dot, line_exp& exp, double& dist)
{
	double L = 0.0;
	if(dot.size() != (exp.w).size())
	{
		cerr << "[ERROR] size of x and w is different." << endl;
		return -1;
	}
	double L1 = 0.0;
	for(int i = 0; i < (exp.w).size();i++)
	{
		L += (exp.w)[i]*(exp.w)[i];
		L1 += (exp.w)[i] * dot[i];
	}
	L1 += exp.b;

	dist = L1/L;
	if(dist < 0)
	{
		dist = 0 - dist;
	}
	cerr << "L1/L = " << L1 << "/"  << L << " = " << dist << endl;

	return 0;
}

int getScores(string line, double& web, double& image, vector<double>& xx)
{
	if(line.find("MAX_CLASS") == -1)
	{
		xx.push_back(0);
		return 0;
	}
	int loc, loc1;
	string tmp;
	if((loc = line.find("image:")) != -1 &&
			(loc1 = line.find(" web:")) != -1 )
	{
		tmp = line.substr(loc1 - loc - 6);
		double score = spaceGary::toDouble(tmp);
		xx.push_back(score);// image's score
	}
	return 0;
}
int isConvergence(line_exp& exp, double& thres) 
{
	double cost;
	double conv;
	for(int i = 0; i < (exp.w).size(); i++)
	{
			conv = (exp.w)[i] - (exp.prew)[i];
			cost += conv * conv;
	}
	if(sqrt(cost) <= thres)
	{
			return 1;
	}

	return 0;
}

int updateParam(line_exp& exp, double& yt, int& y, vector<double>& xx)
{
		if(xx.size() != (exp.w).size())
		{
				cerr << "[ERROR] Size of xx and w is not equal." << endl;
				return -1;
		}
		for(int i =0 ; i < (exp.w).size(); i++)
		{
				exp.prew[i] = exp.w[i];
				exp.w[i] = exp.w[i] + yt * y * xx[i];
		}
		exp.b = exp.b +  y * yt;
		return 0;
}

int main(int args, char* argv[])
{
	string trainfile1,trainfile2,trainfile3,trainfile4;
	trainfile1 = argv[1];
	trainfile2 = argv[2];
	trainfile3 = argv[3];
	trainfile4 = argv[4];
	cerr << "[INFO] Trainfile : " << trainfile1 << endl;
	cerr << "[INFO] Trainfile : " << trainfile2 << endl;
	cerr << "[INFO] Trainfile : " << trainfile3 << endl;
	cerr << "[INFO] Trainfile : " << trainfile4 << endl;
	ifstream infile1;
	ifstream infile2;
	ifstream infile3;
   	ifstream infile4;
	infile1.open(trainfile1.c_str(), ios::in);
	infile2.open(trainfile2.c_str(), ios::in);
	infile3.open(trainfile3.c_str(), ios::in);
	infile4.open(trainfile4.c_str(), ios::in);
	string classFile = argv[5];
	ifstream classinput;
	classinput.open(classFile.c_str(), ios::in);
	if(!infile1 ||!infile2 ||!infile3 || !infile4 || !classinput)
	{
		cerr << "[ERROR] One of the Trainfiles is not exist." << endl;
		return -1;
	}
	// Initialize w,b,yt;
	line_exp exp(4);
	double yt = 0.1;
	double thres = 0.001;

	string line;
	vector<double> xx;
	int y;
	double web_score, image_score;
	while(getline(infile1, line))
	{
		xx.clear();
		spaceGary::StringTrim(line);
		getScores(line, web_score, image_score, xx);
		
		getline(infile2, line);
		spaceGary::StringTrim(line);
		getScores(line, web_score, image_score, xx);
		
		getline(infile3, line);
		spaceGary::StringTrim(line);
		getScores(line, web_score, image_score, xx);
		
		getline(infile4, line);
		spaceGary::StringTrim(line);
		getScores(line, web_score, image_score, xx);
		
		getline(classinput, line);
		spaceGary::StringTrim(line);
		if(line == "1")
		{
				y = 1;
		}else
		{
				y = -1;
		}

		//
		if(exp.w.size() != xx.size())
		{
				cerr << "[ERROR] Size of xx and exp is not equal." << endl;
				continue;
		}
		double L = 0.0;
		for(int i = 0; i < (exp.w).size();i++)
		{
				L = (exp.w)[i] * xx[i];
		}
		L += exp.b;
		L = y * L;
		if(L <= 0)
		{
				updateParam(exp, yt, y, xx);
		}
		// Until convergence
		if(isConvergence(exp, thres))
		{
				break;
		}
		continue;


/*
		for(int i =0 ;i < xx.size(); i++)		
		{
			cerr << xx[i] << " ";
		}
		cerr << endl;
*/
	}

	// Output parameters
	cout << "w = ";
	for(int i = 0; i < exp.w.size(); i++)
			cout << exp.w[i] << " ";
	cout << endl;
	cout << "b = " << exp.b << endl;

	infile1.close();
	infile2.close();
	infile3.close();
	infile4.close();
	classinput.close();

	return 0;
}
