#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<conio.h>
#define CARGO 20

//Global variables
int d_cargo = 10;
char submit;
int choose = 0;
int person = 0;
int amount;
int position;
int select;
int i;

struct stock {
    char name[15];
    float price;
    int remain;
} products[CARGO] = {
                        {"Chocolate",100, 10},
                        {"Cookies and cream",150, 10},
                        {"Green tea",200, 10},
                        {"Mango",250, 10},
                        {"Raspberry Ripple",300, 10},
                        {"Strawberry",350, 10},
                        {"Vanilla",400, 10},
                        {"Hokey pokey",450, 10},
                        {"Cotton candy",500, 10},
                        {"Grape",550, 10},
                    };

//Function prototypes
void show(int person);
void search();
void buy();
void user();
void admin();
void p_add();
void p_del();
void s_add();
void s_del();
void p_edit();
char *check_stock(int step);
int find(int choose);

void show(int person) {
     printf("Name\t\t\t\tPrice\t\tStock\n");
     for (i = 0;i < d_cargo;++i)
     {
        printf("%02d. %-15s\t\t%.2f Baht", i+1, products[i].name, products[i].price);
        if (person)
            printf("\t%d\n", products[i].remain);
        else
            printf("\t%s\n", check_stock(i));
     }
}

char *check_stock(int step) {
    if (products[step].remain > 0)
        return "In stock";
    return "Out of stock";
}

int find(int choose) {
    for (i = 0;i < d_cargo;++i) {
        if (choose-1 == i)
            return i;
    }
};

void search() {
    system("cls");
    char p_name[15], find[15];
    int c = 0,  n = 1, keep[20];
    printf("search\n");
    fflush(stdin);
    scanf("%[^\n]s", &p_name);
    for (i = 0;i < d_cargo; ++i)
    {
        for (int j = 0;j < strlen(products[i].name); ++j)
        {
             for (int k = 0; k < strlen(p_name); ++k)
            {
                /*if (tolower(p_name[k]) == tolower(products[i].name[j]))
                    keep[c++] = i;
                */
                find[k] = tolower(products[i].name[k+j]);
                find[k+1] = '\0';
            }

           //printf("%s\n", find);
           if (!strcmp(find, p_name))
                keep[c++] = i;
        }

    }
    for (i = 0;i < c; ++i) {
        if (keep[i] != keep[i+1])
            printf("%02d. %s %.2f Baht\n",n++, products[keep[i]].name, products[keep[i]].price);
    }
    if (c == 0)
        printf("not found\n");
    printf("PRESS ANY KEY TO CONTINUE\n");
    getch();
}

void buy() {
    system("cls");
    int count;
    float money,total;
    show(person=0);
    printf("buy (1-10) : ");
    scanf("%d", &choose);
    printf("amount (number only) : ");
    scanf("%d", &count);
    position = find(choose);
    if (position == -1)
    {
        printf("\n---------------------\n");
        printf("not found\n");
        printf("---------------------\n");
    }
    else
    {
        total = products[position].price*count;
        printf("\n---------------------\n");
        printf("Name : %s x %d\n", products[position].name, count);
        printf("Total : %.2f Baht\n", total);
        printf("---------------------\n");
        printf("Do you want to buy this product? (Y/N)\n");
        fflush(stdin);
        scanf("%c", &submit);
        if (toupper(submit) == 'Y')
        {
            printf("\n---------------------\n");
            printf("Your cash : ");
            scanf("%f", &money);
            printf("Balance : %.2f\n", money-total);
            printf("Thankyou!!!\n");
            printf("---------------------\n");
            products[position].remain -= count;
        }
    }
    printf("PRESS ANY KEY TO CONTINUE\n");
    getch();

}

void user() {
    system("cls");
    printf("What do you want?\n");
    printf("1.Buy Products\n");
    printf("2.Search Products\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1: buy();;
                break;
        case 2: search();
                break;
        default: printf("Wrong choice\n");
                 printf("PRESS ANY KEY TO CONTINUE\n");
                 getch();
    }
}

void s_add() {
    printf("Select Product : ");
    scanf("%d", &choose);
    printf("Add : ");
    scanf("%d", &amount);
    position = find(choose);
    products[position].remain += amount;
}

void s_del() {
    printf("Select Product : ");
    scanf("%d", &choose);
    printf("Del : ");
    scanf("%d", &amount);
    position = find(choose);
    products[position].remain -= amount;
    if (products[position].remain < 0)
        products[position].remain = 0;
}

void p_add() {
    printf("Name Product : ");
    scanf("%s", &products[d_cargo].name);
    printf("Price Product : ");
    scanf("%f", &products[d_cargo].price);
    printf("Stock Product : ");
    scanf("%d", &products[d_cargo].remain);
    d_cargo++;
}

void p_del() {
    printf("Select Product : ");
    scanf("%d", &choose);
    if(choose < 0 || choose > d_cargo)
    {
        printf("Invalid Number! Please enter number between 1 to %d\n", d_cargo);
    }
    else
    {
        printf("Are you sure? (Y/N)\n");
        scanf(" %c", &submit);
        if (toupper(submit) == 'Y')
        {
            for(i = choose-1; i < d_cargo-1; ++i)
                products[i] = products[i + 1];
            d_cargo--;
        }
    }

}

void p_edit() {
    printf("Select Product : ");
    scanf("%d", &choose);
    printf("1.EDIT Name\n");
    printf("2.EDIT Price\n");
    printf("3.EDIT Stock\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1: printf("Old Name Product : %s\n", products[choose].name);
                printf("New Name Product : ");
                scanf("%s", &products[choose].name);
                break;
        case 2: printf("Old Price Product : %.2f\n", products[choose].price);
                printf("New Price Product : ");
                scanf("%f", &products[choose].price);
                break;
        case 3: printf("Old Remain Product : %d\n", products[choose].remain);
                printf("New Remain Product : ");
                scanf("%d", &products[choose].remain);
                break;
        default: printf("Wrong choice\n");
                 printf("Click some character from keyboard\n");
                 getch();
    }
}

void admin() {
    while (1)
    {
        system("cls");
        show(person=1);
        printf("Options\n");
        printf("1.ADD Stock\n");
        printf("2.DEL Stock\n");
        printf("3.ADD Product\n");
        printf("4.DEL Product\n");
        printf("5.EDIT Product\n");
        printf("6.EXIT\n");
        printf("Select number : ");
        scanf("%d", &select);
        switch(select)
        {
            case 1: s_add();
                    break;
            case 2: s_del();
                    break;
            case 3: p_add();
                    break;
            case 4: p_del();
                    break;
            case 5: p_edit();
                    break;
            case 6: submit = 'N';
                    break;
            default: printf("Wrong choice\n");
                     printf("PRESS ANY KEY TO CONTINUE\n");
                     getch();
        }
        if (submit == 'N')
            break;
    };
};

int main() {
    do
    {
        system("cls");
        printf("1.User\n");
        printf("2.Admin\n");
        scanf("%d", &select);
        switch(select)
        {
            case 1: user();
                    break;
            case 2: admin();
                    break;
            default: printf("Wrong choice\n");
                     printf("PRESS ANY KEY TO CONTINUE\n");
                     getch();
        }
        system("cls");
        printf("Do you want to exit? (Y/N)\n");
        printf("Yes - Exit Program\n");
        printf("No - Back to Menu page\n");
        fflush(stdin);
        scanf(" %c", &submit);
    } while (toupper(submit) == 'N');
    return 0;
}

