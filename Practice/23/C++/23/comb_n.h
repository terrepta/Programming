#ifndef COMB_N_H
#define COMB_N_H
#include "fact_n.h"

int comb_n(int k, int n) {
	int comb;
	comb = fact_n(n) / (fact_n(k) * fact_n(n - k));
	return comb;
}
#endif