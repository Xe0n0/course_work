#include <iostream>
#include <vector>
#include <climits>
#include <utility>
using namespace std;

int calc(int a, int b, char op) {
  if (op == '*') return a * b;
  return a + b;
}

int max_value(vector<pair<int, char> > &circle, int a, int b) {
  if (b - a == 1) return circle[a].first;

  int value = INT_MIN;

  for (int i = a; i < b - 1; ++i) {

    value = max(value, calc(max_value(circle, a, i + 1),
                max_value(circle, i + 1, b), circle[i].second));
  }
  return value;
}

int main() {
  int n;
  cin >> n;
  vector<pair<int, char> > circle;
  while (n--) {
    int a;
    char b;
    cin >> a >> b;
    circle.push_back(make_pair(a, b));
  }
  int len = circle.size();
  circle.resize(2 * len);
  copy(circle.begin(), circle.begin() + len, circle.begin() + len);

  int value = INT_MIN;
  for (int i = 0; i < len; ++i) {
    value = max(value,
        max_value(circle, i, i + len));
  }
  cout << value << endl;

  return 0;
}
