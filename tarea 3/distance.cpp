// Online C++ compiler to run C++ program online
#include <iostream>
#include <math.h>
using namespace std;
float distance(int x1, int y1 , int z1, int x2, int y2, int z2){
	float distance1=(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2));
	float d=sqrt(distance1);
	return d;
}
	int main() {
		
		cout<<distance(20,35,40,5,7,9);
		
		
		return 0;
	}
