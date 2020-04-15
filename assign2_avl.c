#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define c 4

struct showroom 
{
	struct salesman *man;
	struct stocks *stock_details;
}s[3];

enum Fuel_type { Petrol,Deisel,Electric,CNG };


typedef struct cars_Details
{
	int VIN;
	char car_name[30];
	char color[10];
	long int price;
    char Fuel[15];
	char type[30];
	int status;
//	int sold_cars;
//	int avail_cars;
}Car_Details;

struct customer_details
{
	int VIN;
	char name[20];
	char Mob[10];
	char address[50];
	int reg_num;
	char payment;
	int amount_per_month;
};

struct customer
{
	struct customer_details customers;
	struct customer *left;
	struct customer *right;
	int height;
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
	salesman_detail man;
	struct salesman *left;
	struct salesman *right;
	int height;
};

struct stocks
{
    Car_Details car;
	struct stocks *left;
	struct stocks *right;
	int height;
};

struct stocks * insert (struct stocks *,int,char * ,char * ,long int , char * ,char *);

void preOrder(struct stocks *); 

void preOrder_salesman(struct salesman *);

struct salesman* insert_salesman(struct salesman* , int  , char *); 

struct showroom CreateStockTree1(struct stocks *,struct salesman *);
struct showroom CreateStockTree2(struct stocks *,struct salesman *);
struct showroom CreateStockTree3(struct stocks *,struct salesman *);

struct showroom sell(int ,struct salesman * ,struct stocks *);


int main()
{
	int key;
	int choice,flag1,flag2,choice1,choice2,choice3;
        s[0].stock_details=NULL;
        s[0].man=NULL;        
        s[1].stock_details=NULL;
        s[1].man=NULL;        
        s[2].stock_details=NULL;
        s[2].man=NULL;
	printf("Creation of B tree for node %d\n",c);
	flag1=1;
	s[0]=CreateStockTree1(s[0].stock_details,s[0].man);
	s[1]=CreateStockTree2(s[1].stock_details,s[1].man);
	s[2]=CreateStockTree3(s[2].stock_details,s[2].man);
	
	while(flag1==1)
	{
	        flag2=1;
	        printf("1.showroom1 operations\n");
	        printf("2.showroom2 operations\n");
	        printf("3.showroom3 operations\n");
	        printf("4.\n");	        
	        printf("5.copy stocks data of showrooms\n");	        
	        printf("6.Most Popular car of all showrooms\n");	        
	        printf("7.Most Successfull salesman in all showroom \n");
	        printf("8.quit program\n");
	        scanf("%d",&choice1);
	        if(choice1==4)
	        {
	        	printf("Enter the showroom numbers of which data u want to exchange\n" );
	        	scanf("%d%d",&choice2,&choice3);
	        	struct showroom temp;
	        	temp=s[choice2];
	        	s[choice2]=s[choice3];
	        	s[choice3]=temp; 
	       		flag2=0;
	        }
	        else if (choice1==5)
	        {
	        	printf("Enter the 2 showroom numbers, number1 showroom data is copied to number2 showroom\n");
	        	scanf("%d%d",&choice2,&choice3);
	        	s[choice2].stock_details=s[choice3].stock_details;
	        	flag2=0;

	        }
	        else if (choice1==6)
	        {
	        	
	        	flag2=0;
	        }
	        else if (choice1==7)
	        {
	        	/* code */
	        	flag2=0;
	        }
	        else if(choice1==8)
	        {
	                flag2=0;
	                flag1=0;
            }
	        while(flag2==1)
	        {
	                
	                printf("1.Buy a Car \n");
	                printf("2.Insert in salesman tree \n");
	                printf("3.Display cars\n");
	                printf("4.Display salesman\n");	
	                printf("5.Move to Another showroom\n");
	                printf("Enter your choice : ");
	                scanf("%d",&choice);
	                
	                switch(choice)
	                {
	                        case 1:
	                        printf("Salesman in the Showroom are :\n");
	                        preOrder_salesman(s[choice1-1].man);
	                        printf("\n");
	                        printf("Enter the id of salesman from which u want to buy the car : ");
	                        scanf("%d",&key);
	                        s[choice1-1]=sell(key,s[choice1-1].man,s[choice1-1].stock_details);
	                        break;
	                        
	                		case 2:
	                        printf("Enter the id of new salesman : ");
	                        scanf("%d",&key);
	                        char name[30];
	                        printf("Enter salesman name\n");
	                        gets(name);
	                        s[choice1-1].man=insert_salesman(s[choice1-1].man,key,name);
	                        break;
	                        case 3:
	                        printf("Cars in the Showroom are :\n");
	                       // printf("vin\t name \t\t colour price   Tyoe of car  Fuel type\n" );
	                        preOrder(s[choice1-1].stock_details);
	                        printf("\n");
	                        break;
	                        case 4:
                                printf("Salesman in the Showroom are :\n");
	                        preOrder_salesman(s[choice1-1].man);
	                        printf("\n");
	                        break;
	                        case 5:
	                        flag2=0;
	                        break;
	                        default:
	                        printf("Wrong choice\n");
	                        break;
	                }/*End of switch*/
	        }/*End of while*/
	}
	return 0;
}
