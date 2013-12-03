#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
int n;
vector<string> board;
queue<pair<int, int> > q;
void addq(int x, int y) {

  if (x >= 0 and x < n and
      y >= 0 and y < n and board[x][y] != '#'
     )
  {
    q.push(make_pair(x, y));
  }

}
bool find(int x, int y){
  
  q.push(make_pair(x, y));
  bool found = false;
  while (!q.empty()) {
    pair<int, int> p = q.front();
    q.pop();
    if (board[p.first][p.second] == 'e') {
      found = true;
      break;
    }
    board[p.first][p.second] = '#';
    x = p.first;
    y = p.second;
    addq(x, y - 1);
    addq(x, y + 1);
    addq(x - 1, y);
    addq(x + 1, y);
  }
  while (!q.empty()) q.pop();

  if (found) return true;
  return false;
}

int main(){
  int m;
  cin >> m;

  while (m--) {
    cin >> n;
    board.clear();
    board.resize(0);
    board.resize(n, string(n, '.'));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cin >> board[i][j];
      }
    }
    if (find(0, 0)) cout << "YES";
    else cout << "NO";
    cout << endl;
  }
}

