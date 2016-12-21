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
            if(dbll->head && dbll->head->first->next)
            {
            if_sum(dbll);
            }
            else
            {
              printf("Fewarguments, empty stack!\n");
            }
            break;
        case '-':
            minus++;
            break;
        case '*':
            if(dbll->head && dbll->head->first->next)
            {
                if_multiplication(dbll);
            }
            else
            {
              printf("Fewarguments, empty stack!\n");
            }
            break;
        case '/':
            if(dbll->head && dbll->head->first->next)
            {
                if_division(dbll);
            }
            else
            {
              printf("Few arguments, empty stack!\n");
            }
            break;
        case 'd':
            if(dbll->head)
            {
                number_delete(dbll);
            }
            else
            {
                printf("Nothing to output!!!\n");
            }
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
                    if(dbll->head && dbll->head->first->next)
                    {
                        if_subtraction(dbll);
                    }
                    else
                    {
                        printf("Few arguments, empty stack!\n");
                    }
                }
                flag=0;
                minus=0;
            }
            break;
        }

        c=getchar();
    }

    delete_dbl_list(&dbll);

    return 0;
}
