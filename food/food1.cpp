#include <cstdio>
#define MAX_N 1000000

int main() {
  int N, P;
  int type, a, b;
  long long count[MAX_N + 5] = { 0 };

  scanf("%d %d", &N, &P);
  for (int i = 0; i < P; i++) {
    scanf("%d %d %d", &type, &a, &b);

    if (type == 1) {
      count[a] += b;
    } else {
      long long answer = 0;
      for (int j = a; j <= b; j++) {
        answer += count[j];
      }
      printf("%lld\n", answer);
    }
  }

  return 0;
}
