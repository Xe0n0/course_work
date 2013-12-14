#include <iostream>
#include <list>
#include <vector>
#include <utility>
using namespace std;

int main() {
  int n;
  cin >> n;

  while (n--) {

    string temp;
    cin >> temp;
    list<char> cs(temp.begin(), temp.end());
    vector<pair<int, char> > sectors;

    char c = cs.front();
    int count = 1;
    cs.pop_front();

    while (!cs.empty()) {
      if (cs.front() == c) {
        count++;
        cs.pop_front();
      }
      else {
        sectors.push_back(make_pair(count, c));
        c = cs.front();
        count = 1;
        cs.pop_front();
      }
    }
    sectors.push_back(make_pair(count, c));

    int idx = 0;
    int m = 1;
    for (int i = 0; i < sectors.size(); ++i) {
      if (sectors[i].first > m) {
        idx = i;
        m = sectors[i].first;
      }
    }

    cout << sectors[idx].second << ' ' << sectors[idx].first << endl;
  }
  return 0;
}
