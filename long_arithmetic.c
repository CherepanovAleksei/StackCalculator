#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "stack.h"
#include "long_arithmetic.h"
#include "struct.h"

void if_sum()
{
    //++
    if(dbll_up->head->sign==0 && dbll_up->head->next->sign==0)
    {
        sum();
    }
    //--
    else if (dbll_up->head->sign>0 && dbll_up->head->next->sign>0)
    {
        sum();
        num_sign_change();
    }
    //+-
    else if (dbll_up->head->sign>0 && dbll_up->head->next->sign==0)
    {
        subtraction();
    }
    //-+
    else if (dbll_up->head->sign==0 && dbll_up->head->next->sign>0)
    {
        subtraction();
        num_sign_change();
    }
}

void if_subtraction()
{
    //++
    if(dbll_up->head->sign==0 && dbll_up->head->next->sign==0)
    {
        subtraction();
    }
    //--
    else if (dbll_up->head->sign>0 && dbll_up->head->next->sign>0)
    {
        subtraction();
        num_sign_change();
    }
    //+-
    else if (dbll_up->head->sign>0 && dbll_up->head->next->sign==0)
    {
        sum();
    }
    //-+
    else if (dbll_up->head->sign==0 && dbll_up->head->next->sign>0)
    {
        sum();
        num_sign_change();
    }
}

void if_multiplication()
{
    //++ --
    if(dbll_up->head->sign == dbll_up->head->next->sign)
    {
        multiplication();
    }
    //+- -+
    else
    {
        multiplication();
        num_sign_change();
    }
}

void if_division()
{
    //++ --
    if(dbll_up->head->sign == dbll_up->head->next->sign)
    {
        division();
    }
    //+- -+
    else
    {
        division();
        num_sign_change();
    }
}

void sum()
{
    dbl_list_node *num1=dbll_up->head->next->tail;
    dbl_list_node *num2=dbll_up->head->tail;
    if(!comparison(dbll_up->head->next,dbll_up->head))
    {
        num1=dbll_up->head->tail;
        num2=dbll_up->head->next->tail;
    }

    dbl_list_num *dbll_res= num_push_head(dbll_up);

    long long int sum;
    long long int plus=0;
    long long int a;//num1(value)
    long long int b;//num2(value)

    while(1)
    {
        a=num1->value;
        b=num2->value;

        sum=(a+b+plus)%1000000000;
        plus=(a+b+plus)/1000000000;

        node_push_head(sum, dbll_res);

        if(!num2->prev)
        {
            num2->value=0;
        }
        else
        {
            num2=num2->prev;
        }

        if(!num1->prev)
        {
            break;
        }
        else
        {
            num1=num1->prev;
        }
    }

    if(plus)
    {
        node_push_head(plus, dbll_res);
    }

    num_pop(dbll_up, dbll_up->head->next);
    num_pop(dbll_up, dbll_up->head->next);
}

void subtraction()
{
    dbl_list_node *num1=dbll_up->head->next->tail;
    dbl_list_node *num2=dbll_up->head->tail;
    char minus=0;
    if(!comparison(dbll_up->head->next,dbll_up->head))
    {
        num1=dbll_up->head->tail;
        num2=dbll_up->head->next->tail;
        minus=1;
    }

    dbl_list_num *dbll_res= num_push_head(dbll_up);
    if (minus)
    {
        dbll_res->sign=1;
    }

    long long int a;//num1(value)
    long long int b;//num2(value)
    dbl_list_node *buff;

    while(1)
    {
        a=num1->value;
        b=num2->value;
        if (a<b)
        {
            a+=1000000000;
            buff=num1->prev;
            while(1)
            {
                if(buff->value)
                {
                    buff->value--;
                    break;
                }
                else
                {
                    buff->value=999999999;
                    buff=buff->prev;
                }
            }
        }

        node_push_head(a-b, dbll_res);

        if(num2->prev)
        {
            num2=num2->prev;
        }
        else
        {
            num2->value=0;
        }

        if(num1->prev)
        {
            num1=num1->prev;
        }
        else
        {
            break;
        }
    }

    //delete '0'
    while(!dbll_res->head->value)
    {
        if(dbll_res->head==dbll_res->tail)
        {
            break;
        }
        node_pop_head(dbll_res);
    }

    num_pop(dbll_up, dbll_up->head->next);
    num_pop(dbll_up, dbll_up->head->next);
}

void multiplication()
{
    dbl_list_node *num1=dbll_up->head->next->tail;
    dbl_list_node *num2=dbll_up->head->tail;
    if(!comparison(dbll_up->head->next,dbll_up->head))
    {
        num1=dbll_up->head->tail;
        num2=dbll_up->head->next->tail;
    }
    dbl_list_node *begin_of_num1 = num1;

    dbl_list_num *dbll_res= num_push_head(dbll_up);
    node_push_head(0, dbll_res);
    dbl_list_node *pointer=dbll_res->tail;
    dbl_list_node *last_pos_of_pointer=pointer;

    long long int a;//num1(value)
    long long int b=num2->value;//num2(value)
    long long int plus=0;

    while(1)
    {
        a=num1->value;
        pointer->value+=a*b;

        if(num1->prev)
        {
            num1=num1->prev;
            if(pointer->prev)
            {
                pointer=pointer->prev;
            }
            else
            {
                node_push_head(0, dbll_res);
                pointer=dbll_res->head;
            }
        }
        else
        {
            pointer=last_pos_of_pointer;
            plus=0;

            while(1)//растаскиваем
            {
                pointer->value+=plus;
                plus=0;
                plus=pointer->value/1000000000;
                pointer->value=pointer->value%1000000000;
                if(!pointer->prev)
                {
                    if(plus)
                    {
                        node_push_head(plus, dbll_res);
                    }
                    break;
                }
                pointer = pointer->prev;
            }


            if(num2->prev)
            {
                num1=begin_of_num1;
                last_pos_of_pointer=last_pos_of_pointer->prev;
                pointer=last_pos_of_pointer;
                num2=num2->prev;
                b=num2->value;
            }
            else
            {
                break;
            }
        }
    }
    node_pop_zeros(dbll_up);
    num_pop(dbll_up, dbll_up->head->next);
    num_pop(dbll_up, dbll_up->head->next);
}

