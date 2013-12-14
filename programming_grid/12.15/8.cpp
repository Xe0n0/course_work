#include <iostream>

int main()

{
      char str[35];

      int f,i,l=0;
      gets(str);

      for (i = 0; str[i] != '\0'; i++)
      {
            if ( str[i] >= '0' && str[i] <= '9')
            {
                  printf("%c",str[i]);
                  f = 1;
            }
            else
                  f = 0;

            if (f == 0 && str[i - 1] >= '0' && str[i - 1] <= '9')

                  printf("\n");

            l++;

      }

      if (str[l - 1] >= '0' && str[l - 1] <= '9')
            printf("\n");
      return 0;

}
