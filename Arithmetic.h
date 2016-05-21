#ifndef ARTH_H
#define ARTH_H

#include <string>
#include <stdio.h>
#include <fstream>
#include "Model.h"
#include <vector>
using namespace std;

typedef 
class Arithmetic
{
private:
	//to make sure that calculations don't get out of unsigne dint range
	
	int CODE_VALUE_BITS_ = (std::numeric_limits<unsigned int>::digits + 3) / 2;
	int FREQUENCY_BITS_ = std::numeric_limits<unsigned int>::digits - CODE_VALUE_BITS_ ; //max total cumulative frequencey
	unsigned int MAX_CODE = (unsigned int(1) << CODE_VALUE_BITS_) - 1;
	//instead of setting them with 0x800000 , 0x400000  and 0xc000000 we scale them based on new precision
	const unsigned int ONE_FOURTH = unsigned int(1) << (CODE_VALUE_BITS_ - 2);;
	 const unsigned int ONE_HALF = 2 * ONE_FOURTH;
	 const unsigned int  THREE_FOURTHS = 3 * ONE_FOURTH;
	
	//check for outing bits
	unsigned char mask; 
	char next_byte; 

	//check for inputing bits
	unsigned char in_mask;
	unsigned char current_byte;
	

	ofstream outfile;
	ifstream infile;
	ifstream infile2;

	int indx;
	long int length;
	
public:
	Arithmetic();
	void compress(Model &m , int number);
	void decompress(Model &m ,int number);
	void output_bit(bool bit, int &pending);
	void putBit(bool value);
	void putByte(char c);

	bool getBit();
	unsigned char getByte();

	~Arithmetic();
};

#endif

