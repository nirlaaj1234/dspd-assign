#include<stdio.h>
#include<stdlib.h>
#define c 4

struct showroom 
{
//	struct salesman *man;
	struct stocks *stock_details;
}s1,s2,s3;

enum Fuel_type { Petrol,Deisel,Electric,CNG };

enum KeyStatus { Duplicate,SearchFailure,Success,InsertIt,LessKeys };

typedef struct cars_Details
{
	int VIN;
	char car_name[30];
	char color[10];
	long int price;
	enum Fuel_type Fuel;
	char type[30];
	int sold_cars;
	int avail_cars;
}Car_Details;

struct customer_details
{
	char name[20];
	char Mob[10];
	char address[50];
	int VIN;
	int reg_num;
	char payment;
	int amount_per_month;
};

struct customer
{
	struct customer_details customers;
	struct customer *next;
	struct customer *prev;
};

typedef struct salesman_details
{
	int Id;
	char name[30];
	int num_of_cars_sold;
	int sales_achieved;
	int sales_commission;
	struct customer *customer_list;
}salesman_detail;

struct salesman
{
	salesman_detail man[c];
	struct salesman *node[c+1];
	struct salesman *parent;
};

struct stocks
{
        int n;
        Car_Details car[c];
	struct stocks *node[c+1];
	struct stocks *parent;
};

struct stocks * insert (int ,struct stocks *);

void display(struct stocks * , int );

void search(int  , struct stocks *);

int main()
{
	int key;
	int choice;
	struct stocks *root;
        root=NULL;
	printf("Creation of B tree for node %d\n",c);
	while(1)
	{
	printf("1.Insert\n");
	printf("2.Search\n");
	printf("3.Display\n");
	printf("4.Quit\n");
	printf("Enter your choice : ");
	scanf("%d",&choice);
	
	switch(choice)
	{
	case 1:
	printf("Enter the key : ");
	scanf("%d",&key);
	root = insert(key,root);
	break;
	case 2:
	printf("Enter the key : ");
	scanf("%d",&key);
	search(key , root);
	break;
	case 3:
	printf("Btree is :\n");
	display(root,0);
	break;
	case 4:
	exit(1);
	default:
	printf("Wrong choice\n");
	break;
	}/*End of switch*/
	}/*End of while*/
	return 0;

}
