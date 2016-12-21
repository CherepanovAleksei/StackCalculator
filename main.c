#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "stack.h"
#include "long_arithmetic.h"
#include "struct.h"

int main()
{
    dbll_up= up_create();


    char* str_in;

    long long count=0;

    long long size_str=2;

    char symbol;

    int new_number_flag=0;
    char minus=0;
    symbol=getchar();


    while(symbol!=EOF)
    {
        switch (symbol)
        {
        case '+':
            if(dbll_up->head && dbll_up->head->next)
            {
                if_sum();
            }
            else
            {
                printf("Few arguments,empty stack!\n");
            }
            break;
        case '-':
            minus=1;
            break;
        case '*':
            if(dbll_up->head && dbll_up->head->next)
            {
                if_multiplication();
            }
            else
            {
                printf("Few arguments,empty stack!\n");
            }
            break;
        case '/':
            if(dbll_up->head && dbll_up->head->next)
            {
                if_division();
            }
            else
            {
                printf("Few arguments,empty stack!\n");
            }
            break;
        case 'd':
            if(dbll_up->head)
            {
                num_pop(dbll_up, dbll_up->head);
            }
            else
            {
                printf("Nothing to output!!!\n");
            }
            break;
        case '=':
            if(dbll_up->head)
            {
                print_resalt();
            }
            else
            {
                printf("Nothing to output!!!\n");
            }
            break;
        default:
            if(symbol!='\n')
            {
                //create string with big number
                if(!new_number_flag)
                {
                    str_in= (char*)malloc(sizeof(char)*2);
                }

                if(count+1==size_str)
                {
                    size_str=size_str*2;
                    str_in=realloc(str_in,size_str);
                }

                str_in[count]=symbol;
                count++;
                new_number_flag=1;
            }
            else
            {
                if(new_number_flag)
                {
                    num_read(str_in,count);

                    if(minus)
                    {
                        num_sign_change();
                        minus=0;
                    }
                    count=0;
                    size_str=2;
                    new_number_flag=0;
                    free(str_in);

                }
                if(minus)
                {
                    if(dbll_up->head && dbll_up->head->next)
                    {
                        if_subtraction();
                    }
                    else
                    {
                        printf("Few arguments,empty stack!\n");
                    }
                    minus=0;
                }

            }
            break;
        }
        symbol=getchar();
    }

    up_pop();

    return 0;
}
