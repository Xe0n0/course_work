#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> a, b;
int m, n;

void read(){
  cin >> m >> n;
  a.resize(m);
  b.resize(n);

  for (int i = 0; i < m; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }
}
void sortArray(){
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
}

void merge(){
  for (int i = 0; i < n; ++i) {
    a.push_back(b[i]);
  }
}
void display() {
  for (int i = 0; i < m + n; ++i) {
    cout << a[i];
    if (i + 1 < m + n) cout << ' ';
  }
  cout << endl;
}

int main() {
  read();
  sortArray();
  merge();
  display();
  return 0;
}
