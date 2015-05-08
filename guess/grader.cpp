#include <stdio.h>
#include <stdlib.h>
#include "guess.h"

static int K;

extern long long find_number();

bool ask_yun_kai(long long N) {
    return N >= K;
}

void init() {
	scanf("%d", &K);
}

int main() {
    int N = -1;
	init();
	printf("%lld\n", find_number());
	return 0;
}
