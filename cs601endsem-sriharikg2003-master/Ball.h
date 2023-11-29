//CS601:Endsem, Autumn23, Part-II. This is the helper file. YOUR MODIFICATIONS TO THIS FILE MUST BE LIMITED TO ATMOST ONE WORD AND NO MORE
#include<iostream>
using namespace std;

class Ball { 
private: 
	const float pi ; 
	int radius; 
public: 
	Ball(); 
	Ball(int r);
	void SetRadius(int rad);
	const Ball& operator=(const Ball& b);
	virtual void Print() {
	cout << radius; 
	}
        friend void ReadMembers(const Ball& a);
};
 
class BasketBall: public Ball { 
private: 
	int color; 
public: 
	BasketBall(int rad, int col);
	void Print() {
		cout << color; 
	} 
}; 


