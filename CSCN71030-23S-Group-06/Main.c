#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Function.h"

int main() {
  
    // Test Case 1: Valid File and Mode
    const char* filename1 = "testfile.txt";
    const char* mode1 = "w"; 
    FILE* file1 = openFile(filename1, mode1);
    if (file1 != NULL) 
    {
        printf("Test Case 1: File created successfully\n");
        fclose(file1);
    }
    else 
    {
        printf("Test Case 1: Error creating file\n");
    }
    // Should run

    //// Test Case 2: Invalid File
    //const char* filename2 = "non_existent_file.txt";
    //const char* mode2 = "r";
    //FILE* file2 = openFile(filename2, mode2);
    //// Should return an error when trying to open the file

    //// Test Case 3: Invalid Mode
    //const char* filename3 = "testfile.txt";
    //const char* mode3 = "invalid_mode";
    //FILE* file3 = openFile(filename3, mode3);
    //// Should return an error when using the wrong mode
    return 0;
}
