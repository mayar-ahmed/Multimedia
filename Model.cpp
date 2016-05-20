//#include "Model.h"
//#include <iostream>
//using namespace std;
////for numbers only
//Model::Model()
//{
//	reset();
//}
//
//void Model::reset()
//{
//	for (int i = 0; i < 129; i++)
//		cumulative[i] = i;
//	frozen = false;
//}
//
//void Model::update(int c)
//{
//	for (int i = c + 1; i < 129; i++)
//	{
//		cumulative[i]++;
//		
//	}
//
//	if (cumulative[128] >= MAX_FREQ) 
//		frozen = true;
//}
//
//prob Model::getProbability(int c)
//{
//	prob p = { cumulative[c], cumulative[c + 1], cumulative[128] };
//	if (!frozen)
//		update(c);
//	
//	return p;
//}
//
//prob Model::getChar(unsigned int scale, int & c)
//{
//	for (int i = 0; i < 128; i++)
//	{
//		if (scale < cumulative[i + 1]) 
//		{
//			c = i;
//
//			prob p = { cumulative[i], cumulative[i + 1], cumulative[128] };
//			if (!frozen)
//				update(c);
//			return p;
//		}
//	}
//}
//
//unsigned int Model:: getCount()
//{
//	return cumulative[128];
//}
//
//Model::~Model()
//{
//}

//for all characters
#include "Model.h"
#include <iostream>
using namespace std;
Model::Model()
{
	reset();
}

void Model::reset()
{
	for (int i = 0; i < 258; i++)
		cumulative[i] = i;
	frozen = false;
}

void Model::update(int c)
{
	for (int i = c + 1; i < 258; i++)
	{
		cumulative[i]++;

	}

	if (cumulative[257] >= MAX_FREQ)
		frozen = true;
}

prob Model::getProbability(int c)
{
	prob p = { cumulative[c], cumulative[c + 1], cumulative[257] };
	if (!frozen)
		update(c);

	return p;
}

prob Model::getChar(unsigned int scale, int & c)
{
	for (int i = 0; i < 257; i++)
	{
		if (scale < cumulative[i + 1])
		{
			c = i;

			prob p = { cumulative[i], cumulative[i + 1], cumulative[257] };
			if (!frozen)
				update(c);
			return p;
		}
	}
}

unsigned int Model::getCount()
{
	return cumulative[257];
}

Model::~Model()
{
}

