#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int i;
    int hasUpper, hasLower, hasDigit, allGood;
    char user[25], password[25];

    hasUpper = hasLower = hasDigit = allGood = 0;

    printf("Choose username:");
    scanf(" %s", user);

    printf("Enter password:");
    scanf(" %s", password);

    for (i = 0; i < strlen(password); i++)
    {
        if (isdigit(password[i]))
            hasDigit = 1;
        if (isupper(password[i]))
            hasUpper = 1;
        if (islower(password[i]))
            hasLower = 1;
    }

    if ((hasDigit) && (hasUpper) && (hasLower))
    {
        printf("\nExcellent work, %s!", user);
        printf("Your password has upper and lower case, letters and numerals.\n");
        allGood = 1;
    }
    else
    {
        printf("\nPlease consider a more secure password, %s!", user);
        printf("\nChoose one with upper and lower case as well as numerals.\n");
    }

    return 0;
}
