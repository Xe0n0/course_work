#include <iostream>
#include <string>

using namespace std;

int main() {
    
    string a, b;
    
    cin >> a >> b;
    
    int n = max(a.size(), b.size());
    
    string r(n, '0');
    
    int carry = 0;
    
    int i = a.size() - 1, j = b.size() - 1, c = n-1;
    
    while (i >= 0 && j >= 0) {
        
        r[c] = a[i] - '0' + b[j] - '0' + carry;
                
        carry = r[c] / 10;
        
        r[c] %= 10;
        
        i--;
        j--;
        c--;
        
    }
    
    while (i >= 0) {
        
        r[c] = a[i] - '0' + carry;
        
        carry = r[c] / 10;
        r[c] %= 10;
        i--;
        c--;
    }
    
    while (j >= 0) {
        
        r[c] = b[j] - '0' + carry;
        carry = r[c] / 10;
        r[c] %= 10;
        j--;
        c--;
    }
    
    if (carry)
        cout << 1;
    
    i = 0;
    while (!carry and r[i] == 0 and i + 1 < r.size()) i++;
    for (; i < r.size(); i++) {
        
        cout << int(r[i]);
        
    }
    
    cout << endl;
    
        return 0;
}
