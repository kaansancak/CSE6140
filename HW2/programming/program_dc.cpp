/**
 * Starter template for divide and conquer
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

struct Interval
{
    float value;
    int start;
    int end;
};

Interval findMaxContSum(std::vector<float> v, int low, int high);
Interval findMaxCrossingMiddle(std::vector<float> v, int low, int high);

int main(int argc, char **argv)
{
    std::string in_file_path, out_file_path;
    std::ifstream infile;
    std::string line, curChar;
    std::vector<std::vector<float>> v;

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
    infile.open(argv[1], std::ifstream::in);

    if (infile.is_open())
    {
        while (infile.good())
        {
            if (!getline(infile, line))
                break;

            std::vector<float> temp;
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
                    temp.push_back(stof(curChar));
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

    // Find maximum continues sum for each sample
    for (int i = 0; i < numSamples; i++)
    {
        // Call helper for each sample that calculates max cont. sum
        int start = 0;
        int end = numDays - 1;
        Interval max = findMaxContSum(v[i], start, end);
        std::cout << max.value << " Indeces: " << max.start + 1 << "\t" << max.end + 1 << std::endl;
    }

    // Write results to output

    return 0;
}

/**
 * Recursive helper function
 * @param low keeps track of current lowest index
 * @param high keeps track of current highest index
 * @param start keeps track of start index of maximum sum
 * @param end keeps track of end index of maximum sum
*/
Interval findMaxContSum(std::vector<float> v, int low, int high)
{
    // Base case: 1 element
    if (low == high)
    {
        Interval t;
        t.value = v[high];
        t.start = low;
        t.end = high;
        return t;
    }

    // Find mid point
    int mid = (low + high) / 2;

    // Find max for left
    Interval left = findMaxContSum(v, low, mid);

    // Find max for right
    Interval right = findMaxContSum(v, mid + 1, high);

    // Find max such that crosses the middle point
    Interval middle = findMaxCrossingMiddle(v, low, high);

    // Return maximum of three values
    return left.value > right.value ? (left.value > middle.value ? left : middle)
                                    : (right.value > middle.value ? right : middle);
}

Interval findMaxCrossingMiddle(std::vector<float> v, int low, int high)
{
    // Keep track of left and right sum
    float leftSum = 0;
    float rightSum = 0;
    float tempSum = std::numeric_limits<float>::min();

    Interval t;
    // Find mid point
    int mid = (low + high) / 2;

    t.start = mid;
    t.end = mid;

    // Find left sum
    for (int i = mid; i >= low; i--)
    {
        tempSum += v[i];
        t.start = leftSum >= tempSum ? t.start : i;
        leftSum = leftSum >= tempSum ? leftSum : tempSum;
    }

    tempSum = std::numeric_limits<float>::min();
    // Find right sum
    for (int i = mid + 1; i <= high; i++)
    {
        tempSum += v[i];
        t.end = rightSum >= tempSum ? t.end : i;
        rightSum = rightSum >= tempSum ? rightSum : tempSum;
    }

    t.value = leftSum + rightSum;
    return t;
}
