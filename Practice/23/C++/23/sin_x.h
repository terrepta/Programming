#ifndef SIN_X_H
#define SIN_X_H
#include <cmath>
#include "fact_n.h"

double sin_x(double x, int k) {
	double res_sum = 0;
	int pown = -1;  
	for (int i = 0; i < k; i++) {
		pown *= -1;			 //(-1)^n	//��� ������ �������� � ����������� � ������� ����� 1 � -1.
		res_sum += pown * pow(x, 2 * i + 1) / fact_n(2 * i + 1);	//������� ���� �������
	}
	return res_sum;
}

#endif