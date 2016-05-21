#ifndef BT
#define BT
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
#include<iomanip>
#include<set>
#include<iterator>
#include<stack>
#include<map>
#include <streambuf>
using namespace std;


class bwt{
	int block_size = 60000;
	int inverse_block_size = block_size + 1;
public:
	vector<pair<int, int>> BWT_blockmaker(string input);
	vector<vector<char>> rotation(vector<pair<int, int>> blocks, string input);
	vector<pair<char, int>> number(vector<char> block);
	vector<vector<char>> IBWT_blockmaker(string input);
	string BWT(string input);
	string inverseBWT(string input);
	bool cmp(pair<char, int> a, pair<char, int>b);
	bool compareblocks(vector<vector<char>> a, vector<vector<char>> b);
};
#endif