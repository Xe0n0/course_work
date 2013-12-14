#include <iostream>
using namespace std;

int main() {
  int k;
  cin >> k;
  int m, n;

  while (k--) {
    cin >> m >> n;

    int sum = 0;

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int t;
        cin >> t;
        if (i == 0 || j == 0 || i == m - 1 || j == n - 1) {
          sum += t;
        }
      }
    }
    cout << sum << endl;
  }
  return 0;
}
