#include "stdafx.h"
#include "setting.h"

void updateBias(float** first_vectors, float** second_vectors, learnModel model) {
	int i, j, k;
	for (i = 0; i < model.learnNum; i++) {
		/*first_vecotrsによるパラメータ調整*/
		for (j = 0; j < model.teacherNum; j++) {
			if (!(calculation(first_vectors[j], model) >= 0.0)) {
				for (k = 0; k < model.featureNum; k++) {
					if (k == 0) model.bias[k] += model.coefficient*1.0;
					else model.bias[k] += model.coefficient*first_vectors[j][k-1];
				}
			}
		}
		/*second_vecotrsによるパラメータ調整*/
		for (j = 0; j < model.teacherNum; j++) {
			if (!(calculation(second_vectors[j], model) < 0.0)) {
				for (k = 0; k < model.featureNum; k++) {
					if (k == 0) model.bias[k] -= model.coefficient*1.0;
					else model.bias[k] -= model.coefficient*second_vectors[j][k-1];
				}
			}
		}
	}
};

float calculation(float* vectors, learnModel model) {
	int i;
	float result = 0.0;
	for (i = 0; i < model.featureNum; i++) {
		if(i == 0) result += model.bias[i] * 1.0;
		else result += model.bias[i] * vectors[i-1];
	}
	return result;
}

float evaluateModel(float** first_vectors, float** second_vectors, learnModel model) {
	int i, correctNum;
	float result, correctRate;
	correctNum = 0;
	/*first_vecotrsにおける正解数*/
	for (i = 0; i < model.teacherNum; i++) {
		result = calculation(first_vectors[i], model);
		if(result>= 0.0) correctNum++;
	}
	/*second_vecotrsにおける正解数*/
	for (i = 0; i < model.teacherNum; i++) {
		result = calculation(second_vectors[i], model);
		if (result < 0.0) correctNum++;
	}

	correctRate = (float)((float)correctNum / (float)(2 * model.teacherNum));
	return correctRate;
};