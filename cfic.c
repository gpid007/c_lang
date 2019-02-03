/* 
 * CFIC = C - Float Interpreted Calculator 
 * Author = GPH
 * Warranty = NONE WHATSOEVER
 * Have fun!
 */

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

# define CHARMAX 65 
# define OPR "+-*/"
# define DELIM "; ,"

// PROTOTYPE
int getIN();

// MAIN
int main()
{
    printf("\n\t\tC-FIC\n\tC - Float Interpreted Calculator");
    printf("\n\n# Operators [+-*/]\n# Delimiters [; ,]");
    printf("\n# Interpretation [FIFO]\n# FIFO evaluation [2 + 3 / 5] = [1]");
    printf("\n# [exit] to quit\n");
    int RUN = 1;
    while (RUN > 0)
    {
        RUN = getIN();
    }
    printf("\n");
    return 0;
}

// FUNCTION
int getIN()
{
    char IN[CHARMAX];
    char *token;
    float eval = 0; 
    char opr = '\0';
    int ctr = 0;

    // READ
    printf("\n<<< ");
    fgets(IN, CHARMAX, stdin); // read incl. whitespace and linebreak
    token = strtok(IN, DELIM); // tokenize input straem by delimiter

    // EVALUATE
    while (token != NULL)
    {   
        // HANDLE ERROR
        if (strchr(OPR, (char) *token))
        {
            opr = (char) *token;
        }
        if (atof(token) && ctr == 0)
        {
            eval = atof(token);
        }
        if (atof(token) && ctr > 0)
        {
            // INTERPRET OPERATOR
            switch (opr)
            {
                case '+':
                    eval += atof(token);
                    break;
                case '-':
                    eval -= atof(token);
                    break;
                case '*':
                    eval *= atof(token);
                    break;
                case '/':
                    eval /= atof(token);
                    break;
            }
        }
        token = strtok(NULL, DELIM);
        ctr++;
    }
    // PRINT RESULT
    printf(">>> %f", eval);

    // EXIT
    if (strcmp("exit\n", IN) == 0)
        return 0;
    else
        return 1;
}
