#include <iostream>
#include <vector>
 
using namespace std;
 
int main()
{
    vector<int>v(120); 
    int i, data, n, m;
    cin >> n >> m;
    for(i = 0; i < n; i++)
        cin >> v[i];
    for(i = 0; i < n - m; i++)
        v[i+n] = v[i];
    for(i = n-m; i < n; i++)
        v[(i+m)%n] = v[i];
    for(i = m; i < n; i++)
        v[i] = v[i+n-m];
    for(i = 0; i < n; i++) {
        cout << v[i];
        if (i < n - 1) cout << ' ';
    }
    return 0;
}
