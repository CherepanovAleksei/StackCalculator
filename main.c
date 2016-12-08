#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>



typedef struct node
{
    int value; //значение
    int category;//разряд(сколько цифр до начала)
    struct node *next;
    struct node *prev;
    struct node *first;
} node;

typedef struct double_linked_list
{
    int size;
    node *head;
    node *tail;
} dbl_list;


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
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->first = NULL;
    return tmp;
}

void node_add(dbl_list *dbll, int c, int flag)
{
    node*new_struct=node_create();

    new_struct->value = c;
    if (flag == 0)
    {
        new_struct->category=1;
        new_struct->first=new_struct;
    }
    else
    {
        new_struct->category=dbll->head->category+1;
        new_struct->first=dbll->head->first;
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
    if(dbll->head == dbll->tail)
    {
        node *tmp = dbll->head;
        dbll->head=NULL;
        dbll->tail=NULL;
        free(tmp);
    }
    else
    {
        node *tmp = dbll->head;
        if (dbll->head == NULL)
        {
            printf("problems with delete!!!");
            exit(2);
        }
        dbll->head=dbll->head->next;
        dbll->head->prev=NULL;
        free(tmp);
        dbll->size--;
    }
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
    node *buff = NULL;

    while (pointer!=dbll->head)
    {
        printf("%d",pointer->value);
        buff = pointer->prev;
        pointer = buff;
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
        node_add(dbll, value, flag);
        flag++;

        if(tmp->category == 1)
        {
            break;
        }
        tmp=tmp->next;
    }
}

void sum(dbl_list *dbll)
{
    dbl_list* dbll_buff=create_dbl_list();
    node *num1 = dbll->head->first->next;
    node *num2 = dbll->head;

    if (num2->category >= num1->category) //переприсвавает если 1<2
    {
        num1 = dbll->head;
        num2 = dbll->head->first->next;
    }

    int sum;
    int plus=0;
    int flag=0;
    int a;//num1(value)
    int b;//num2(value)

    while(1)
    {
        a=num1->value;
        b=num2->value;
        sum=(a+b+plus)%10;
        plus=(a+b+plus)/10;

        node_add(dbll_buff, sum, flag);
        flag++;

        if(num2->category==1)
        {
            num2->value=0;
        }
        else
        {
            num2=num2->next;
        }

        if(num1->category==1)
        {
            break;
        }
        else
        {
            num1=num1->next;
        }
    }

    if(plus)
    {
        node_add(dbll_buff, plus, flag);
    }

    number_delete(dbll);
    number_delete(dbll);
    buff_to_dbll(dbll_buff,dbll);
}

int main()
{
    dbl_list* dbll=create_dbl_list();
    char c;
    int flag=0;
    c=getchar();
    while(c!='q')
    {
        switch (c)
        {
        case '+':
            sum(dbll);
            break;
        case 'd':
            number_delete(dbll);
            break;
        case 'r':
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
                node_add(dbll, c-'0',flag);
                flag++;
            }
            else
            {
                flag=0;
                printf("принято\n");
            }
            break;
        }

        c=getchar();
    }

    delete_dbl_list(&dbll);

    return 0;
}
