//CS601:Endsem, Autumn23, Part-II. This part has 2 questions indicated with comment lines that have Q. Answer as instructed. DONOT MODIFY THIS FILE.
#include<iostream>
#include<cassert>
#include "Ball.h"
void ReadMembers(const Ball& a){assert(a.pi==3.0);assert(a.radius==1);}	
int main(){
	//Q1 (3 points). Modify the constructors of BasketBall and Ball classes so that Ball part of Basketball is correctly initialized when the following code is executed.
	//By correctly initialized, we mean that the member color is initialized with 100 and member radius is initialized with 1, and pi is initialized with 3.0. Note that 3.0 is different from 3.
 	BasketBall a(1,100);
	ReadMembers(a);
	//Q2 (1 point). Modify BasketBall and Ball classes so that the following lines prints 100 100 (two hundreds separated by a blankspace)
	Ball *b=&a;
	a.Print(); 
	cout<<" ";
	b->Print();
}
