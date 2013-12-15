#include <iostream>
using namespace std;

int main() {
  int m, n;
  cin >> m >> n;

  int *A = new int[m * n];

  for (int i = 0; i < m; ++i)
  for (int j = 0; j < n; ++j)
    cin >> *(A + i * n + j);

  for (int l = 1; l < m + n; ++l)
  for (int i = 0; i < l and i < m; ++i)
    if (l - i - 1 < n)
      cout << *(A + i * n + l - i - 1) << endl;

  return 0;
}
