/**
 * Starter template for dynamic programming
 * CSE6140, Fall 2019
 * Kaan Sancak
 * GT ID: 903523701
 */

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <iomanip>

struct Interval
{
    double value;
    int start;
    int end;
    std::chrono::duration<double> time;
};

int main(int argc, char **argv)
{
    std::string in_file_path, out_file_path;
    std::ifstream infile;
    std::string line, curChar;
    std::vector<std::vector<double>> v;

    int numSamples = -1, numDays = -1;

    if (argc != 3)
    {
        printf("Usage: %s <input> <output>\n", argv[0]);
        return -1;
    }

    // Read file
    infile.open(in_file_path, std::ifstream::in);

    if (infile.is_open())
    {
        while (infile.good())
        {
            if (!getline(infile, line))
                break;

            std::vector<double> temp;
            std::istringstream ss(line);

            while (ss)
            {
                if (!getline(ss, curChar, ','))
                    break;

                if (numSamples == -1)
                {
                    numSamples = stoi(curChar);
                }
                else if (numDays == -1)
                {
                    numDays = stoi(curChar);
                }
                else
                {
                    temp.push_back(stod(curChar));
                }
            }

            if (temp.size() > 0)
            {
                v.push_back(temp);
            }
        }
        infile.close();
    }
    else
    {
        std::cout << "Cannot open input file!" << std::endl;
    }
    // Write results to output

    return 0;
}
