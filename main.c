#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
    char item_name[10]; // for item name  and 10 is length of name
    int item_quantity;
    int item_price;
    int total_price;

    struct node *next; // for next node address
    struct node *pre;  // for previous node address
};

struct node *current = NULL;
struct node *last = NULL;
struct node *head = NULL;
struct node *back = NULL; // it will follow new node and stay after that
char username[1000][20];  //20 is max. length of username
char password[1000][20];  //20 is length of password
int amount[1000];         //amount in your wallet
int price[6] = {50, 500, 200, 150, 240, 70};
char item[6][10] = {"Soap", "Basket", "Powder", "Shampoo", "Rice", "Salt"};

char temp_user[20], temp_pass[20], main_pass[20];
int count = 0;
int ii;

void wallet();
void shopping();
int login();
void add();
void del();
void display();

int main()
{
    int login_choice;
    do
    {
        int k;
        k = login();
        if (k == 1)
            goto z;
        head = NULL;
        int cc;
        printf("\nCURRENT BALANCE : %d ", amount[ii]);
        printf("\n1 FOR DEPOSITE AMOUNT IN WALLET\n2 FOR SHOPPING \n");
        printf("ENTER CHOICE : ");
        scanf("%d", &cc);
        if (cc == 1)
            wallet();
        shopping();

    z:
        printf("\n1 FOR NEW LOGIN\n2 FOR EXIT\n");
        printf("ENTER CHOICE : ");
        scanf("%d", &login_choice);
    } while (login_choice == 1);

    return 0;
}

int login()
{

    printf("\nENTER YOUR E-MAIL ID AS USERNAME :");
    fflush(stdin);
    scanf("%[^\n]*s", temp_user);
    for (ii = 0; ii < count; ii++)
    {
        if (strcmp(temp_user, username[ii]) == 0)
        {
            strcpy(main_pass, password[ii]);

            break;
        }
    }

    if (ii < count)
    {
        int ff = 0; // for check 1 time or not
        do
        {
            if (ff++ > 0)
            {
                int tt;
                printf("\nWRONG PASSWORD!!!\n1 FOR TRY AGAIN\n2 FOR EXIT : ");
                printf("\nENTER CHOICE : ");
                scanf("%d", &tt);

                if (tt == 1)
                    goto z;
                else
                {
                    return 1;
                }
            }
        z:
            printf("\nENTER YOUR PASSWORD :");
            fflush(stdin);
            scanf("%[^\n]*s", temp_pass);
            ff++;
        } while (strcmp(temp_pass, main_pass) != 0);
        printf("\nSUCCESSFULLY lOGINED!!!\n");
    }
    else
    {
        strcpy(username[count], temp_user);
        printf("\nNO SUCH USERNAME EXIST");
        fflush(stdin);
        printf("\nTO CREATE ACCOUNT \nSET PASSWORD :");
        scanf("%[^\n]*s", password[count]);
        count++;
        printf("\nYOU HAVE SUCCESSFULLY CREATED YOUR ACCOUNT!!");
        amount[ii] = 200;
        printf("\nCONGRATS YOU GOT 200 Rs IN YOUR WALLET!!!\n");
    }

    return 0;
}

void wallet()
{
    int td;
    printf("\nENTER AMOUNT YOU WANT TO DEPOSITE : ");
    scanf("%d", &td);
    if(td<0)
    {
        printf("\nYOU CAN'T DEPOSITE NEGATIVE AMOUNT\n");
        return;
    }
    amount[ii] += td;
    printf("\n YOUR CURRENT AMOUNT IN WALLET IS : %d\n", amount[ii]);
}

void shopping()
{
    int sc;

    do
    {
        printf("\n0 FOR DEPOSITE AMOUNT\n1 FOR ADD TO CART\n2 FOR REMOVE FROM CART\n3 FOR DISPLAY\n4 FOR EXIT\n");
        scanf("%d", &sc);
        if (sc == 0)
        {
            wallet();
        }
        else if (sc == 1)
        {
            add();
        }
        else if (sc == 2)
        {

            del();
        }
        else if (sc == 3)
        {
            display();
        }
    } while (sc < 4);
}

void add()
{
    printf("\n1.Soap -> 50 Rs\n2.Basket -> 500 Rs \n3.Powder -> 200 Rs\n4.Shampoo -> 150 Rs\n5.Rice -> 240 Rs\n6.Salt -> 70 Rs\n"); //{50, 500, 200, 150, 240, 70};
    int it, qq;

    struct node *p;

    scanf("%d", &it);
    printf("\nENTER QUANTITY : ");
    scanf("%d", &qq);
    p = (struct node *)malloc(sizeof(struct node));
    strcpy(p->item_name, item[it - 1]);
    p->item_quantity = qq;
    p->item_price = price[it - 1];
    p->total_price = price[it - 1] * qq;

    if (head == NULL)
    {
        p->pre = NULL;
        p->next = NULL;
        back = p;
        head = p;
        last = p;
        current = p;
    }
    else
    {
        back->next = p;
        p->pre = back;
        back = p;
        p->next = NULL;
        last = p;
    }
}

void del()
{
    printf("ENTER NAME OF ITEM:\n");
    fflush(stdin);
    char s[10];
    scanf("%[^\n]s", s);
    struct node *p;
    p = head;
    while (p != NULL && strcmp(p->item_name, s))
    {
        p = p->next;
    }
    if (p == NULL)
        printf("THIS ITEM  IS NOT FOUND IN LIST!!!\n");
    else
    {
        if (p != head && p != last)
        {
            p->pre->next = p->next;
            p->next->pre = p->pre;
        }
        else if (p == head && p == last)
            head = NULL;
        else if (p == head)
        {
            p->next->pre = NULL;
            head = p->next;
        }
        else
        {
            p->pre->next = NULL;
            last = p->pre;
        }
        printf(" %s IS REMOVED SUCCESSFULLY\n", p);
        if (head == NULL)
        {
            printf("LIST IS EMPTY.\n");
        }
    }
}

void display()
{

    int i = 1;
    struct node *p;
    int total = 0;
    p = head;
    if (head == NULL)
    {
        printf("CART IS EMPTY!!! ");
        return;
    }
    printf("LIST OF ITEM IN CART :\n");
    printf("no.\tNAME\t\tPRICE\tQUANTITY\tTOTAL PRICE\n");

    while (p != NULL)
    {

        printf("%d\t%s\t\t%d\t%d\t\t%d \n", i, p->item_name, p->item_price, p->item_quantity, p->total_price);
        total += p->total_price;
        i++;
        p = p->next;
    }

    printf("\nFINAL AMOUNT : %d ", total);
    printf("\n");

    int y;
    printf("YOW WANT TO PROCEED??\n1 for YES\n2 for NO\n");
    scanf("%d", &y);
    if (y == 1)
    {
        if (amount[ii] - total < 0)
        {
            printf("\nNOT ENOUGH MONEY AVAILABLE");
            printf("\nYOUR BALANCE : %d\n", amount[ii]);
        }
        else
        {
            amount[ii] -= total;
            printf("\nREMAINING BALANCE : %d ", amount[ii]);
            head = NULL;
        }
    }
}
