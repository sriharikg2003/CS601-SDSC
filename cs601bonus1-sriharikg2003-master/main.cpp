//CS601BOnus1: Answer questions as asked below in lines that have comments beginning with Q
#include<iostream>
#include<cassert>
#include<cstring>
#include"myvec.h"
using namespace std;

int main() {
	//Q1: create a MyVec object v1. v1's member 'data' has type char. The object v1 must be able to store exactly 4 C-style strings./
	MyVec<char*> v1(4);

	
	//DONOT delete or edit the following line
	assert(v1.GetVecLen() == 4);

	//Q2: Initialize v1 such that it contains the following 4 strings: "RED","BLUE", "GREEN","YELLOW"/
	v1[0] = "RED";
	v1[1] = "BLUE";
	v1[2] = "GREEN";
	v1[3] = "YELLOW";
	
	//DONOT delete or edit the following lines
	for(int i=0;i<v1.GetVecLen();i++)
		cout<<v1[i]<<endl;

	/*Q3: Implement predecrement and postdecrement methods of MyVec. v1-- or --v1 should overwrite with previous alphabet e.g., if data[0]="RED" earlier, then after v1-- or --v1 we should have data[0]="QDC" and so on.. Note that each letter now is the previous letter in the alphabet. Assume capital letters only and you don't have letter 'A' in input. */
	v1--;

	//DONOT delete or edit the following lines
	assert(!strcmp("QDC",v1[0]));
	MyVec<char*> v2;

	//Q4: Implement copy assignment operator of MyVec class so that a statement such as v2=v1 is possible./
	
	
	//DONOT delete or edit the following lines
	assert(!strcmp(v1[0], v2[0]));
	assert(!strcmp(v1[1], v2[1]));
	assert(!strcmp(v1[2], v2[2]));
	assert(!strcmp(v1[3], v2[3]));

	/*Q5: Implement MyVec class method for overriding - operator.  v1-v2 should return a MyVec object that contains strings that are present in v1 but not in v2 (complement of a set) */


}