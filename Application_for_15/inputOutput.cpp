#include "stdafx.h"
#include "setting.h"
#include <Windows.h>
#include <stdio.h>
#include <string>


int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath) {
	return GetPrivateProfileInt(section, keyword, defaultValue, filePath);
};

bool readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath) {
	if (GetPrivateProfileString(section, keyword, defaultValue, returnValue, CHARBUFF, filePath) != 0) {
		return true;
	}
	else {
		fprintf(stdout, "%s doesn't contain [%s] %s\n", filePath, section, keyword);
		return false;
	}
};

double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath) {
	char buf[CHARBUFF];
	GetPrivateProfileString(section, keyword, "none", buf, CHARBUFF, filePath);
	defaultValue = strtod(buf, NULL);
	return defaultValue;
};

void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
};

void fetchFile(char importFile[BUFFSIZE], float** vectors, learnModel model) {
	char lineData[BUFFSIZE];
	int index = 0;
	FILE *fp;
	errno_t error;
	error = fopen_s(&fp, importFile, "r");
	if (error != 0) {
		fprintf_s(stderr, "failed to open for txt in importFile_%s", importFile);
	} else {
		while (fgets(lineData, BUFFSIZE, fp) != NULL) {
			strPicker(lineData, vectors[index]);
			index++;
		}
		fclose(fp);
	}
};


void getClassDatas(char firstFile[BUFFSIZE], char secondFile[BUFFSIZE], float** firstVectors, float** secondVectors, learnModel model) {
	fetchFile(firstFile, firstVectors, model);
	fetchFile(secondFile, secondVectors, model);
}

void getTestData(float* vector, learnModel model) {
	char lineData[BUFFSIZE];
	int j = 0;
	FILE *fp;
	errno_t error;
	error = fopen_s(&fp, "test.txt", "r");
	if (error != 0) {
		fprintf_s(stderr, "failed to open for txt in test.txt");
	}
	else {
		while (fgets(lineData, BUFFSIZE, fp) != NULL) {
			strPicker(lineData, vector);
		}
		fclose(fp);
	}
}

void writeResult(float correctRate, float *test_vector, char *result, learnModel model) {
	FILE *fp;
	errno_t error;
	int i;

	error = fopen_s(&fp, "result.txt", "w");
	if (error == 0)
	{
		fprintf_s(fp, "学習係数: %f\n", model.coefficient);
		fprintf_s(fp, "学習回数: %d\n", model.learnNum);
		fprintf_s(fp, "重み:\n");
		for (i = 0; i < model.featureNum+1; i++) {
			fprintf_s(fp, "\tw%d = %f\n", i, model.bias[i]);
		}
		fprintf_s(fp, "正解率: %f\n", correctRate);
		fprintf_s(fp, "****分類結果*****\n入力されたtestデータは、 %sと判断されました!!!", result);
		fclose(fp);
	}
}

void strPicker(char *lineData, float *vector) {
	char *character_line;
	char delim[] = " ";
	char *ctx;
	int i;
	i = 0;

	character_line = strtok_s(lineData, delim, &ctx);
	while (character_line != NULL) {
		*(vector + i) = strtof(character_line,NULL);
		character_line = strtok_s(NULL, delim, &ctx);
		i++;
	}
}