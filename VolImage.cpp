/* Assignment 2
 * VolImage.cpp
 * Osher Shuman
 * SHMOSH001
 * Date Due: 16/3/2015
 */

#include "VolImage.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>


namespace SHMOSH001
{

	//default constructor
	VolImage::VolImage()
	{
		using namespace std;
		width = 0;
		height = 0;

	}

	//destructor
	VolImage::~VolImage()
	{
		int numImages = slices.size();
		for(int n = 0; n < numImages; n++)
		{
			for(int r = 0; r < height; r++)
			{
				delete slices[n][r]; //delete pointer to each row of raw file
			}
			delete slices[n]; //delete pointer to each raw file
		}
	}

	//readImages method
	bool VolImage:: readImages(std::string baseName)
	{
		using namespace std;
		//string to store path of file
		string dataPath = "brain_mri_raws/" + baseName + ".dat";
		//ifstream to read file. convert string to char
		ifstream dataFile (dataPath.c_str());


		if(dataFile.is_open())
		{
					string line;
					getline(dataFile, line); //gets line from file and stores in string line
					stringstream ss; //used later to convert string to int
					ss.str(line);
					string item;
					int num;
					vector<int> data;
					//split  string by a whitespace
					while(getline(ss,item, ' '))
					{
						istringstream(item) >> num;
						data.push_back(num);
					}

					//store header file data into their components
					width = data[0];
					height = data[1];
					int numImages = data[2];
					dataFile.close();


					//for loop to go through each raw file
					for(int i = 0; i < numImages; i++)
					{
						string index;
						stringstream ss1;
						ss1 << i;
						index = ss1.str();
						//string path for raw file. Add index to string to read each raw file.
						string rawPath = "brain_mri_raws/" + baseName + index + ".raw";
						ifstream rawFile (rawPath.c_str(), ios::binary); //reads binary file
						//array pointer for columns
						unsigned char** sliceCol = new unsigned char* [height];

						//for loop goes through height of raw file
						for (int h = 0; h < height; h++)
						{
							//array pointer for width
							unsigned char* sliceWidth = new unsigned char[width];
							rawFile.read((char*)sliceWidth,width); //type cast sliceWidth to read binary raw file
							sliceCol[h] = sliceWidth;

						}

						//add to slices vector
						slices.push_back(sliceCol);
						rawFile.close();


					}
		}

		//file not found error message
		else
		{
			cout << "File not found." << endl;
		}

		return true;
	}

	//difference map
	void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix)
	{
		using namespace std;
		ofstream output;
		string filename = output_prefix + ".raw"; //file name
		output.open(filename.c_str(),ios::binary); //write to binary file

		//loop through each row
		for(int r = 0; r < height; r++)
		{
			unsigned char* tempRow = new unsigned char[width];
			//loop through each figure in the row
			for(int c = 0; c < width; c++)
			{
				tempRow[c] = (unsigned char)(abs((float)slices[sliceI][r][c] - (float)slices[sliceJ][r][c])/2);

			}
			output.write((char*)tempRow,width); //writes row to raw file
		}
		output.close();
		cout << "Difference Map method complete" << endl;
	}

	//extract method
	void VolImage::extract(int sliceId, std::string output_prefix)
	{
		using namespace std;
		//path name
		string filename = output_prefix + ".raw";
		ofstream output;
		output.open(filename.c_str(),ios::binary); //open a binary file

		for(int h = 0; h < height; h++)
		{
			//write each row to raw file
			output.write((char*)slices[sliceId][h],width);
		}

		output.close(); //close file

		//make and write a .dat header file for raw file
		filename = output_prefix + ".dat";
		output.open(filename.c_str());
		output << width << " " << height << " " << 1 << endl;
		output.close();
		cout << "Extract method complete" << endl;

	}

	// number of bytes uses to store image data bytes and pointers
	int VolImage::volImageSize(void)
	{
		using namespace std;
		int numFiles = slices.size(); //number of files
		cout << "Number of images: " << numFiles << endl; //prints out Number of images

		int sizePoint = sizeof(char*);
		int fileSize;
		//fileSize calculates the space in bytes required for memory
		fileSize = width * height * numFiles * sizePoint;
		return fileSize;
	}

	void VolImage::extraCredit(int index, std::string output_prefix)
	{
		using namespace std;
		//path name
		string filename = output_prefix + ".raw";
		ofstream output;
		output.open(filename.c_str(),ios::binary); //open a binary file

		int numFiles = slices.size();
		for(int n = 0; n < numFiles; n++)
		{
			//write specified row to raw file
			output.write((char*)slices[n][index],width);
		}
		output.close(); //close file
		cout << "Extra Credit method complete" << endl;

	}
}








