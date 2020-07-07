#pragma once
int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath);
bool readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath);
double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath);
void getCurrentDirectory(char *currentDirectory);
void getVectors(char importFile[BUFFSIZE], float** first_vectors, float** second_vectors, learnModel model);
void getTestData(float* vector, learnModel model);
void writeResult(float correctRate, float *test_vectors, char *result, learnModel model);
void strPicker(char *lineData, float *temp);