#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
  list<string> strs;

  string temp;
  while (cin >> temp) {
    strs.push_back(temp);
  }

  int n = strs.size();
  for (int i = 0; i < n; ++i) {
    cout << strs.front();
    strs.pop_front();
    if (i < n - 1) cout << ' ';
  }
  return 0;
}
