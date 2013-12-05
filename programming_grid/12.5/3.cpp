#include <iostream>
using namespace std;

int main() {
  char c;

  cin >> c;
  
  while ((c >= '0' and c <= '9') or c == '-') {
    cin.putback(c);

    int n;
    cin >> n;

    unsigned x = 1 << 31;

    while (x > 0) {
      if (n & x) cout << 1;
      else cout << 0;
      x >>= 1;
    }
    cout << endl;
    cin >> c;
  }
  return 0;

}
