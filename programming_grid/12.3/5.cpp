#include <iostream>
#include <string>
using namespace std;
bool isMatch(const char *s, const char *p) {
        const char *p_s, *p_p;

        if ((p_s = s) == NULL || (p_p = p) == NULL) return false;


        bool has_star = false;

        while (*p_s != '\0') {

            switch (*p_p) {
                case '*':
                    has_star = true;
                    p = p_p;
                    s = p_s;
                    while (*p == '*') {
                        p++;
                    }
                    if (*p == '\0') return true;

                    p_s = s - 1;
                    p_p = p - 1;
                    break;

                case '?':
                    break;

                default:
                    if (*p_p != *p_s) {
                        if (!has_star) return false;
                        s++;
                        p_s = s-1;
                        p_p = p-1;
                    }
                    break;

            }

            p_s++;
            p_p++;
        }
        while (*p_p == '*') p_p++;

        return *p_p == '\0';
}
int main(){
  string p, s;
  cin >> p >> s;
  if (isMatch(s.c_str(), p.c_str())) cout << "matched";
  else cout << "not matched";

  cout << endl;
  return 0;
}
