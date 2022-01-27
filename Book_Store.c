#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int counter=0;
//structure for the admin book management
struct node
{
    char Bname[200];
    int price;
    struct node *prev;
    struct node *next;
} * header;
//structure for the customer book management
struct order
{
    char Bname[200];
    int price, qty;
    struct order *prev1;
    struct order *next1;
} * header1;

void sort_book(){
    printf("Function called!!\n");
    printf("HEAD-->%x\n", header);
    for(struct node *i = header; i != NULL; i=i->next){
        for(struct node *j = i; j->next != NULL; j=j->next){
            printf("Enter loop\n");
            // Comparing j with j->next, swap if j->next is lexicographically ahead
            if(strcmp(j->next->Bname, j->Bname) > 0){
                printf("Swapping %s with %s\n", j->Bname, j->next->Bname);
                // swap book name
                char temp_name[200];
                strcpy(temp_name, j->Bname);
                strcpy(j->Bname, j->next->Bname);
                strcpy(j->next->Bname, temp_name);

                // swap price
                int temp_price = j->price;
                j->price = j->next->price;
                j->next->price = temp_price;
            }
        }
    }
}

// serach book by title
struct node *search_book(struct node *header){
    char key[200];
    int found = 0;
    printf("Key: ");
    getc(stdin);
    fgets(key, 200, stdin);
    struct node *p;
    for(p = header; p != NULL; p = p->next){
        if(strcmp(key, p->Bname) == 0){
            found = 1;
            break;
        }
    }
    if(found)
        return p;
    else{
        printf("Not Found!!\n");
        return NULL;
    }
}

// 12:38am: TRY RUNNING WHEN YOU RETURN

void showBill(struct order *bill){
    int total = 0, index = 0;
    printf("Sl.no\tBook\tQty\tPrice\n");
    for(struct order *p = bill; p != NULL; p = p->next1){
        int i = 0;
        while(p->Bname[i] != '\n' && p->Bname[i] != '\0')
            i++;
        p->Bname[i] = '\0';
        int price = p->qty*p->price;
        printf("%d\t%s\t%d\t%d\n", ++index, p->Bname, p->qty, price);
        total += price;
    }
    printf("-----------------------------\nTOTAL: %d\n", total);
}

void placeOrder(struct node *book_list, struct order *bill){
    int billing = 1;
    bill = NULL;
    while(billing){
        int opt = 0;
        printf("[1] Next Book\t[2] Show Bill\t[3] EXIT\n");
        printf("Choice: ");
        scanf("%d", &opt);
        if(opt == 1){
            struct node *res = search_book(book_list);
            struct order *newItem = malloc(sizeof(struct order));
            printf("Enter Quantity: ");
            scanf("%d", &newItem->qty);
            if(bill == NULL)
                newItem->next1 = NULL;
            else{
                newItem->next1 = bill;
                bill->prev1 = newItem;
            }
            newItem->prev1 = NULL;
            bill = newItem;
            strcpy(newItem->Bname, res->Bname);
            newItem->price = res->price;
            printf("Item Added!!\n");
            // For debug
            showBill(bill);
        }
        else if(opt == 2)
            showBill(bill);
        else if(opt == 3)
            billing = 0;
        else
            printf("Invalid Option!!\n");
    }
}


//function to generate the bill and display it on the screen
void generate_bill(struct order *header1)
{
    struct order *temp = header1;
    int j, i = 1, Total = 0;
    if (temp == NULL)
    {
        printf("\nNo book is ordered :(");
    }
    else
    {
        printf("--------------------------------------------\n");
        printf("-------------------BILL---------------------\n");
        printf("sl no\tBook Name\tQuantity\tPrice\n");
        while (temp != NULL)
        {
            printf("%d\t", i);
            for (j = 0; temp->Bname[j] != '\n'; j++)
            {
                printf("%c", temp->Bname[j]);
            }
            printf("\t");
            printf("\t%d", temp->qty);
            printf("\t%d\n", temp->price);
            Total = Total + temp->price;
            temp = temp->next1;
            i++;
        }
        printf("--------------------------------------------\n");
        printf("                           TOTAL : %d\n", Total);
        printf("--------------------------------------------\n");
    }
}
//sample function to display the books purchased
void display_order(struct order *header1)
{
    int j, i = 1;
    struct order *ptr1 = header1;
    if (ptr1 == NULL)
    {
        printf("\nOops , no books are purchased yet!1\n");
    }
    else
    {
        printf("-----------------------------------\n");
        printf("-----------------------------------\n");
        printf("Sl.No.\tBook Name\tPrice\n");
        while (ptr1 != NULL)
        {
            printf("%d\t", i);

            for (j = 0; ptr1->Bname[j] != '\n'; j++)
            {
                printf("%c", ptr1->Bname[j]);
            }
            printf("\t");
            printf("\t%d\n", ptr1->price);
            ptr1 = ptr1->next1;
            i++;
        }
        printf("-----------------------------------\n");
        printf("-----------------------------------\n");
    }
}

