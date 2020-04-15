#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define c 4

struct showroom 
{
	struct salesman *man;
	struct stocks *stock_details;
}s[3];

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
//	int reg_num;
//	char payment;
	float amount_per_month;
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

void preOrder(struct stocks *);
struct customer *insert_customer(int,struct customer * ,char *, char *,char *, float);


struct stocks *search_car(int ,struct stocks *);

struct salesman *search_salesman(int key,struct salesman *man)
{
	if(man!=NULL)
	{
		if(key>man->man.Id)
		{
			man=search_salesman(key,man->right);
		}
		else if (key<man->man.Id)
		{
			man=search_salesman(key,man->left);
		}
	}
	return man;

}


struct showroom sell(int k,struct salesman *sales,struct stocks *car)
{
	int flag=1;
	struct salesman *man;
	struct stocks *temp_car;
	temp_car=car;
	man=sales;

	//printf("%d %d \n",car->height,car->car.VIN );
	//printf("%d %d \n",temp_car->height,temp_car->car.VIN );
	                       
	struct showroom s;
	while(flag==1)
	{
		man=search_salesman(k,man);
	//	printf("%d %d\n",temp_car->height,temp_car->car.VIN );
	                       
	//	printf("%d\n",man->height );
		if(man==NULL)
			printf("Wrong Id Entered\n");
		else
		{
			temp_car=car;
		//	printf("%d %d\n",temp_car->height,temp_car->car.VIN );
	                       
			preOrder(temp_car);
			//printf("%d %d\n",temp_car->height,temp_car->car.VIN );
	                       
			printf("Enter the VIN number of the car u want to buy\n");
			int temp_vin;
			scanf("%d",&temp_vin);
			//printf("%d %d\n",temp_car->height,temp_car->car.VIN );
	                       
			temp_car=search_car(temp_vin,temp_car);
			//printf("%d %d\n",temp_car->height,temp_car->car.VIN );
			if(temp_car==NULL)
			{
				printf("Car is not available with this VIN number\n" );
			}
			else
			{
				printf("Found the car\n");
					char name[30],Mob[10],address[50];
					int choice,loan_option;
					float monthly_payment;
					printf("The car is available pls Enter the following for billing\n");
					printf("Enter Your Name:");
					scanf("%s",name);

					printf("Enter your Mob number without any code or 0:" );
					scanf("%s",Mob);
					printf("\nEnter your Address:");
					scanf("%s",address);
					printf("Now choose any your payment option \n1.Full Payment 2.Loan\n");
					scanf("%d",&choice);
					if(choice==1)
					{
						man->man.customer_list=insert_customer(temp_vin,man->man.customer_list,name,Mob,address,0);
					}
					else if (choice==2)
					{
						printf("\nHere are the different options for Loan");
						printf("\n1  9.00 percent rate of interest for 84 months EMI");
						printf("\n2  8.75 percent rate of interest for 60 months EMI");
						printf("\n3  8.50 percent rate of interest for 36 months EMI\n");
						scanf("%d",&loan_option);
						if(loan_option==1)
						{
							monthly_payment=(float)((temp_car->car.price/84)+(temp_car->car.price*(0.09)));
						}
						else if (loan_option==2)
						{
							monthly_payment=(float)((temp_car->car.price/60)+(temp_car->car.price*(0.0875)));
						}
						else if (loan_option==3)
						{
							monthly_payment=(float)((temp_car->car.price/36)+(temp_car->car.price*(0.085)));
						}
						printf("%f\n",monthly_payment);
						man->man.customer_list=insert_customer(temp_vin,man->man.customer_list,name,Mob,address,monthly_payment);
					}
					if (man->man.customer_list!=NULL)
					{
						temp_car->car.status=0;
						printf("\nData is successfully updated and the car is yours now\n");
						flag=0;
						man->man.num_of_cars_sold++;
						man->man.sales_achieved=temp_car->car.price;
					}
			}
		}
	}
	s.stock_details=car;
	s.man=sales;	
	return s;
}