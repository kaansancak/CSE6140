/**
 * Starter template for dynamic programming
 * CSE6140, Fall 2019
 */

#include <stdio.h>
#include <string>


int main(int argc, char **argv) {
    std::string in_file_path, out_file_path;

    if (argc != 3) {
        printf("Usage: %s <input> <output>\n", argv[0]);
        return -1;
    }

    in_file_path = std::string(argv[1]);
    out_file_path = std::string(argv[2]);
    
    // Your code
    
    // Write results to output

    return 0;
}
