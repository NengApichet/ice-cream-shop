#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define CARGO 20 //ประกาศใช้ใน array of struct stock

//Global variables
int d_cargo = 10;
char submit;
int choose;
int person = 0;
int amount;
int position;
int select;
int i, j, k;

struct stock
{
    char name[30];
    float price;
    int remain;
} products[CARGO];

/*
ตัวใหม่ที่คิดว่า ไม่เคยเจอ
    fflush(stdin);
    system("cls"); ดึงจาก --> stdlib.h
    atoi(); ดึงจาก --> stdlib.h
    atof(); ดึงจาก --> stdlib.h
    getch(); ดึงจาก  --> conio.h
*/

//Function prototypes
void intro();                    //ป้ายร้าน
void center(char *s, int width); //จัดข้อความให้อยู่ตรงกลาง
void show(int person);           //แสดงตารางสินค้า
void search();                   //ค้นหาสินค้า
void buy();                      //เลือกซื้อสินค้า
void pay(int pos);               //จ่ายเงิน
void user();                     //แสดงหน้าผู้ใข้
void admin();                    //แสดงหน้า admin
void p_add();                    //เพิ่มสต๊อกสินค้า
void p_del();                    //ลดสต๊อกสินค้า
void s_add();                    //เพิ่มสินค้า
void s_del();                    //ลดสินค้า
void p_edit();                   //แก้ไขสินค้า
void red();                      //แสดงข้อความสีแดง
void cyan();                     //แสดงข้อความสีฟ้าอ่อน
void green();                    //แสดงข้อความสีเขียว
void yellow();                   //แสดงข้อความสีเหลือง
void reset();                    //คืนค่าสีข้อความปกติ
char *check_stock(int step);     //แสดงสินค้าคงเหลือ สำหรับผู้ใช้
int find(int choose);            //หาตำแหน่งสินค้า

int main()
{
    FILE *fp;
    fp = fopen("menu.txt", "r");
    char temp_name[30];
    char temp_number[5];

    if (!fp)
    {
        printf("Program can't find \"menu.txt\"");
        getch();
        return 1;
    }

    for (i = 0; i < 10; ++i)
    {
        fscanf(fp, "%s", temp_name);
        for (j = 0; temp_name[j] != '\0'; ++j)
        {
            if (temp_name[j] == '_')
            {
                temp_name[j] = 32; //space
            }
        }
        strcpy(products[i].name, temp_name);
        fscanf(fp, "%s", temp_number);
        products[i].price = atof(temp_number);
        fscanf(fp, "%s", temp_number);
        products[i].remain = atoi(temp_number);
    }
    fclose(fp);

    do
    {
        system("cls");
        intro();
        yellow();
        center("----Welcome----", 80);
        printf("\n");
        center("1.Customer", 80);
        center("2.Owner", 80);
        printf("\n\n");
        reset();

        printf("Please choose a number\n");
        printf("Enter number : ");
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            user();
            break;
        case 2:
            admin();
            break;
        default:
            red();
            printf("Invalid Number! Please enter number between 1 or 2\n");
            printf("Press any key to continue\n");
            reset();
            getch();
        }
        system("cls");
        intro();
        printf("Do you want to exit? (Y/N)\n");
        printf("\nYes - Exit Program\n");
        green();
        printf("No - Back to Menu page\n\n");
        reset();
        fflush(stdin);
        scanf("%c", &submit);
    } while (toupper(submit) == 'N');
    return 0;
}

void cyan()
{
    printf("\033[0;36m");
}

void red()
{
    printf("\033[1;31m");
}

void yellow()
{
    printf("\033[1;33m");
}

void green()
{
    printf("\033[0;32m");
}

void reset()
{
    printf("\033[0m");
}

void intro()
{

    cyan();
    printf("\t****************************************************************************\n");
    printf("\t*    _                                                _                    *\n");
    printf("\t*   (_)                                              | |                   *\n");
    printf("\t*    _  ___ ___    ___ _ __ ___  __ _ _ __ ___    ___| |__   ___  _ __     *\n");
    printf("\t*   | |/ __/ _ \\  / __| '__/ _ \\/ _` | '_ ` _ \\  / __| '_ \\ / _ \\| '_ \\    *\n");
    printf("\t*   | | (_|  __/ | (__| | |  __/ (_| | | | | | | \\__ \\ | | | (_) | |_) |   *\n");
    printf("\t*   |_|\\___\\___|  \\___|_|  \\___|\\__,_|_| |_| |_| |___/_| |_|\\___/| .__/    *\n");
    printf("\t*                                                                | |       *\n");
    printf("\t*                                                                |_|       *\n");
    printf("\t****************************************************************************\n");
    printf("\n\n");
    reset();
}

void center(char *txt, int width)
{
    int padlen1 = (width - strlen(txt)) / 2;
    int padlen2 = padlen1;
    if ((padlen1 * 2 + strlen(txt)) != width)
        padlen1++;
    printf("%*s%s%*s\n", padlen1, "", txt, padlen2, "");
}

