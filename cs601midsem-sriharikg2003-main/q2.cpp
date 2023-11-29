#include<iostream>
#include<cstdlib>
#include<fstream>
#include<iomanip>
#include"q2_helper.h"
using namespace std;
int main(int argc, char* argv[]){
	if(argc !=3)
		exit(0);
	fstream inp;
	int numDataPoints=atoi(argv[1]);
	cout<<"Num data points to be read:"<<numDataPoints<<endl;
	inp.open (argv[2], fstream::in);
	float* data=new float[numDataPoints];
	for(int i=0;i<numDataPoints;i++)
		inp>>setprecision(2)>>data[i];
	inp.close();
	float mean, var;
	ComputeMeanAndVar_V1(data, numDataPoints, &mean, &var);
	printf("ComputeMeanAndVar_V1: mean=%.2f var=%.2f\n",mean, var);
	ComputeMeanAndVar_V2(data, numDataPoints, &mean, &var);
	printf("ComputeMeanAndVar_V2: mean=%.2f var=%.2f\n",mean, var);
	//TODO: Uncomment at most one of the four lines below 
	//Uncomment the below line if you think V1 is the correct answer.
	printf("V1 is correct\n");
	//Uncomment the below line if you think V2 is the correct answer.
	//printf("V2 is correct\n");
	return 0;
}
