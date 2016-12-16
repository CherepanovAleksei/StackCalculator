#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "stack.h"
#include "long_arithmetic.h"
#include "struct.h"

int main()
{
    dbl_list* dbll=create_dbl_list();
    char c;
    int flag=0;
    char minus=0;
    c=getchar();
    while(c!=EOF)
    {
        switch (c)
        {
        case '+':
            if_sum(dbll);
            break;
        case '-':
            minus++;
            break;
        case '*':
            if_multiplication(dbll);
            break;
        case '/':
            if_division(dbll);
            break;
        case 'd':
            number_delete(dbll);
            break;
        case '=':
            if(dbll->head)
            {
                print_resalt(dbll);
            }
            else
            {
                printf("Nothing to output!!!\n");
            }
            break;
        default:
            if(c!='\n')
            {
                node_add(dbll, c-'0',flag, minus);
                flag++;
                minus=0;
            }
            else
            {
                if(minus)
                {
                    if_subtraction(dbll);
                }
                flag=0;
                minus=0;
                printf("принято\n");
            }
            break;
        }

        c=getchar();
    }

    delete_dbl_list(&dbll);

    return 0;
}
