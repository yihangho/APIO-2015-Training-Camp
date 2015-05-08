#include <limits>
#include <cstdio>
#include "guess.h"
using namespace std;

long long find_number() {
  long long lo, hi, mid, answer = 0;

  if (ask_yun_kai(numeric_limits<long long>::min())) {
    return numeric_limits<long long>::min();
  }

  if (ask_yun_kai(-1)) { // negative
    lo = numeric_limits<long long>::min() + 1;
    hi = -1;
  } else { // positive
    lo = 0;
    hi = numeric_limits<long long>::max();
  }

  while (lo <= hi) {
    mid = lo + (hi - lo) / 2;
    if (ask_yun_kai(mid)) {
      answer = mid;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }

  return answer;
}
