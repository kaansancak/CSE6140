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

double findMaxContSum(std::vector<double> v, int &low, int &high);

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

    // Read the arguments
    in_file_path = std::string(argv[1]);
    out_file_path = std::string(argv[2]);

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
    std::string filename = out_file_path;
    {
        std::ofstream ostrm(filename);
        for (int i = 0; i < numSamples; i++)
        {

            // Call helper for each sample that calculates max cont. sum
            int start = 0;
            int end = 0;

            //Measure time
            auto startTime = std::chrono::high_resolution_clock::now();
            double max = findMaxContSum(v[i], start, end);
            auto endTime = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> diff =
                std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

            ostrm << std::fixed << std::setprecision(2) << max << ',' << (start + 1)
                  << ',' << (end + 1) << ',' << diff.count() << '\n';
        }
    }

    return 0;
}

double findMaxContSum(std::vector<double> v, int &low, int &high)
{
    double sum = std::numeric_limits<double>::min();
    double tempSum = 0;
    int tLow = 0;

    for (int i = 0; i < v.size(); i++)
    {
        tempSum = tempSum + v[i];
        if (sum <= tempSum)
        {
            sum = tempSum;
            low = tLow;
            high = i;
        }
        if (tempSum <= 0)
        {
            tempSum = 0;
            tLow = i + 1;
        }
    }

    std::cout << low << " " << high << std::endl;

    return sum;
}
