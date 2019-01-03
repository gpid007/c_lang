#include <stdio.h>
#include <string.h>

int main()
{
    char city[15];
    char st[3];
    char location[18] = "";

    puts("What city do you live in?");
    gets(city);

    puts("What stat do you lvie in? (2-letter abbreviation)");
    gets(st);

    strcat(location, city);
    strcat(location, ", ");
    strcat(location, st);

    puts("\nYou live in ");
    puts(location);
    
    return 0;
}
