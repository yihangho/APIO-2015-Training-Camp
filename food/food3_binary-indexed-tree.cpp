#include <cstdio>
#include <cstring>
#define MAX_N 1000000

class BinaryIndexedTree {
private:
  int N;
  long long bit[MAX_N + 5];

public:
  BinaryIndexedTree(int N) {
    this->N = N;
    memset(bit, 0, sizeof(bit));
  }

  void add(int index, int delta) {
    while (index <= N) {
      bit[index] += delta;
      index += (index & -index);
    }
  }

  long long query(int index) {
    long long answer = 0;
    while (index > 0) {
      answer += bit[index];
      index -= (index & -index);
    }
    return answer;
  }

  long long query(int a, int b) {
    return query(b) - query(a - 1);
  }
};

int main() {
  int N, P;
  int type, a, b;

  scanf("%d %d", &N, &P);

  BinaryIndexedTree bit(N);

  for (int i = 0; i < P; i++) {
    scanf("%d %d %d", &type, &a, &b);

    if (type == 1) {
      bit.add(a, b);
    } else {
      printf("%lld\n", bit.query(a, b));
    }
  }

  return 0;
}
