#include <iostream>
#include <string>
#include <list>
using namespace std;

int main() {
  string temp;
  getline(cin, temp);

  list<char> str(temp.begin(), temp.end());
  str.push_back(temp[0]);

  int n = str.size();
  char c = str.front();

  for (int i = 0; i < n - 1; ++i) {
    str.pop_front();
    char t = c + str.front();
    cout << t;
    c = str.front();
  }
  return 0;
}

