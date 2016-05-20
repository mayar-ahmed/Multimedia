#include "Arithmetic.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>

using namespace std;
Arithmetic::Arithmetic()
{
	mask = 0x80;
	next_byte = 0x0;
	current_byte = 0;
	in_mask = 0x01;
	indx = 0;
	
}

void Arithmetic::putBit(bool value)
{
	//cout << value;
	if (value)
		next_byte |= mask;
	mask >>= 1;
	
	if (!mask)
	{
		putByte(next_byte);
		next_byte = 0;
		mask = 0x80;
	}
}

void Arithmetic::putByte(char c)
{
	outfile.write(reinterpret_cast<char*>(&c), sizeof(c));
	
}
void Arithmetic::output_bit(bool bit, int & pending)
{
	putBit( bit);
	while (pending != 0)
	{
		putBit(!bit);
		pending--;
	}
}

void Arithmetic::compress(Model &m, string file)
{
	string msg="";
	std::ifstream ifs(file);
	std::string read((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	msg = read;
	//cout << msg;
	
	// fopen_s(p,"encoded.bin","w");
	//cout << msg << endl;
	outfile.open("example.bin" , ios::binary);
	char a = 254;
	msg += a;
	int pending_bits = 0;
	unsigned int low = 0;
	unsigned int high = MAX_CODE;
	int i = 0;
	for (;;)
	{
		
		int c = msg[i];
		if (c <0)
			c += 256;

		//cout << char(c);
		
		if (i == msg.size())	
			c = 256;
		

		prob p = m.getProbability(c);
		unsigned int range = high - low + 1;
		high = low + (range * p.high / p.count) - 1;
		low = low + (range * p.low / p.count);

		for (;;) {
			if (high <  ONE_HALF)
				output_bit(0, pending_bits);
			else if (low >= ONE_HALF)
			{
				output_bit(1, pending_bits);
				low -= ONE_HALF;
				high -= ONE_HALF;
			}
			else if (low >= ONE_FOURTH && high < THREE_FOURTHS) {
				pending_bits++;
				low -= ONE_FOURTH;
				high -= ONE_FOURTH;
			}
			else
				break;
			high <<= 1;
			high++;
			low <<= 1;
			//high &= MAX_CODE;
			//low &= MAX_CODE;
		}
		//for (;;) { //check if low goes above 0.5 or high below 0.5 of range or they are about to
		//	if (high < ONE_HALF) //MSB of high drops below 1
		//	{//put_bit_plus_pending(0, pending_bits); output msb (0)
		//		output_bit(0, pending_bits);
		//		low <<= 1;
		//		high <<= 1;
		//		high |= 1;
		//	}
		//	else if (low >= ONE_HALF)
		//	{//put_bit_plus_pending(1, pending_bits); //MSB of low above 1 output 1
		//		output_bit(1, pending_bits);
		//		low <<= 1;
		//		high <<= 1;
		//		high |= 1;
		//	}
		//	else if (low >= ONE_FOURTH && high < THREE_FOURTHS) { //near convergence state high is 10 and low 01
		//		//this will produce 100000 or 0111111 
		//		pending_bits++;
		//		//discard second bit of high and low and retain the first
		//		low <<= 1;
		//		low &= 0x7FFFFFFF;
		//		high <<= 1;
		//		high |= 0x80000001;
		//	}
		//	else
		//		break;
	
		//}
		if (c == 256) //256 is the special EOF code
			break;
		i++;
	}
	// to make sure that end of file completes 8 bits
	pending_bits++;
	if (low < ONE_FOURTH)
	{
		output_bit(0, pending_bits);
		//put_bit_plus_pending(0, pending_bits);
	}
	else
	{
		output_bit(1, pending_bits);
		//put_bit_plus_pending(1, pending_bits);
	}

	outfile.close();
}

void Arithmetic::decompress(Model &m)
{
	
	infile2.open("example.bin", ios::in | ios::binary);
	outfile.open("decoded.txt" );


	infile2.seekg(0, ios::end);
	length = infile2.tellg();
	infile2.seekg(0, ios::beg);
	/*p = new char[length];
	infile.read(p, length);

	for (int i = 0; i < length; i++)
	{
		cout << p[i] << endl;
	}*/
	

	unsigned int high = MAX_CODE;
	unsigned int low = 0;
	unsigned int value = 0;
	cout << endl << endl;
	for (int i = 0; i < CODE_VALUE_BITS_; i++) {
		value <<= 1;
		value += getBit() ? 1 : 0; //shift first 32 inputs in the value , after decoding shift msb and replace it with 
		// a bit from the file
	}

	for (;;) {

		unsigned int range = (high - low )+ 1;
		unsigned int count = ((value - low + 1) * m.getCount() - 1) / range; //reverse encoding 

		int c= 0;
		prob p = m.getChar(count, c);

	
		if (c < 0)
			c += 256;
		//cout << c << endl;
		if (c == 254)
		{
			//outfile << char(c);
			break;
		}
			
	
		outfile << (char)c; //output decoded character
		
		//set new high and low
		high = low + (range*p.high) / p.count - 1;
		low = low + (range*p.low) / p.count;

		for (;;) {
			if (high < ONE_HALF) {
				//do nothing, bit is a zero
			}
			else if (low >= ONE_HALF) {
				value -= ONE_HALF;  //subtract one half from all three code values
				low -= ONE_HALF;
				high -= ONE_HALF;
			}
			else if (low >= ONE_FOURTH && high < THREE_FOURTHS) {
				value -= ONE_FOURTH;
				low -= ONE_FOURTH;
				high -= ONE_FOURTH;
			}
			else
				break;
			low <<= 1;
			high <<= 1;
			high++;
			
				value <<= 1;
				value += getBit() ? 1 : 0;
			
		}

		//for (;;) {
		//	if (low >= ONE_HALF || high < ONE_HALF) {
		//		low <<= 1;
		//		high <<= 1;
		//		high |= 1;
		//		value <<= 1;
		//		value += getBit() ? 1 : 0; //if low or high converges shift bit and get last one
		//	}
		//	else if (low >= ONE_FOURTH && high < THREE_FOURTHS) {
		//		low <<= 1;
		//		low &= 0x7FFFFFFF;
		//		high <<= 1;
		//		high |= 0x80000001;
		//		value <<= 1;
		//		value += getBit() ? 1 : 0;
		//	}
		//	else
		//		break;
		//}
	}

	infile2.close();
	outfile.close();

}

unsigned char Arithmetic::getByte()
{
	char x = ' ';
	infile2.read(&x, sizeof(x));
	
	 return x;
}

bool Arithmetic::getBit()
{
	if (in_mask == 1)
	{
		/*if (indx > length)
		{
			return 0;
		}*/
		current_byte =getByte();
		//cout << (int)current_byte << endl;
		indx++;
		
		
		//indx++;

	/*	if (current_byte < 0) {
			if (CODE_VALUE_BITS_ <= 0)
				cout << "EOF";
			else
				CODE_VALUE_BITS_-= 8;
		}*/
		in_mask = 0x80;
	}
	else
		in_mask >>= 1;

	//cout << ((current_byte & in_mask) != 0);
	return (current_byte & in_mask) != 0;

}
Arithmetic::~Arithmetic()
{
}
