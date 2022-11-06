#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct items
{
	char itemname[20];
	float price;
	int qty;
};
 
struct order
{
	char name[50];
	char date[20];
	int intemsno;
	struct items itm[20];
};

void header(char name [50], char date[20])
{
	printf("\n\n");
	printf("\t   KBG Restaurent\n");
	printf("\t--------------------\n");
	printf("Date: %s\n",date);
	printf("Invoice To: %s\n", name);
	printf("------------------------------------------\n");
	printf("Items");
	printf("\t\tQty");
	printf("\t\tTotal\n");
	printf("------------------------------------------\n\n");

}

void Body(char itemname[20], float price, int qty)
{
	printf("%s\t\t", itemname);
	printf("%d\t\t", qty);
	printf("%0.2f\n", qty*price);
}

void footer(float total)
{
	printf("------------------------------------------\n");
	printf("sub total\t\t\t%0.2f", total);
	float Discount = 0.1*total;
	printf("\nDiscount @10%\t\t\t%0.2f", Discount);
	printf("\n\t\t\t\t---------- ");
	float nettotal = total - Discount;
	printf("\nNet Total\t\t\t%0.2f", nettotal);
	float cgst = (0.09*nettotal);
	printf("\nCGST @9%\t\t\t\t%0.2f", cgst);
	printf("\nSGST @9%\t\t\t\t%0.2f", cgst);
	printf("\n------------------------------------------");
	float Grandtotal = (cgst*2)+nettotal;
	printf("\nGrand Total\t\t\t%0.2f", Grandtotal);
	printf("\n------------------------------------------");

}

int main(int argc, char const *argv[])
{
	FILE* fptr;
	int n;
	int opt;
	char name[25];
	char saveBill, flag = 'y';
	struct order ord;
	struct order orders;

while(flag == 'y')
{
	//Dashboard
	int invoicefound = 0;
	float total = 0;
	float rtotal = 0;
	system("cls");
	printf("\n\t======KBG Restaurent======\n\n");
	printf("1.Generate Invoice\n");
	printf("2.Show All Invoices\n");
	printf("3.Search Invoice\n");
	printf("4.Exit\n\n");

	printf("Please select your prefered Operation :\t");
	scanf("%d", &opt);
	printf("\n\n");
	fgetc(stdin);


	switch(opt)
	{
		case 1:
		    system("cls");
			printf("Enter Following Details to Generate Invoice\n\n");
			printf("*Enter name of the customer :\t");
			fgets(ord.name, 50, stdin);
			ord.name[strlen(ord.name) - 1] = 0;
			strcpy(ord.date, __DATE__);
			printf("\n*Number Of items :\t");
			scanf("%d", &n);
			ord.intemsno = n;

			for (int i = 0; i < n; i++)
			{
				fgetc(stdin);
				printf("\n\n");
				printf("Enter item name %d :\t", i + 1);
				fgets(ord.itm[i].itemname, 20, stdin);
				ord.itm[i].itemname[strlen(ord.itm[i].itemname) - 1] = 0; // Explore this line
				printf("Enter the quantity of Item :\t");
				scanf("%d", &ord.itm[i].qty);
				printf("Enter unit price :\t");
				scanf("%f", &ord.itm[i].price);
				total = total + (ord.itm[i].qty * ord.itm[i].price);
	           }

	            header(ord.name, ord.date);

	            for (int i = 0; i < ord.intemsno; i++)
	            {
		         Body(ord.itm[i].itemname, ord.itm[i].price, ord.itm[i].qty);
	            }

	            footer(total);

                //file opening

                printf("\n\nDo you Want to save Invoice[y/n]:");
	            scanf("%s", &saveBill);

	            if (saveBill == 'y')
	            {
	            	fptr = fopen("Bills.txt", "a+"); //file opening

	                fwrite(&ord, sizeof(struct order), 1, fptr);
	                if (fwrite != 0)
	                {
		              printf("\n\nsave succsefully!\n");
	                }
	                else
	               {
		             printf("\n\nerror\n");
	               }
	               fclose(fptr);

	            }
	            else
	            {
	            	printf("\nInvoice Not be saved!\n");
 
	            }

	    break;  

	    case 2:	      
	           system("cls");  	        
	           fptr = fopen("Bills.txt", "r");
	           printf("\n\t ======Your Previous Invoice======\n"); 		          
          
	           while(fread(&orders, sizeof(struct order), 1, fptr))
	           {	    
	           
	           	header(orders.name, orders.date);
	           	for (int i = 0; i < orders.intemsno; i++)
	            {	             	
		         Body(orders.itm[i].itemname, orders.itm[i].price, orders.itm[i].qty);
		         rtotal = total + (orders.itm[i].qty * orders.itm[i].price);
	            }
	            footer(rtotal);
	           }

	           fclose(fptr);

        break;

        case 3:
               system("cls");
               printf("Enter the name of the customer :\t");
               fgets(name, 25, stdin);
               name[strlen(name)-1] = 0;                 
	           fptr = fopen("Bills.txt", "r");
	           printf("\n\t ======Invoice of %s======\n", name); 

	           while(fread(&orders, sizeof(struct order), 1, fptr))
	           {
	           	if (!strcmp(orders.name,name)) // How fuction work
	           	{
	           		header(orders.name, orders.date);
	           	    for (int i = 0; i < orders.intemsno; i++)
	                {
		              Body(orders.itm[i].itemname, orders.itm[i].price, orders.itm[i].qty);
		              rtotal = total + (orders.itm[i].qty * orders.itm[i].price);
	                }
	                footer(rtotal);
	                invoicefound = 1;
	           	}
	           	
	           }
	           if (!invoicefound)
	           {
	           	printf("\n**sorry the Invoice for %s doesnot exists\n",name);
	           }
	           fclose(fptr);

        break;

        case 4:
               printf("\n\t\t Bye Bye :)");
               exit(0);
        break;

        default:
               printf("\t\t**sorry invalid option\n");
        break;       
    }

    printf("\n\nDo you want perform another Operation [y/n] :\t");
    scanf("%s",&flag);

}
   printf("\n\t\t Bye Bye :)");

	return 0;
}