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


node* create()
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

void node_add(dbl_list *dbll, char c, int flag)
{
    node*new_struct=create();
//возможно сюда надо адрес, но все работает
    new_struct->value = c-'0';
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
        //printf("del1\n");
        //next = tmp->next;
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
        printf("del\n");
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*dbll);
    (*dbll) = NULL;
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
            printf("its plus\n");
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
                node_add(dbll, c,flag);
                flag++;
            }
            else
            {
                flag=0;
                printf("принято--\\n\n");
            }
            break;
        }
        c=getchar();
    }

    delete_dbl_list(&dbll);

    return 0;
}
