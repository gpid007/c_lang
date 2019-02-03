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
void help();

// MAIN
int main()
{
    help();
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
        if (strcmp("exit\n", token) == 0)
        {
            return 0;
        }
        if (strcmp("help\n", token) == 0)
        {
            help();
        }
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
    printf("\n>>> %f", eval);
}

void help()
{
    printf("\nC - Float Interpreted Calculator (C-FIC)");
    printf("\n\n# Pronounced as in [speCIFIC]");
    printf("\n# Operators [+-*/]\n# Delimiters [; ,]");
    printf("\n# Interpretation [FIFO]\n# To quit [exit]\n# For help [help]");
    printf("\n");
}