// //function to display the Book Menu

void display_menu(struct node *header)
{
    //function for viewing the added books
    //SORTING FUNCTION is to be called
    struct node *ptr = header;
    if (ptr == NULL)
    {
        printf("\nSorry currently no books are available at the moment!\n");
    }
    else
    {
        int j, i = 1;
        printf("-----------------------------------\n");
        printf("-----------------------------------\n");
        printf("Sl.No.\tBook Name\tPrice\n");
        while (ptr != NULL)
        {

            printf("%d\t", i);
            for (j = 0; ptr->Bname[j] != '\n'; j++)
            {
                printf("%c", ptr->Bname[j]);
            }
            printf("\t");
            printf("\t%d\n", ptr->price);
            ptr = ptr->next;
            i++;
        }
        printf("-----------------------------------\n");
        printf("-----------------------------------\n");
    }
}

/////////////////////////////////////////////ADMIN FUNCTION STARTS//////////////////////////////////////////////////
struct node *add_Book(struct node *header)
{
    //function for adding new books
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    struct node *ptr = header;
    newnode->next = NULL;
    printf("Enter the name of the book: ");
    fgetc(stdin);
    fgets(newnode->Bname, 200, stdin);
    printf("Enter the unit price of the book: ");
    scanf("%d", &newnode->price);
    fgetc(stdin);
    if (ptr == NULL)
    {
        newnode->prev = NULL;
        newnode->next = NULL;
        header = newnode;
    }
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        newnode->prev = ptr;
        ptr->next = newnode;
        newnode->next=NULL;               
    }
    counter++;
    return header;
}

struct node *autoAddBook(struct node *header, char *name, int price)
{
    //function for adding new books
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    struct node *ptr = header;
    newnode->next = NULL;
    newnode->Bname[0] = '\0';
    strcpy(newnode->Bname, name);
    newnode->price = price;
    if (ptr == NULL)
    {
        newnode->prev = NULL;
        newnode->next = NULL;
        header = newnode;
    }
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        newnode->prev = ptr;
        ptr->next = newnode;
        newnode->next=NULL;               
    }
    counter++;
    return header;
}

//function to delete the books
struct node *delete_Book(struct node *header)
{
    struct node *ptr = header;
    int k, i = 1;
    if (ptr == NULL)
    {
        printf("\nNo books are available in the list to delete!\n");
    }
    else
    {
        display_menu(header);
        printf("Enter the Book Index to delete: ");
        scanf("%d", &k);
        while (ptr != NULL)
        {
            if (i == k)
            {
                break;
            }
            i = i + 1;
            ptr = ptr->next;
        }
        if (ptr == NULL)
        {
            printf("\nEntered index out of bound!\n");
        }
        else
        {
            if (ptr->next == NULL)
            {
                if (ptr->prev == NULL)
                {
                    header = ptr->next;
                    //free(ptr);
                }
                else
                {
                    ptr->prev->next = NULL;
                    //free(ptr);
                }
                //dis[play]
            }
            else if (ptr == header)
            {
                ptr->next->prev = NULL;
                header = ptr->next;
                //free(ptr);
            }
            else
            {
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
                //free(ptr);
            }
            printf("\n           *.Book Menu is Updated.*           \n");
            display_menu(header);
        }
    }
    return header;
}

/////////////////////////////////////////////ADMIN FUNCTION ENDS///////////////////////////////////////////////////

