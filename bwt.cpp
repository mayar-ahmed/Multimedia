#include"bwt.h"

bool compareblocks(vector<vector<char>> a, vector<vector<char>> b){
	return a == b;
}

vector<pair<int, int>> bwt::BWT_blockmaker(string input)
{
	vector<pair<int, int>> blocks;
	int current = 0;
	for (int i = 0; i + block_size - 1 <= input.size(); i += block_size)
	{

		blocks.push_back(pair<int, int>(i, i + block_size - 1));
		current = i + block_size;
	}
	if (current + block_size > (input.size() - 1) && current <input.size())
	{


		blocks.push_back(pair<int, int>(current, input.size() - 1));
	}
	return blocks;

}
//actual rotation
vector<vector<char>> bwt::rotation(vector<pair<int, int>> blocks, string input)
{
	vector<vector<char>> newblocks;
	for (int i = 0; i < blocks.size(); i++)
	{
		set<vector<char>> rotations;
		int blocksize = blocks[i].second - blocks[i].first + 1;
		int start = blocks[i].first;
		int end = blocks[i].second + 1;
		vector<char> temp2(input.begin() + start, input.begin() + end);
		temp2.push_back('$');
		rotations.insert(temp2);


		while (start<end) //making and sorting rotations
		{
			start++;
			vector<char> temp(input.begin() + start, input.begin() + end);
			temp.push_back('$');
			temp.push_back(input[start - 1]);

			rotations.insert(temp);

		}
		vector<char> rot;
		set<vector<char>>::iterator it;
		int k = 0;
		for (it = rotations.begin(); it != rotations.end(); ++it, ++k)
		{
			vector<char> a = *it;
			rot.push_back(a.back());
		}
		newblocks.push_back(rot);
	}
	return newblocks;
}
vector<pair<char, int>> bwt::number(vector<char> block){
	vector<pair<char, int>> num;
	map<char, int> match;
	for (int i = 0; i < block.size(); i++)
	{

		num.push_back(pair<char, int>(block[i], match[block[i]]));
		match[block[i]]++;
	}
	return num;
}
bool bwt::cmp(pair<char, int> a, pair<char, int>b){
	return (a.first == b.first) && (a.second == b.second);
}
vector<vector<char>> bwt::IBWT_blockmaker(string input){
	vector<vector<char>> blocks;
	int current = 0;
	for (int i = 0; i + inverse_block_size - 1 < input.size(); i += inverse_block_size)
	{
		vector<char>temp(input.begin() + i, input.begin() + i + inverse_block_size);
		blocks.push_back(temp);
		//blocks.insert(blocks.end(), input.begin() + i, input.begin() + i + block_size-1);
		current = i + inverse_block_size;
	}
	if (current + inverse_block_size > (input.size() - 1) && current <input.size())
	{


		//blocks.push_back(pair<int, int>(current, input.size() - 1));
		vector<char>temp(input.begin() + current, input.end());
		blocks.push_back(temp);
		//blocks.insert(blocks.end(), input.begin()+current, input.end());
	}
	return blocks;
}
string bwt::inverseBWT(string input){

	vector<vector<char>> blocks = IBWT_blockmaker(input);

	string all;
	for (int i = 0; i < blocks.size(); i++)
	{
		vector<pair<char, int>> last = number(blocks[i]);
		sort(blocks[i].begin(), blocks[i].end());  //first column of the rotation table
		vector<pair<char, int>> first = number(blocks[i]);
		pair<char, int> value('$', 0);
		vector<char> answer;
		while (answer.size()<blocks[i].size())
		{

			int index = find(last.begin(), last.end(), value) - last.begin();
			value = first[index];
			answer.push_back(value.first);
			first[index].first = NULL;
			last[index].first = NULL;
			first[index].second = NULL;
			last[index].second = NULL;
		}
		answer.pop_back();
		all.insert(all.end(), answer.begin(), answer.end());
	}
	return all;
}

string bwt::BWT(string input){

	
	vector<vector<char>> result=rotation(BWT_blockmaker(input), input);
	string bwt;
	for (int i = 0; i < result.size();i++)
	for (int m = 0; m < result[i].size(); m++)
		bwt += result[i][m];
	return bwt;
}
