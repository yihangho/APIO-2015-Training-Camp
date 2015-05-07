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

  cin >> M;
  for (int i = 0; i < M; i++) {
    cin >> input;

    for (int j = 0; j < N; j++) {
      if (input == stolen[j]) {
        answer += 1;
        break;
      }
    }
  }

  cout << answer << endl;
  return 0;
}
