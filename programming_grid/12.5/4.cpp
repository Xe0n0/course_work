#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
  string target;
  string pattern;
  stack<pair<char, int> > ss;
  while (cin >> target) {
    pattern.resize(0);
    pattern.resize(target.size(), ' ');

    for (int i = 0; i < target.size(); ++i) {

      switch (target[i]) {
        case '(':
          ss.push(make_pair('(', i));
          break;
        case ')':
          if (!ss.empty()) {
            pattern[ss.top().second] = ' ';
            ss.pop();
          }
          else {
            pattern[i] = '?';
          }
          break;
        default:
          pattern[i] = ' ';
          break;
      }
    }
    while (!ss.empty()) {
      pattern[ss.top().second] = '$';
      ss.pop();
    }
    cout << target << endl;
    cout << pattern << endl;
  }

  return 0;
}

