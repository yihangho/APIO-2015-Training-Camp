#include <cstdio>
#include <cmath>
#define MAX_N 1000000
#define MAX_SQRT_N 10000

int main() {
  int N, P, bucket_size;
  int type, a, b;
  long long buckets[MAX_SQRT_N + 5] = { 0 }, count[MAX_N + 5] = { 0 };

  scanf("%d %d", &N, &P);
  bucket_size = sqrt(N);

  for (int i = 0; i < P; i++) {
    scanf("%d %d %d", &type, &a, &b);

    if (type == 1) {
      count[a] += b;
      buckets[a / bucket_size] += b;
    } else {
      long long answer = 0;
      for (int j = a; j <= b; ) {
        if (j % bucket_size == 0 && j + bucket_size - 1 <= b) {
          answer += buckets[j / bucket_size];
          j += bucket_size;
        } else {
          answer += count[j];
          j += 1;
        }
      }
      printf("%lld\n", answer);
    }
  }
}
