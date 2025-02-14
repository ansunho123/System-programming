#include "func.h"

int func(int a) {
	int ret = 0;
	for (int i = 0; i < a; i++) {
		ret = ret + i ;
	}
	return ret;
}

