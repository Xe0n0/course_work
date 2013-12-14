#include <iostream>
#include <list>
using namespace std;

int main() {
  int n;
  cin >> n;
  list<int> array;

  int t;
  for (int i = 0; i < n; ++i) {
    cin >> t;
    array.push_back(t);
  }
  
  for (int i = 0; i < n; ++i) {
    cout << array.back();
    array.pop_back();
    if (i < n - 1) cout << ' ';
  }
  cout << endl;

  return 0;
}
