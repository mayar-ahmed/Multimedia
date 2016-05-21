#ifndef M_TF
#define M_TF
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class MTF
{
private:
	int arr[256];
public:
	MTF();
	void reset();
	void encode(string inFile);
	void decode(string inFile);
	void movetofront(int indx);
	void printArr();
	~MTF();
};
#endif