dbl_list_num * subtraction_for_division(dbl_list_up *buff_up, dbl_list_num* divider)
{
    dbl_list_node *num1=buff_up->head->tail;
    dbl_list_node *num2=divider->tail;

    dbl_list_num *dbll_res= num_push_head(buff_up);

    long long int a;//num1(value)
    long long int b;//num2(value)
    dbl_list_node *buff;
    a=num1->value;
    b=num2->value;
    while(1)
    {

        if (a<b)
        {
            a+=1000000000;
            buff=num1->prev;
            while(1)
            {
                if(buff->value)
                {
                    buff->value--;
                    break;
                }
                else
                {
                    buff->value=999999999;
                    buff=buff->prev;
                }
            }
        }

        node_push_tail(a-b, dbll_res);

        if(num2->prev)
        {
            num2=num2->prev;
            b=num2->value;
        }
        else
        {
            b=0;
        }

        if(num1->prev)
        {
            num1=num1->prev;
            a=num1->value;
        }
        else
        {
            break;
        }
    }

    //delete '0'
    //node_pop_zeros(buff_up);

    num_pop(buff_up,buff_up->head->next);
    return dbll_res;
}

void division()
{
    dbl_list_node *num1=dbll_up->head->next->head;

    dbl_list_num *divider=dbll_up->head;
    dbl_list_num *dbll_res= num_push_head(dbll_up);

dbl_list_up *buff_up=up_create();
dbl_list_num *dbll_buff= num_push_head(buff_up);

    long long int div=0;

    //node_push_head(0, dbll_res);
    while(1)
    {
        node_push_tail(num1->value, dbll_buff);
        if(comparison(dbll_buff,divider))
        {//делить можно
            while(1)
            {
                dbll_buff=subtraction_for_division(buff_up,divider);
                div++;
                if(!comparison(dbll_buff,divider))
                {
                    break;
                }
            }
            node_push_tail(div, dbll_res);
            div=0;
        }
        else
        {//делить пока рано, надо снести еще из делимого
            node_push_tail(0, dbll_res);
        }

        if(num1->next)
        {
            num1=num1->next;
        }
        else
        {
            break;
        }
    }



}
/*
void division(dbl_list *dbll)
{
    dbl_list* dbll_res=create_dbl_list();


    dbl_list* dbll_buff=create_dbl_list();
    node *num1 = dbll->head->first->next->first;
    node *num2;

    int category1=dbll->head->first->next->category;
    int category2=dbll->head->category;
    int count;

    int flag1=0;
    int flag2;
    node_add(dbll_res,0,0,0);

    node *res=dbll_res->head;
    while(1)
    {
        //добавляем 1 цифру из делителя
        node_add(dbll_buff, num1->value,flag1,0);
        flag1++;

        //num2 to buff struct добавил все частное
        flag2=0;
        num2 = dbll->head->first;
        for(count=0; count<category2;count++)
        {
            node_add(dbll_buff,num2->value,flag2,0);
            flag2++;
            num2=num2->prev;
        }//num2 заходит в null

        //проверка
        if(!comparison(dbll_buff))
        {//если вычесть нельзя

            number_delete(dbll_buff);

        }
        else
        {//если вычесть можно
            while(1)
            {
                subtraction(dbll_buff);
                res->value++;

                //num2 to buff struct добавил все частное
                flag2=0;
                num2 = dbll->head->first;
                for(count=0; count<category2;count++)
                {
                    node_add(dbll_buff,num2->value,flag2,0);
                    flag2++;
                    num2=num2->prev;
                }//num2 заходит в null

                if(!comparison(dbll_buff))
                {//если вычесть нельзя

                    number_delete(dbll_buff);

                    break;
                }
            }
        }

        if(num1->category!=category1)
        {
            num1=num1->prev;
            node_add(dbll_res,0,1,0);
            res=dbll_res->head;
        }
        else
        {
            break;
        }
    }

    roll(dbll_res);

    //delete '0'
    node *tmp;
    tmp=dbll_res->head;
    if(tmp->value==0)
    {
        while(1)
        {
            if(dbll_res->head == dbll_res->tail)
            {
                break;
            }
            node_del(dbll_res);
            tmp=dbll_res->head;//исправить баг с '0'!!!-удаляется
            if(tmp->value!=0)
            {
                break;
            }
        }
    }
    number_delete(dbll);
    number_delete(dbll);
    buff_to_dbll(dbll_res,dbll);
    delete_dbl_list(&dbll_res);
    delete_dbl_list(&dbll_buff);
}
*/
