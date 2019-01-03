#include <stdio.h>

int main()
{
    int c, s, i;
    char Print[300];

    i = 0;
    while( (c=getchar())!=EOF ) 
    {
        if( c>='A' && c<='z' )
        {
            Print[i] = c;
            ++i;
        }
        else if( c==' ' )
        {
            if( (s=getchar())!='\n' )
            {
                Print[i] = c;
                Print[i+1] = s;
                i += 2;
            }
            else
                Print[i] = '\n';
        }
    }

    return 0;
}
