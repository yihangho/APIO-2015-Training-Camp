#include <algorithm>
#include <iostream>
#include <string>
#define MAX_N 100000
using namespace std;

int main() {
  int N, M, answer = 0;
  string input, stolen[MAX_N + 5];

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> stolen[i];
  }

  sort(stolen, stolen + N);

  cin >> M;
  for (int i = 0; i < M; i++) {
    cin >> input;
    answer += binary_search(stolen, stolen + N, input);
  }

  cout << answer << endl;
}
