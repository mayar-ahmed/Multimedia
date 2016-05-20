#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <iomanip>
#include <string>
#include <queue>
#include <iterator>
#include <cmath>
#include <math.h>
#include <bitset>
#include <sstream>
#include <fstream>
#include<set>
#include "Model.h"
#include "Arithmetic.h"
#include "MTF.h"
#include "bwt.h"

using namespace std;


bool compare2(string file1 , string file2)
{
	std::ifstream ifs(file1);
	std::string read1((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	ifs.close();

	ifstream ifs2(file2);
	std::string read2((std::istreambuf_iterator<char>(ifs2)), (std::istreambuf_iterator<char>()));
	ifs2.close();

	if (read1 == read2)
		return true;

	return false;
}


int main(){
	

	/*ofstream outfile;
	outfile.open("testunicode2.txt");
	outfile << input_message<<endl;
	outfile.close();
*/
	

	
	//---------Encoding-----------//

	//get message we need to encode
	string input_message = "";
	std::ifstream ifs("encoded.txt");
	std::string read((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	input_message = read;
	
	//transform to bwt
	bwt b;
	string encode = b.BWT(input_message);
	ofstream out("bwt.txt"); //bwt encoded in bwr.txt
	out << encode;
	out.close();

	//after burrows wheeler, mtf
	MTF mt;
	mt.encode("bwt.txt");

	//arithmetic encode the mtf encoded file
	Model m;
	Arithmetic a;
	a.compress(m, "mtfEnc.txt"); 



	//---------Decoding-----------//

	//decode arithmetic
	m.reset();
	a.decompress(m);
	//reverse mtf encoding
	mt.decode("decoded.txt");

	//final stage :reverse bwt to get original file
	ifstream in2("mtfDec.txt");
	string read2((istreambuf_iterator<char>(in2)), (istreambuf_iterator<char>()));
	string bwte = read2;
	string decode2 = b.inverseBWT(bwte);

	ofstream outfile("bwt_inverse.txt");
	outfile << dec;
	outfile.close();

	//compare original file with bwt inverse
	cout << compare2("cleopatra.txt", "bwt_inverse.txt");
	


}

