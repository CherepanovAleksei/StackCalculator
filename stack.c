#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "stack.h"
#include "long_arithmetic.h"
#include "struct.h"

dbl_list_up* up_create()
{
    dbl_list_up *dbll_up_new = (dbl_list_up*) malloc(sizeof(dbl_list_up));
    dbll_up_new->head = NULL;
    dbll_up_new->tail = NULL;
    return dbll_up_new;
}

void up_pop()
{
  while(dbll_up->head)
  {
    num_pop(dbll_up, dbll_up->head);
  }
  free(dbll_up);
  dbll_up=NULL;
}

dbl_list_num* num_create()
{
    dbl_list_num *dbll_num = (dbl_list_num*) malloc(sizeof(dbl_list_num));
    //dbll_num->size = 0;
    dbll_num->sign = 0;
    dbll_num->head = NULL;
    dbll_num->tail = NULL;
    dbll_num->next = NULL;
    dbll_num->prev = NULL;
    return dbll_num;
}

void num_read(char*str_in,int count)
{
    dbl_list_num* dbll_num;
    char* str_fragment;
    int count2=0;
    int count3=0;
    int i;
    //add new number
    dbll_num= num_push_head(dbll_up);

    i=count%9;
    str_fragment= (char*)malloc(sizeof(char)*(i+1));
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
    free(str_fragment);
    node_pop_zeros(dbll_up);
}

//insert after number:
dbl_list_num* num_push_head(dbl_list_up *dbll_base)
{
    dbl_list_num *num_new=num_create();
    dbl_list_num *num_base=dbll_base->head;
    if(num_base)
    {
      num_base->prev=num_new;
      num_new->next=num_base;
      dbll_base->head=num_new;
      //size++
    }
    else
    {
        dbll_base->head=num_new;
        dbll_base->tail=num_new;
        //size++
    }
    return num_new;
}

void num_pop(dbl_list_up* up_del,dbl_list_num* num_del)
{
  if(up_del->head==up_del->tail)
  {
    up_del->head=NULL;
    up_del->tail=NULL;
    //size--
  }
  else
  {
    if(num_del->next)
    {
      num_del->next->prev=num_del->prev;
    }
    if(num_del->prev)
    {
      num_del->prev->next=num_del->next;
    }
    /*if(up_del->head==num_del)
    {
      up_del->head=num_del->next;
    }
    if (up_del->tail==num_del)
    {
      up_del->tail==num_del->prev;
    }*/
    if(!num_del->prev)
    {
        up_del->head=num_del->next;
    }
    if(!num_del->next)
    {
        up_del->tail=num_del->prev;
    }
    //size--
  }

  while (num_del->head)
  {
    node_pop_head(num_del);
  }
  free(num_del);
  num_del=NULL;
}

void num_sign_change()
{
    if(dbll_up->head->sign)
    {
        dbll_up->head->sign=0;
    }
    else
    {
        dbll_up->head->sign=1;
    }
}

dbl_list_node* node_create()
{
  dbl_list_node *dbll_node = (dbl_list_node*) malloc(sizeof(dbl_list_node));
  dbll_node->value=0;
  dbll_node->next = NULL;
  dbll_node->prev = NULL;
  return dbll_node;
}

void node_push_head(long long int fragment_of_num, dbl_list_num* dbll_num)
{
    dbl_list_node *node_new=node_create();
    node_new->value=fragment_of_num;

    if(dbll_num->head)
    {
      dbl_list_node *node_base=dbll_num->head;
      node_base->prev=node_new;
      node_new->next=node_base;
      dbll_num->head=node_new;
      //size++
    }
    else
    {
        dbll_num->head=node_new;
        dbll_num->tail=node_new;
        //size++
    }
}

void node_push_tail(long long int fragment_of_num, dbl_list_num* dbll_num)
{
    dbl_list_node *node_new=node_create();
    node_new->value=fragment_of_num;

    if(dbll_num->tail)
    {
      dbl_list_node *node_base=dbll_num->tail;
      node_base->next=node_new;
      node_new->prev=node_base;
      dbll_num->tail=node_new;
      //size++
    }
    else
    {
        dbll_num->head=node_new;
        dbll_num->tail=node_new;
        //size++
    }
}

void node_pop_head(dbl_list_num* dbll_num)//нельзя вызывать на пустое num
{
    if(dbll_num->head==dbll_num->tail)
    {
        free(dbll_num->head);
        dbll_num->head=NULL;
        dbll_num->tail=NULL;
        //size--
    }
    else
    {
        dbl_list_node *node_del=dbll_num->head;
        dbll_num->head=node_del->next;
        dbll_num->head->prev=NULL;
        free(node_del);
        //size--
    }
}

void node_pop_tail(dbl_list_num* dbll_num)//нельзя вызывать на пустое num
{
    if(dbll_num->head==dbll_num->tail)
    {
        free(dbll_num->tail);
        dbll_num->head=NULL;
        dbll_num->tail=NULL;
        //size--
    }
    else
    {
        dbl_list_node *node_del=dbll_num->tail;
        dbll_num->tail=node_del->prev;
        dbll_num->tail->next=NULL;
        free(node_del);
        //size--
    }
}

void node_pop_zeros(dbl_list_up *del_up)
{
    while(!del_up->head->head->value)
    {
        if(del_up->head->head==del_up->head->tail)
        {
            break;
        }
        node_pop_head(del_up->head);
    }
}

int comparison(dbl_list_num* first, dbl_list_num* second)
{
    dbl_list_node *num1=first->tail;
    dbl_list_node *num2=second->tail;

    while(1)
    {
        if(num1->prev && num2->prev)
        {
            num1=num1->prev;
            num2=num2->prev;
        }
        else
        {
            if(num1->prev)
            {
                return 1;
            }
            else
            {
                if(num2->prev)
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
        }
    }

    num1=first->head;
    num2=second->head;
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
            if(!num1->next)
            {
                return 1;
            }
            num1=num1->next;
            num2=num2->next;
        }
    }
}

void print_resalt()
{
    dbl_list_node* pointer;

    if(dbll_up->head->sign > 0 && dbll_up->head->head->value!=0)
    {
        printf("-");
    }

    long long int value;
    int count=0;
    for(pointer=dbll_up->head->head; pointer!=NULL; pointer = pointer->next)
    {
        value=pointer->value;
        if(value>0 && value<100000000 && pointer!=dbll_up->head->head)
        {
            while(value)
            {
                value/=10;
                count++;
            }
            count=9-count;

            for(value=0;value<count;value++)
            {
                printf("0");
            }
            count=0;
        }
        else if(value==0 && pointer!=dbll_up->head->head)
        {
            for(value=0;value<8;value++)
            {
                printf("0");
            }
        }

        printf("%lli",pointer->value);

    }
    printf("\n");
}



/**
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
    delete_dbl_list(&dbll_buff);
}
*/
