#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct node
{
    int value; //значение
    int category;//разряд(сколько цифр до начала)
    char minus;
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

    if(pointer->minus > 0)
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

        node_add(dbll_buff, sum, flag, 0);
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
        node_add(dbll_buff, plus, flag, 0);
    }

    number_delete(dbll);
    number_delete(dbll);
    buff_to_dbll(dbll_buff,dbll);
}

void subtraction(dbl_list *dbll)
{
    dbl_list* dbll_buff=create_dbl_list();
    node *num1 = dbll->head->first->next;
    node *num2 = dbll->head;
    char minus=0;
    if (num2->category > num1->category || (num2->category == num1->category && num2->first->value > num1->first->value)) //переприсвавает если 1<2
    {
        num1 = dbll->head;
        num2 = dbll->head->first->next;
        minus++;
    }
    node *buff;

    int flag=0;
    int a;//num1(value)
    int b;//num2(value)

    while(1)
    {
        a=num1->value;
        b=num2->value;
        if (a<b)
        {
            a+=10;
            buff=num1->next;
            while(1)
            {
                if(!buff->value)
                {
                    buff->value=9;
                    buff=buff->next;
                }
                else
                {
                    buff->value--;
                    break;
                }
            }

        }

        node_add(dbll_buff, a-b, flag, 0);
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

    buff=dbll_buff->head;
    if(buff->value==0)
    {
        while(1)
        {
            node_del(dbll_buff);
            buff=dbll_buff->head;
            if(buff->value!=0)
            {
                break;
            }
        }
    }

    /** Альтернатива
    while(1)
    {
        buff=dbll_buff->head;
        if(buff->value==0)
        {
            node_del(dbll_buff);
        }
        else
        {
            break;
        }
    }*/

    number_delete(dbll);
    number_delete(dbll);
    buff_to_dbll(dbll_buff,dbll);

    if(minus)
    {
        change_sign(dbll);
    }
}

void multiplication(dbl_list *dbll)
{
    dbl_list* dbll_buff=create_dbl_list();
    node *num1 = dbll->head->first->next;
    node *num2 = dbll->head;

    if (num2->category > num1->category) //переприсвавает если 1<2
    {
        num1 = dbll->head;
        num2 = dbll->head->first->next;
    }

    node *begin_of_num1 = num1;
    int cat1=num1->category;
    int flag=0;
    int i;
    int count=num1->category+num2->category;

    for(i=0;i<count;i++)
    {
        node_add(dbll_buff, 0, flag, 0);
        flag++;
    }

    node *tmp=dbll_buff->tail;
    node *last_pos_of_tmp=tmp;
    int a;//num1(value)
    int b=num2->value;//num2(value)
    int plus=0;

    while(1)
    {
        a=num1->value;
        tmp->value+=a*b;

        if(num1->category==1)
        {
            tmp=last_pos_of_tmp;
            plus=0;

            for(i=0;i<=cat1;i++)//на 1 больше
            {
                tmp->value+=plus;
                plus=0;
                while(tmp->value > 9)
                {
                    tmp->value-=10;
                    plus++;
                }
                tmp = tmp->prev;
            }

            if(num2->category==1)
            {
                break;
            }
            else
            {
                num1=begin_of_num1;
                last_pos_of_tmp=last_pos_of_tmp->prev;
                tmp=last_pos_of_tmp;
                num2=num2->next;
                b=num2->value;
            }
        }
        else
        {
            num1=num1->next;
            tmp=tmp->prev;
        }
    }

    tmp=dbll_buff->head;
    if(tmp->value==0)
    {
        while(1)
        {
            node_del(dbll_buff);
            tmp=dbll_buff->head;
            if(tmp->value!=0)
            {
                break;
            }
        }
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
    char minus=0;
    c=getchar();
    while(c!='q')
    {
        switch (c)
        {
        case '+':
            //++
            if(dbll->head->minus==0 && dbll->head->first->next->minus==0)
            {
                sum(dbll);
            }
            //--
            else if (dbll->head->minus > 0 && dbll->head->first->next->minus > 0)
            {
                sum(dbll);
                change_sign(dbll);
            }
            //+-
            else if (dbll->head->minus > 0 && dbll->head->first->next->minus == 0)
            {
                subtraction(dbll);
            }
            //-+
            else if (dbll->head->minus == 0 && dbll->head->first->next->minus > 0)
            {
                subtraction(dbll);
                change_sign(dbll);
            }
            break;
        case '-':
            minus++;
            break;
        case '*':
            //++ --
            if(dbll->head->minus == dbll->head->first->next->minus)
            {
                multiplication(dbll);
            }
            //+- -+
            else if (dbll->head->minus != dbll->head->first->next->minus)
            {
                multiplication(dbll);
                change_sign(dbll);
            }
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
                node_add(dbll, c-'0',flag, minus);
                flag++;
                minus=0;
            }
            else
            {
                if(minus)
                {
                    //++
                    if(dbll->head->minus==0 && dbll->head->first->next->minus==0)
                    {
                        subtraction(dbll);
                    }
                    //--!
                    else if (dbll->head->minus > 0 && dbll->head->first->next->minus > 0)
                    {
                        subtraction(dbll);
                        change_sign(dbll);
                    }
                    //+-
                    else if (dbll->head->minus > 0 && dbll->head->first->next->minus == 0)
                    {
                        sum(dbll);
                    }
                    //-+
                    else if (dbll->head->minus == 0 && dbll->head->first->next->minus > 0)
                    {
                        sum(dbll);
                        change_sign(dbll);
                    }
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
