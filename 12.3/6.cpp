#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
bool zero(long long *a, int len) {
  bool zero = true;
  for (int i = 0; i < len; ++i) 
    if (a[i] != 0) zero = false;
  return zero;
}

void m2n(int a, string &num, int b) 
{
        long long n[1000], ten[1000], x[1000];
        memset(n,0,sizeof(n));
        memset(x,0,sizeof(x));
        int len = num.size();
        int i;
        for(i=0;i<len;i++)
            if(num[i]<='9'&&num[i]>='0') n[i]=num[i]-'0';
            else n[i]=num[i]-'A'+10;
            if(zero(n,len))
            {
                printf("0\n");
                return ;
            }
            int j=0;
        int tenleft = 0;
        while(!zero(n,len))
        {   
            tenleft = 0;
            for(i=0;i<len;i++)
            {
                tenleft*=a;
                n[i]+=tenleft;
                tenleft=n[i]%10;
                n[i]/=10;
            }
            ten[j++]=tenleft;
        }
        /*for(i=0;i<j;i++)
        if(x[i]<=9&&x[i]>=0)
            printf("%d",ten[i]);
        else printf("%c",x[i]+'a'-10);
        printf("\n");*/
 
        len=j;
        j=0;
        while(!zero(ten,len))
        {   
            tenleft=0;
            for(i=len-1;i>=0;i--)
            {
                tenleft*=10;
                ten[i]+=tenleft;
                tenleft=ten[i]%b;
                ten[i]/=b;
            }
            x[j++]=tenleft;
        }
        for(i=j-1;i>=0;i--)
        if(x[i]<=9&&x[i]>=0)
            printf("%d",x[i]);
        else printf("%c",x[i]+'A'-10);
        printf("\n");
}

int main() {
  int mm;
  cin >> mm;
  while (mm--) {
    int m, n;
    cin >> m;
    char c;
    cin >> c;
    string a;
    cin >> c;
    while (c != ',') {
      a.push_back(c);
      cin >> c;
    }
    cin >> n;
    char nNum[100];
    memset(nNum, 0, sizeof(nNum));
    m2n(m, a, n);
    //printf("%s\n", nNum);
  }
}
