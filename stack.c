#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "stack.h"
#include "long_arithmetic.h"
#include "struct.h"

//output:1=last(num2)>first(num1) 0=last<first
int comparison(dbl_list *dbll)
{
    int category1=dbll->head->first->next->category;
    int category2=dbll->head->category;
    if(category1 > category2)
    {
        return 1;
    }
    else if(category1 < category2)
    {
        return 0;
    }
    else
    {
        node *num1 = dbll->head->first->next->first;
        node *num2 = dbll->head->first;
        while(1)
        {
            if(num1->value > num2->value)
            {
                return 1;
            }
            else if(num1->value < num2->value)
            {
                return 0;
            }
            else
            {
                if(num2->prev)
                {
                    num1=num1->prev;
                    num2=num2->prev;
                }
                else
                {
                    return 1;
                }
            }
        }
    }
}

void change_sign(dbl_list *dbll)
{
    node*tmp=dbll->head;
    if(tmp->minus)
    {
        while(tmp->category!=1)
        {
            tmp->minus=0;
            tmp=tmp->next;
        }
        tmp->minus=0;
    }
    else
    {
        while(tmp->category!=1)
        {
            tmp->minus=1;
            tmp=tmp->next;
        }
        tmp->minus=1;
    }
}


node* node_create()
{
    node *tmp = (node*) malloc(sizeof(node));
    if (tmp == NULL)
    {
        printf("Smth wrong in node*create\n");
        exit(1);
    }

    tmp->category=0;
    tmp->value = 0;
    tmp->minus = 0;
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->first = NULL;
    return tmp;
}

void node_add(dbl_list *dbll, int c, int flag, char minus)
{
    node*new_struct=node_create();

    new_struct->value = c;
    if (flag == 0)
    {
        new_struct->category=1;
        new_struct->first=new_struct;
        new_struct->minus=minus;
    }
    else
    {
        new_struct->category=dbll->head->category+1;
        new_struct->first=dbll->head->first;
        new_struct->minus=dbll->head->minus;
    }

    new_struct->next = dbll->head;
    new_struct->prev = NULL;

    if (dbll->head)
    {
        dbll->head->prev = new_struct;
    }

    dbll->head = new_struct;

    if (!dbll->tail)
    {
        dbll->tail = new_struct;
    }

    dbll->size++;
}

void node_del(dbl_list *dbll)
{
    node *tmp = dbll->head;
    if (dbll->head == NULL)
    {
        printf("problems with delete!!!");
        exit(2);
    }
    if(dbll->head == dbll->tail)
    {
        dbll->head=NULL;
        dbll->tail=NULL;
    }
    else
    {
        dbll->head=dbll->head->next;
        dbll->head->prev=NULL;
    }
    free(tmp);
    dbll->size--;
}

void number_delete(dbl_list *dbll)
{
    int count=dbll->head->category;
    int k;

    for(k=0;k<count;k++)
    {
        node_del(dbll);
    }
}

dbl_list* create_dbl_list()
{
    dbl_list *new_dbl_list = (dbl_list*) malloc(sizeof(dbl_list));
    new_dbl_list->size = 0;
    new_dbl_list->head = NULL;
    new_dbl_list->tail = NULL;
    return new_dbl_list;
}

void delete_dbl_list(dbl_list **dbll)
{
    node *tmp = (*dbll)->head;
    node *next = NULL;

    while (tmp)
    {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }

    free(*dbll);
    (*dbll) = NULL;

    printf("Goodbye\n");
}

void print_resalt(dbl_list *dbll)
{
    node *pointer=dbll->head->first;

    if(pointer->minus > 0 && dbll->head->first->value!=0)
    {
        printf("-");
    }

    while (pointer!=dbll->head)
    {
        printf("%d",pointer->value);
        pointer = pointer->prev;
    }
    printf("%d\n",pointer->value);
}

void buff_to_dbll(dbl_list *dbll_buff, dbl_list *dbll)
{
    int value;
    int flag=0;
    node *tmp = dbll_buff->head;
    while(1)
    {
        value=tmp->value;
        node_add(dbll, value, flag, 0);
        flag++;

        if(tmp->category == 1)
        {
            break;
        }
        tmp=tmp->next;
    }
}

void roll(dbl_list *dbll)
{
    dbl_list *dbll_buff=create_dbl_list();
    int flag=0;
    node *tmp = dbll->tail;
    while(1)
    {
        node_add(dbll_buff, tmp->value, flag, 0);
        flag++;

        if(!tmp->prev)
        {
            break;
        }
        tmp=tmp->prev;
    }
    number_delete(dbll);
    buff_to_dbll(dbll_buff,dbll);
}