void show(int person)
{
    center("Menu", 80);
    printf("\t ------------------------------------------------------------------ \n");
    printf("\t|  No. | Name\t\t\t\t| Price\t\t| Stock    |\n");
    printf("\t ------------------------------------------------------------------ \n");
    for (i = 0; i < d_cargo; ++i)
    {
        if (products[i].remain <= 0)
            red();
        printf("\t|  %02d. | %-15s\t\t| %.2f Baht", i + 1, products[i].name, products[i].price);
        if (person)
            printf("\t| %d\t   |\n", products[i].remain);
        else
            printf("\t| %s |\n", check_stock(i));
        reset();
    }
    printf("\t ------------------------------------------------------------------ \n");
}

char *check_stock(int step)
{
    if (products[step].remain > 0)
        return "In stock";
    return "Sold out";
}

int find(int choose)
{
    for (i = 0; i < d_cargo; ++i)
    {
        if (choose - 1 == i)
            return i;
    }
    return -1;
};

void search()
{
    system("cls");
    char p_name[30], finds[30], temp[20][30], check;
    int keep[20];
    int c = 0;
    int n = 0;
    printf("--- Search ---\n");
    printf("Type whatever you want...\n");
    fflush(stdin);
    scanf("%[^\n]s", &p_name);
    for (i = 0; i < d_cargo; ++i)
    {
        for (j = 0; j < strlen(products[i].name); ++j)
        {
            for (k = 0; k < strlen(p_name); ++k)
            {
                finds[k] = tolower(products[i].name[k + j]);
                finds[k + 1] = '\0';
            }
            if (strcmp(finds, p_name) == 0) {
                keep[c++] = i;
            }
        }
    }
    
    printf("\n");
    for (i = 0; i < c; ++i)
    {
        if (keep[i] != keep[i + 1] || c == 1)
        {
            printf("%02d. %s %.2f Baht\n", n + 1, products[keep[i]].name, products[keep[i]].price);
            strcpy(temp[n++], products[keep[i]].name);
        }
    }
    if (c == 0)
    {
        red();
        printf("\nNot found\n");
        printf("Press any key to continue\n");
        reset();
        getch();
    }
    else
    {
        printf("\n\nDo you want to buy something in here ? (Y/N)\n");
        fflush(stdin);
        scanf("%c", &check);
        if (toupper(check) == 'Y')
        {
            if (n == 1)
            {
                for (i = 0; i < d_cargo; ++i)
                {
                    if (strcmp(products[i].name, temp[0]) == 0)
                    {
                        pay(i);
                        break;
                    }
                }
            }
            else
            {
                printf("\n\tSelect Number (1-%d) : ", n);
                scanf("%d", &choose);
                for (i = 0; i < d_cargo; ++i)
                {
                    if (strcmp(products[i].name, temp[choose-1]) == 0)
                    {
                        pay(i);
                        break;
                    }
                }
            }
        }
    }
}

void buy()
{
    system("cls");
    show(person = 0);
    cyan();
    printf("\t--- Buy Products ---\n");
    printf("\tSelect Number (1-%d) : ", d_cargo);
    scanf("%d", &choose);
    reset();
    position = find(choose);
    if (position == -1)
    {
        red();
        printf("\n--------------------\n\n");
        printf("Not found\n");
        printf("Press any key to continue\n");
        reset();
        getch();
    }
    else
        pay(position);
}

void pay(int pos)
{
    int count;
    float money, total;
    printf("\tQuantity (limit %d) : ", products[pos].remain);
    scanf("%d", &count);
    if (count > products[pos].remain)
    {
        red();
        printf("\nSorry, stock of product is not enough\n");
    }
    else
    {
        total = products[pos].price * count;
        printf("\n--------------------\n\n");
        printf("Name : %s x %d\n", products[pos].name, count);
        printf("Total : %.2f Baht\n", total);
        printf("\n--------------------\n\n");
        printf("Do you want to buy this product? (Y/N)\n");
        fflush(stdin);
        scanf("%c", &submit);
        if (toupper(submit) == 'Y')
        {
            printf("\n--------------------\n\n");
            printf("Your cash : ");
            scanf("%f", &money);
            if (money < total)
            {
                printf("\n--------------------\n\n");
                red();
                printf("Sorry, Your money is not enough\n");
            }
            else
            {
                printf("Balance : %.2f Baht\n", money - total);
                printf("\n--------------------\n\n");
                green();
                printf("Thank you\n");
                products[pos].remain -= count;
            }
        }
    }
    printf("Press any key to continue\n");
    reset();
    getch();
}

void user()
{
    system("cls");
    intro();
    green();
    printf("\t\t1. Buy Products\n");
    printf("\t\t2. Search Products\n");
    red();
    printf("\t\t3. Exit\n");
    reset();
    printf("\nPlease choose a number\n");
    printf("Enter number : ");
    scanf("%d", &select);
    switch (select)
    {
    case 1:
        buy();
        break;
    case 2:
        search();
        break;
    case 3:
        break;
    default:
        red();
        printf("\nInvalid Number! Please enter number between 1 to 3 \n");
        printf("Press any key to continue\n");
        reset();
        getch();
    }
}

