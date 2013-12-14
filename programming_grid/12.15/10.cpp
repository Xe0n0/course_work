#include <iostream>
using namespace std;

int main() {
  int G;
  cin >> G;
  int *A = new int[10000];
  int *B = new int[10000];
  long long *C = new long long[10000];

  while (G--) {
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> *(A + i * m + j);

    for (int i = 0; i < m; ++i)
    for (int j = 0; j < k; ++j)
      cin >> *(B + i * k + j);

    memset(C, 0, sizeof(long long) * 10000);
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < k; ++j)
    for (int t = 0; t < m; ++t)
      *(C + i * k + j) += *(A + i * m + t) * *(B + t * k + j);

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < k; ++j) {
        cout << *(C + i * k + j);
        if (j < k - 1) cout << ' ';
      }
      cout << endl;
    }
  }

  return 0;
}


