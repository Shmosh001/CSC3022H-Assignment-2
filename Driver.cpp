/* Assignment 2
 * Driver.cpp
 * Osher Shuman
 * SHMOSH001
 * Date Due: 16/3/2015
 */
#include <iostream>
#include "VolImage.h"
#include <sstream>

int main(int argc, char* argv[])
{
	using namespace std;
	SHMOSH001::VolImage vImg;


	if(argc < 3)
	{
		string fileName = (string)(argv[1]);
		vImg.readImages(fileName);
		int fileSize = vImg.volImageSize();
		cout << "Number of bytes required: " << fileSize << endl;
	}


	else
	{
		string fileName = (string)(argv[1]);
		vImg.readImages(fileName);
		string option = (string)argv[2];

		//diffmap
		if(option == "-d")
		{
			int index1;
			int index2;

			istringstream(argv[3]) >> index1; //convert char to int
			istringstream(argv[4]) >> index2; //convert char to int

			string prefixName = (string)argv[5];
			vImg.diffmap(index1, index2, prefixName);
		}

		//extract method
		else if(option == "-x")
		{
			int index;
			istringstream(argv[3]) >> index; //convert char to int
			string prefixName = (string)argv[4]; //type cast char to string
			vImg.extract(index, prefixName);
		}

		//bonus question = read a line
		else if(option == "-g")
		{
			int index;
			istringstream(argv[3]) >> index; //convert char to int
			string prefixName = (string)argv[4]; //type cast char to string
			vImg.extraCredit(index, prefixName);
		}


		//incorrect input
		else
		{
			cout << "Input Error" << endl;
		}

	}





	return 0;

}


