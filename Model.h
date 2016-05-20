#ifndef MOD_H
#define MOD_H
struct prob {
	unsigned int low;
	unsigned int high;
	unsigned int count;
};

class Model
{
private:
	const int frequency_bits = 15;
	const unsigned int  MAX_FREQ = (unsigned int (1) << frequency_bits) - 1;
public:
	bool frozen = false;
	//unsigned int cumulative[129];//128 has sum of all ranges
	unsigned int cumulative[258]; //cumulative[257] has sum of all ranges
								  // cumulative[256] is end of file symbol

	Model();
	void reset();
	prob getProbability(int c);
	prob getChar(unsigned int scale, int & c);
	unsigned int getCount();
	void update(int c);
	
	~Model();
};

#endif