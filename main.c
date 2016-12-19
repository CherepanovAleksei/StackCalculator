#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "stack.h"
//#include "long_arithmetic.h"
#include "struct.h"

int main()
{
    dbll_up= up_create();
    dbl_list_num* dbll_num;

    char* str_in;
    char* str_fragment;
    long long count=0;
    int count2=0;
    int count3=0;
    long long size_str=2;

    char symbol;
    int i;
    int new_number_flag=0;
    int new_number=0;
    char minus=0;
    symbol=getchar();


    while(symbol!=EOF)
    {
        switch (symbol)
        {
        /*case '+':
            if_sum(dbll);
            break;*/
        case '-':
            minus=1;
            break;
        /*case '*':
            if_multiplication(dbll);
            break;
        case '/':
            if_division(dbll);
            break;
        case 'd':
            number_delete(dbll);
            break;*/
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
                    //add new number
                    dbll_num= num_push_after(dbll_up->head);

                    str_fragment= (char*)malloc(sizeof(char)*(i+1));
                    i=count%9;
                    for(count2=0; count2<i;count2++)
                    {
                        str_fragment[count2]=str_in[count2];
                    }
                    str_fragment[count2]='\0';
                    node_push_head(atoll(str_fragment),dbll_num);

                    free(str_fragment);
                    str_fragment= (char*)malloc(sizeof(char)*10);
                    str_fragment[9]='\0';

                    i=count/9;
                    count=count2;
                    for(count2=0; count2<i; count2++)
                    {
                        for(count3=0;count3<9;count3++)
                        {
                            str_fragment[count3]=str_in[count+count3];
                        }
                        node_push_tail(atoll(str_fragment),dbll_num);
                        count+=9;
                    }
                    count=0;
                    size_str=2;
                    new_number_flag=0;
                    free(str_in);
                    free(str_fragment);
                    while(!dbll_up->head->head->value)
                    {
                        if(dbll_num->head==dbll_num->tail)
                        {
                            break;
                        }
                        node_pop_head(dbll_num);
                    }
                    if(minus)
                    {
                        dbll_up->head->sign=1;
                        minus=0;
                    }
                }
                if(minus)
                {
                    //if_subtraction
                }

            }
            /*else if(minus)
            {
                if_subtraction(dbll);
            }*/
            //minus=0;
            break;
        }
        symbol=getchar();
    }


    up_pop();

    return 0;
}
