#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int> > result;
vector<int> value;
vector<int> path;
void dfs(int depth, int remain) {
  if (depth >= 3) {
      if (remain == 0) {
        result.push_back(path);
        reverse(result.back().begin(), result.back().end());

        return;
      }
      else return;
  }

  int v = value[depth];

  for (int i = 0; i * v <= remain; ++i) {
    path.push_back(i);
    dfs(depth + 1, remain - i * v);
    path.pop_back();
  }
}

int main() {
  value.push_back(5);
  value.push_back(2);
  value.push_back(1);

  int n;
  cin >> n;
  dfs(0, n);

  int len = result.size();
  for (int i = 0; i < len; ++i) {
    printf("%03d", i + 1);
    for (int j = 0; j < 3; ++j) {
      printf("%12d", result[i][j]);
    }
    cout << endl;
  }
  return 0;
}