////////////////////////////////////////CUSTOMER FUNCTION STARTS///////////////////////////////////////////////////
struct order *searchNode(struct node *header, struct order *header1, int num)
{
    int i = 1, flag = 0, Qty;
    struct node *ptr = header;
    struct order *ptr1 = header1;
    struct order *new1 = (struct order *)malloc(sizeof(struct order));
    new1->next1 = NULL;
    while (ptr != NULL)
    {
        if (i == num)
        {
            printf("Enter the quantity of books to be purchased %d : ", num);
            scanf("%d", &Qty);

            strcpy(new1->Bname, ptr->Bname);

            new1->price = (ptr->price) * Qty;
            new1->qty = Qty;
            flag = 1;
            break;
        }
        ptr = ptr->next;
        i++;
    }
    if (flag == 1)
    {
        if (ptr1 == NULL)
        {
            header1 = new1;
        }
        else
        {
            while (ptr1->next1 != NULL)
            {
                ptr1 = ptr1->next1;
            }
            new1->prev1 = ptr1;
            ptr1->next1 = new1;
        }
        printf("Order has been placed successfully\n");
    }
    else
    {
        printf("\nBook with the entered index number is not present!\n");
    }
    return header1;
}
/**
* @deprecated
*/
struct order *place_Order(struct node *header, struct order *header1)
{

    int i = 1, index;
    struct node *ptr = header;
    if (ptr == NULL)
    {
        printf("\nBooks are unavailable to be ordered!!\n");
 
    }
    else
    {
        //display_menu(header);
        printf("\nPLACE THE ORDER \n\n  Enter the index:-\n   (I)'0' to view the book menu\n   (II)book index to place your order\n   (III)'-1' to finish your purchasing\n");
        while (1)
        {
            printf("\nEnter the index : ");
            scanf("%d", &index);
            if (index == 0)
                display_menu(header);
            else if (index == -1)
            {
                if (i == 1)
                {
                    printf("\nOrder Cart is empty");
                }
                else
                {
                    printf("Order has been placed successfully..\n");
                    break;
                }
            }
            else
            {
                struct node *ret = search_book(header);
                if(ret != NULL)
                    printf("Got book: %s of price %d\n", ret->Bname, ret->price);
                i++;
            }
        }
    }
    display_order(header1);
    return header1;
}

/////////////////////////////CUSTOMER FUNCTION ENDS//////////////////////////////////////////

//--------------function detailing about the admin section...............
struct node *admin(struct node *header)
{
    int option, flag = 0;
    while (flag == 0)
    {
        printf("\nChoose an option:\n1.Display BOOK MENU\n2.Add a new book\n3.Delete a book\n4.Sign Out\n\n  Option: _");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            display_menu(header);
            break;
        case 2:
            header = add_Book(header);
            break;
        case 3:
            header = delete_Book(header);
            break;
        case 4:
            flag = 1;
            break;
        default:
            printf("\nEnter a valid option!\n");
            break;
        }
    }
    return header;
}

//................................function detailing about the customer section.........................
struct order *customer(struct node *header, struct order *header1)
{
    int option, flag = 0;
    while (flag == 0)
    {
        printf("\nChoose an option:\n  1.Display the BOOK MENU\n  2.Place my order.\n  3.Generate the bill\n  4.Sign out\n\n  Option: ");
        scanf("%d", &option);
        struct node *res;
        switch (option)
        {
        case 1:
            display_menu(header);
            break;
        case 2:
            // header1 = placeOrder(header, header1);
            placeOrder(header, header1);
            break;
        case 3:
            generate_bill(header1);
            break;
        case 4:
            flag = 1;
            break;
        default:
            printf("invalid choice!\n");
            break;
        }
    }
    return header1;
}

//function to check the login credentials of the admin
int is_admin()
{
    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter the password: ");
    scanf("%s", password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//function to check the login credential of the customer
int is_customer()
{
    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter the password: ");
    scanf("%s", password);
    if (strcmp(username, "reader") == 0 && strcmp(password, "reader") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//main function
int main()
{
    int option, flag = 0;
    while (flag == 0)
    {
        printf("\n1 Log in as the admin.\n2 Log in as a customer.\n3 Exit\n");
        printf("Choose your option: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("\nAdmin\n");
            if (is_admin())
            {
                printf("\nSuccesfully Signed in as the admin!\n");
                header = admin(header);
            }
            else
            {
                printf("\nInvalid username/password for admin!\n");
            }
            break;
        case 2:
            printf("\nUser\n");
            if (is_customer())
            {
                printf("\nSuccesfully Signed in as a customer!\n");
                header1 = customer(header, header1);
            }
            else
            {
                printf("\nInvalid username/password for customer!\n");
            }
            break;
        case 3:
            flag = 1;
            break;
        default:
            printf("\nError: Invalid option.\n");
            break;
        }
    }
}