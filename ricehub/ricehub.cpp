#include "ricehub.h"
#define MAX_R 100000

class PrefixSum {
private:
  long long prefix_sum[MAX_R + 5];
public:
  PrefixSum(int input[], int R) {
    prefix_sum[0] = input[0];
    for (int i = 1; i < R; i++) {
      prefix_sum[i] = prefix_sum[i - 1] + input[i];
    }
  }

  // Return input[a] + input[a + 1] + ... + input[b + 1]
  long long range_sum(int a, int b) {
    if (a == 0) {
      return prefix_sum[b];
    } else {
      return prefix_sum[b] - prefix_sum[a - 1];
    }
  }
};

int max(int a, int b) {
  return a > b ? a : b;
}

int besthub(int R, int L, int X[], long long B)
{
  int output = 1;

  // Compute the prefix sums of X[]
  PrefixSum prefix_sum(X, R);

  // For each starting point, binary search the furthest ending point
  for (int start = 0; start < R; start++) {
    int lo = start, hi = R - 1, end, hub_index, needle;
    while (lo <= hi) {
      end = (lo + hi) / 2;
      hub_index = (start + end) / 2;

      long long cost1 = (hub_index - start + 1) * X[hub_index] - prefix_sum.range_sum(start, hub_index);
      long long cost2 = prefix_sum.range_sum(hub_index, end) - (end - hub_index + 1) * X[hub_index];
      if (cost1 + cost2 <= B) {
        needle = end;
        lo = end + 1;
      } else {
        hi = end - 1;
      }
    }

    output = max(output, needle - start + 1);
  }
  
  return output;
}
