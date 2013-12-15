#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv){
    int n;
    cin >> n;
    char word[41];
    int left = 80;
    bool tag = true;

    while (n--) {
        if (tag) scanf("%s", word);
        
        int len = (int)strlen(word);

        if (left != 80) {
            len++;
        }
        if (len <= left) {
            if (left != 80)
                printf(" ");
            left -= len;
            printf("%s", word);
            tag = true;
        }
        else {
            left = 80;
            printf("\n");
            tag = false;
            n++;
        }
    }
    return 0;
}