void s_add()
{
    yellow();
    printf("\t--- Add Stock ---\n");
    printf("\tSelect Product (1-%d): ", d_cargo);
    scanf("%d", &choose);
    reset();
    if (choose < 0 || choose > d_cargo)
    {
        red();
        printf("\nInvalid Number! Please enter number between 1 to %d\n", d_cargo);
        printf("Press any key to continue\n");
        reset();
        getch();
    }
    else
    {
        printf("\n\nQuantity (numbers only) : ");
        scanf("%d", &amount);
        position = find(choose);
        products[position].remain += amount;
    }
}

void s_del()
{
    yellow();
    printf("\t--- Remove Stock ---\n");
    printf("\tSelect Product (1-%d): ", d_cargo);
    scanf("%d", &choose);
    reset();
    if (choose < 0 || choose > d_cargo)
    {
        red();
        printf("\nInvalid Number! Please enter number between 1 to %d\n", d_cargo);
        printf("Press any key to continue\n");
        reset();
        getch();
    }
    else
    {
        printf("\n\nQuantity (numbers only) : ");
        scanf("%d", &amount);
        position = find(choose);
        products[position].remain -= amount;
        if (products[position].remain < 0)
            products[position].remain = 0;
    }
}

void p_add()
{
    yellow();
    printf("\t--- Add Product ---\n\n");
    reset();
    printf("Name Product : ");
    fflush(stdin);
    scanf("%[^\n]s", &products[d_cargo].name);
    printf("\nPrice Product (numbers only) : ");
    scanf("%f", &products[d_cargo].price);
    printf("\nStock Product (numbers only) : ");
    scanf("%d", &products[d_cargo].remain);
    d_cargo++;
}

void p_del()
{
    yellow();
    printf("\t--- Delete Product ---\n");
    printf("\tSelect Product (1-%d): ", d_cargo);
    scanf("%d", &choose);
    reset();
    if (choose < 0 || choose > d_cargo)
    {
        red();
        printf("\nInvalid Number! Please enter number between 1 to %d\n", d_cargo);
        printf("Press any key to continue\n");
        reset();
        getch();
    }
    else
    {
        printf("\n\nAre you sure? (Y/N)\n");
        fflush(stdin);
        scanf("%c", &submit);
        if (toupper(submit) == 'Y')
        {
            for (i = choose - 1; i < d_cargo - 1; ++i)
                products[i] = products[i + 1];
            d_cargo--;
        }
    }
}

void p_edit()
{
    yellow();
    printf("\t--- Edit Product ---\n");
    printf("\tSelect Product (1-%d): ", d_cargo);
    scanf("%d", &choose);
    if (choose < 0 || choose > d_cargo)
    {
        red();
        printf("\nInvalid Number! Please enter number between 1 to %d\n", d_cargo);
        printf("Press any key to continue\n");
        reset();
        getch();
    }
    else
    {
        green();
        printf("\t1. Edit Name\n");
        printf("\t2. Edit Price\n");
        printf("\t3. Edit Stock\n");
        reset();
        printf("\nPlease choose a number\n");
        printf("Enter number : ");
        scanf("%d", &select);
        printf("\n");
        choose -= 1;
        switch (select)
        {
        case 1:
            printf("Old Name Product : %s\n", products[choose].name);
            printf("New Name Product : ");
            scanf("%s", &products[choose].name);
            break;
        case 2:
            printf("Old Price Product : %.2f Baht\n", products[choose].price);
            printf("New Price Product : ");
            scanf("%f", &products[choose].price);
            break;
        case 3:
            printf("Old Remain Product : %d\n", products[choose].remain);
            printf("New Remain Product : ");
            scanf("%d", &products[choose].remain);
            break;
        default:
            red();
            printf("\nInvalid Number! Please enter number between 1 to 3 \n");
            printf("Press any key to continue\n");
            reset();
            getch();
        }
    }
}

void admin()
{
    while (1) //1 == true
    {
        system("cls");
        show(person = 1);
        yellow();
        printf("\n\t--- Options ---\n");
        cyan();
        printf("\t1. Add Stock\n");
        printf("\t2. Remove Stock\n");
        printf("\t3. Add Product\n");
        printf("\t4. Delete Product\n");
        printf("\t5. Edit Product\n");
        red();
        printf("\t6. Exit\n");
        reset();
        printf("\nPlease choose a number\n");
        printf("Enter number : ");
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            system("cls");
            show(person = 1);
            s_add();
            break;
        case 2:
            system("cls");
            show(person = 1);
            s_del();
            break;
        case 3:
            system("cls");
            show(person = 1);
            p_add();
            break;
        case 4:
            system("cls");
            show(person = 1);
            p_del();
            break;
        case 5:
            system("cls");
            show(person = 1);
            p_edit();
            break;
        case 6:
            submit = 'N';
            break;
        default:
            red();
            printf("Invalid Number! Please enter number between 1 to 6 \n");
            printf("Press any key to continue\n");
            reset();
            getch();
        }
        if (submit == 'N')
            break;
    };
};