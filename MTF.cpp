#include "MTF.h"


MTF::MTF()
{
	reset();
}

void MTF::reset()
{
	for (int i = 0; i < 256; i++)
		arr[i] = i;
}
void MTF::encode(string inFile) //file taht it reads from
{
	ifstream input;
	ofstream output;
	output.open("mtfEnc.txt");
	input.open(inFile);
	std::string read((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
	string msg = read;

	for (int i = 0; i <(int)msg.size(); i++)
	{
		int c = msg[i];
		if (c < 0)
			c += 256;
		for (int j = 0; j < 256; j++)
		{
			if (arr[j] == c)
			{
				output << j <<" ";
				movetofront(j);
				break;
			}
		}


	}

}

void MTF::movetofront(int indx)
{
	int newz = arr[indx];
	for (int i = indx - 1; i >= 0; i--)
	{
		arr[i + 1] = arr[i];
	}
	arr[0] = newz;

}

void MTF::printArr()
{
	for (int i = 0; i < 256; i++)
	{
		cout << char(arr[i]) << " ";
	}
	cout << endl;
}
void MTF::decode(string inFile)
{
	reset();
	ifstream input;
	ofstream out;
	out.open("mtfDec.txt");
	input.open(inFile);
	int x;
	while (input >> x)
	{
		int newc = arr[x];
		out << char(newc);
		movetofront(x);
	}

	out.close();
}
MTF::~MTF()
{
}
