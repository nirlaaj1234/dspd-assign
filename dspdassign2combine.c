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
//	int reg_num;
//	char payment;
	int amount_per_month;
    float interest_percentage;
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
	float sales_commission;
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

int height(struct stocks *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

struct salesman* insert_salesman(struct salesman* , int  , char *); 
  
/* Helper function that allocates a new node with the given key and 
    NULL left and right pointers. */
struct stocks* newNode(int key,char name[] ,char colour[] ,long int price , char Fuel[] ,char type[]) 
{ 
    struct stocks* node = (struct stocks*) 
                        malloc(sizeof(struct stocks)); 
    node->car.VIN   = key;
    strcpy(node->car.car_name,name);
    strcpy(node->car.color,colour);
    node->car.price=price;
    strcpy(node->car.Fuel,Fuel);
    strcpy(node->car.type,type);
    node->car.status=1;
    node->left=NULL;
    node->right=NULL;
   /* int fuel;
    printf("Enter the data car_name, colour, price, fuel type(0.petrol 1.diesel 2.electric 3.CNG), type, available cars.\n  ");
    scanf("%s%s%li%d%s%d",node->car.car_name,node->car.color,&(node->car.price),&fuel,node->car.type,&(node->car.avail_cars)); 
    node->left   = NULL; 
    node->right  = NULL;
    struct stocks *temp_car;
    temp_car=car;
    man=sales;
    while(flag==1)
    {
        man=search_salesman(k,man);
        if(man==NULL)
            printf("Wrong Id Entered\n");
        else
        {
    node->car.sold_cars=0; 
    if(fuel==0){
    node->car.Fuel="Petrol";
    }
    else if (fuel==1)
    {
     node->car.Fuel="Diesel";   // code 
    }Diesel";   // code 
    }
    else if (fuel==2)
    {
        node->car.Fue
    else if (fuel==2)
    {
        node->car.Fuel="Electric";
    }
    else if (fuel==3)
    {
        node->car.Fuel="CNG";
    }
    */
    node->height = 1;  // new node is initially added at leaf 
    return(node); 
} 
  
// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct stocks *rightRotate(struct stocks *y) 
{ 
    struct stocks *x = y->left; 
    struct stocks *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
  
    // Return new root 
    return x; 
} 
  
// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct stocks *leftRotate(struct stocks *x) 
{ 
    struct stocks *y = x->right; 
    struct stocks *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    //  Update heights 
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    // Return new root 
    return y; 
} 
  
// Get Balance factor of node N 
int getBalance(struct stocks *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
  
// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
struct stocks* insert(struct stocks* node, int key ,char name[] ,char colour[] ,long int price , char Fuel[] ,char type[] ) 
{ 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
    {
 
        return(newNode(key,name,colour,price,Fuel,type)); 
    }	
    if (key < node->car.VIN) 
        node->left  = insert(node->left, key,name,colour,price,Fuel,type); 
    else if (key > node->car.VIN) 
        node->right = insert(node->right, key,name,colour,price,Fuel,type); 
    else // Equal keys are not allowed in BST 
	{
	printf("VIN Already exist\n");
        return node; 
	}
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), 
                           height(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && key < node->left->car.VIN) 
        return rightRotate(node); 
  
    // Right Right Case 
    if (balance < -1 && key > node->right->car.VIN) 
        return leftRotate(node); 
  
    // Left Right Case 
    if (balance > 1 && key > node->left->car.VIN) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && key < node->right->car.VIN) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
} 
void preOrder(struct stocks *root) 
{ 
    if(root != NULL) 
    { 
        preOrder(root->left); 
	   printf("%d ", root->car.VIN);
	   printf("%s ",root->car.car_name);
	   printf("%s ",root->car.color);
	   printf("%li ",root->car.price);
	   printf("%s ",root->car.type);
	   printf("%s",root->car.Fuel);
       if(root->car.status==1)
        printf("\tAvailable in stocks\n" );
        else
        printf("\tSold will be Available Soon\n" );
        preOrder(root->right);   
    } 
} 

struct stocks *search_car(int key,struct stocks *cars)
{
    if(cars!=NULL)
    {
        //printf("%d \t",cars->car.VIN);
        //printf("%d",key);
        if(key > cars->car.VIN)
        {
            cars=search_car(key,cars->right);
        }
        else if (key < cars->car.VIN)
        {
            cars=search_car(key,cars->left);
        }
    }
    if(cars!=NULL && cars->car.status==1)
    return cars;
    else 
        return NULL;

}

struct showroom CreateStockTree1(struct stocks *root,struct salesman *root1)
{
    root = insert(root,1,"Maruti Suzuki Swift","red",519000,"Petrol","HatckBack");
    root = insert(root,2,"Maruti Suzuki Swift","blue",519000,"Petrol","HatckBack");
    root = insert(root,3,"Maruti Suzuki Swift","yellow",519000,"Petrol","HatckBack");
    root = insert(root,21,"Maruti Suzuki Baleno","blue",570000,"Petrol","HatchBack");
    root = insert(root,22,"Maruti Suzuki Baleno","grey",570000,"Petrol","HatchBack");
    root = insert(root,23,"Maruti Suzuki Baleno","red",570000,"Petrol","HatchBack");
    root = insert(root,41,"TATA Tiago","blue",460000,"Petrol","HatchBack");
    root = insert(root,42,"TATA Tiago","yellow",460000,"Petrol","HatchBack");
    root = insert(root,43,"TATA Tiago","grey",460000,"Petrol","HatchBack");
    root = insert(root,61,"Maruti Suzuki Dzire","grey",600000,"Petrol","Sedan");
    root = insert(root,62,"Maruti Suzuki Dzire","black",600000,"Petrol","Sedan");
    root = insert(root,63,"Maruti Suzuki Dzire","blue",600000,"Petrol","Sedan");
    root = insert(root,81,"Honda Amaze","red",712000,"Petrol","Sedan");
    root = insert(root,82,"Honda Amaze","blue",712000,"Petrol","Sedan");
    root = insert(root,83,"Honda Amaze","grey",712000,"Petrol","Sedan");
    root = insert(root,101,"Ford Aspire","grey",625000,"Petrol","Sedan");
    root = insert(root,102,"Ford Aspire","black",625000,"Petrol","Sedan");
    root = insert(root,103,"Ford Aspire","red",625000,"Petrol","Sedan");
    root = insert(root,121,"Hyundai Creta","white",1100000,"Diesel","SUV");
    root = insert(root,122,"Hyundai Creta","black",1100000,"Diesel","SUV");
    root = insert(root,123,"Hyundai Creta","grey",1100000,"Diesel","SUV");
    root = insert(root,141,"KIA Seltos","black",1054000,"Diesel","SUV");
    root = insert(root,142,"KIA Seltos","skyblue",1054000,"Diesel","SUV");
    root = insert(root,143,"KIA Seltos","white",1054000,"Diesel","SUV");
    root = insert(root,161,"Mahindra Scorpio","white",1246000,"Diesel","SUV");
    root = insert(root,162,"Mahindra Scorpio","black",1246000,"Diesel","SUV");
    root = insert(root,163,"Mahindra Scorpio","grey",1246000,"Diesel","SUV");
    root1 = insert_salesman(root1,1,"Abhilash");
    root1 = insert_salesman(root1,2,"Ramesh");
    root1 = insert_salesman(root1,3,"Vicky");
    struct  showroom s1;
    s1.man=root1;
    s1.stock_details=root;
    return s1;
}
struct showroom CreateStockTree2(struct stocks *root,struct salesman *root1)
{    
    root = insert(root,4,"Maruti Suzuki Swift","red",519000,"Petrol","HatckBack");
    root = insert(root,5,"Maruti Suzuki Swift","blue",519000,"Petrol","HatckBack");
    root = insert(root,6,"Maruti Suzuki Swift","yellow",519000,"Petrol","HatckBack");
    root = insert(root,24,"Maruti Suzuki Baleno","blue",570000,"Petrol","HatchBack");
    root = insert(root,25,"Maruti Suzuki Baleno","grey",570000,"Petrol","HatchBack");
    root = insert(root,26,"Maruti Suzuki Baleno","red",570000,"Petrol","HatchBack");
    root = insert(root,44,"TATA Tiago","blue",460000,"Petrol","HatchBack");
    root = insert(root,45,"TATA Tiago","yellow",460000,"Petrol","HatchBack");
    root = insert(root,46,"TATA Tiago","grey",460000,"Petrol","HatchBack");
    root = insert(root,64,"Maruti Suzuki Dzire","grey",600000,"Petrol","Sedan");
    root = insert(root,65,"Maruti Suzuki Dzire","black",600000,"Petrol","Sedan");
    root = insert(root,66,"Maruti Suzuki Dzire","blue",600000,"Petrol","Sedan");
    root = insert(root,84,"Honda Amaze","red",712000,"Petrol","Sedan");
    root = insert(root,85,"Honda Amaze","blue",712000,"Petrol","Sedan");
    root = insert(root,86,"Honda Amaze","grey",712000,"Petrol","Sedan");
    root = insert(root,104,"Ford Aspire","grey",625000,"Petrol","Sedan");
    root = insert(root,105,"Ford Aspire","black",625000,"Petrol","Sedan");
    root = insert(root,106,"Ford Aspire","red",625000,"Petrol","Sedan");
    root = insert(root,124,"Hyundai Creta","white",1100000,"Diesel","SUV");
    root = insert(root,125,"Hyundai Creta","black",1100000,"Diesel","SUV");
    root = insert(root,126,"Hyundai Creta","grey",1100000,"Diesel","SUV");
    root = insert(root,144,"KIA Seltos","black",1054000,"Diesel","SUV");
    root = insert(root,145,"KIA Seltos","skyblue",1054000,"Diesel","SUV");
    root = insert(root,146,"KIA Seltos","white",1054000,"Diesel","SUV");
    root = insert(root,164,"Mahindra Scorpio","white",1246000,"Diesel","SUV");
    root = insert(root,165,"Mahindra Scorpio","black",1246000,"Diesel","SUV");
    root = insert(root,166,"Mahindra Scorpio","grey",1246000,"Diesel","SUV");
    root1 = insert_salesman(root1,1,"Yash");
    root1 = insert_salesman(root1,2,"Purvesh");
    root1 = insert_salesman(root1,3,"Rashmi");
    struct  showroom s1;
    s1.man=root1;
    s1.stock_details=root;
    return s1;
}
struct showroom CreateStockTree3(struct stocks *root,struct salesman *root1)
{
    root = insert(root,7,"Maruti Suzuki Swift","red",519000,"Petrol","HatckBack");
    root = insert(root,8,"Maruti Suzuki Swift","blue",519000,"Petrol","HatckBack");
    root = insert(root,9,"Maruti Suzuki Swift","yellow",519000,"Petrol","HatckBack");
    root = insert(root,27,"Maruti Suzuki Baleno","blue",570000,"Petrol","HatchBack");
    root = insert(root,28,"Maruti Suzuki Baleno","grey",570000,"Petrol","HatchBack");
    root = insert(root,29,"Maruti Suzuki Baleno","red",570000,"Petrol","HatchBack");
    root = insert(root,47,"TATA Tiago","blue",460000,"Petrol","HatchBack");
    root = insert(root,48,"TATA Tiago","yellow",460000,"Petrol","HatchBack");
    root = insert(root,49,"TATA Tiago","grey",460000,"Petrol","HatchBack");
    root = insert(root,67,"Maruti Suzuki Dzire","grey",600000,"Petrol","Sedan");
    root = insert(root,68,"Maruti Suzuki Dzire","black",600000,"Petrol","Sedan");
    root = insert(root,69,"Maruti Suzuki Dzire","blue",600000,"Petrol","Sedan");
    root = insert(root,87,"Honda Amaze","red",712000,"Petrol","Sedan");
    root = insert(root,88,"Honda Amaze","blue",712000,"Petrol","Sedan");
    root = insert(root,89,"Honda Amaze","grey",712000,"Petrol","Sedan");
    root = insert(root,107,"Ford Aspire","grey",625000,"Petrol","Sedan");
    root = insert(root,108,"Ford Aspire","black",625000,"Petrol","Sedan");
    root = insert(root,109,"Ford Aspire","red",625000,"Petrol","Sedan");
    root = insert(root,127,"Hyundai Creta","white",1100000,"Diesel","SUV");
    root = insert(root,128,"Hyundai Creta","black",1100000,"Diesel","SUV");
    root = insert(root,129,"Hyundai Creta","grey",1100000,"Diesel","SUV");
    root = insert(root,147,"KIA Seltos","black",1054000,"Diesel","SUV");
    root = insert(root,148,"KIA Seltos","skyblue",1054000,"Diesel","SUV");
    root = insert(root,149,"KIA Seltos","white",1054000,"Diesel","SUV");
    root = insert(root,167,"Mahindra Scorpio","white",1246000,"Diesel","SUV");
    root = insert(root,168,"Mahindra Scorpio","black",1246000,"Diesel","SUV");
    root = insert(root,169,"Mahindra Scorpio","grey",1246000,"Diesel","SUV");
    root1 = insert_salesman(root1,1,"Monica");
    root1 = insert_salesman(root1,2,"Kailash");
    root1 = insert_salesman(root1,3,"Sameer");
    struct  showroom s1;
    s1.man=root1;
    s1.stock_details=root;
    return s1;
}

int height_salesman(struct salesman *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
// A utility function to get maximum of two integers 

  
/* Helper function that allocates a new node with the given key and 
    NULL left and right pointers. */
struct salesman* newNode_man(int key,char name[]) 
{ 
    struct salesman* node = (struct salesman*) 
                        malloc(sizeof(struct salesman)); 
    node->man.Id   = key;
    strcpy(node->man.name,name); 
    node->left   = NULL; 
    node->right  = NULL;
    node->man.num_of_cars_sold=0; 
    node->man.sales_achieved=0;
    node->man.sales_commission=0;
    
    node->height = 1;  // new node is initially added at leaf 
    return(node); 
} 
  
// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct salesman *rightRotate_man(struct salesman *y) 
{ 
    struct salesman *x = y->left; 
    struct salesman *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
    y->height = max(height_salesman(y->left), height_salesman(y->right))+1; 
    x->height = max(height_salesman(x->left), height_salesman(x->right))+1; 
  
    // Return new root 
    return x; 
} 
  
// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct salesman *leftRotate_man(struct salesman *x) 
{ 
    struct salesman *y = x->right; 
    struct salesman *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    //  Update heights 
    x->height = max(height_salesman(x->left), height_salesman(x->right))+1; 
    y->height = max(height_salesman(y->left), height_salesman(y->right))+1; 
  
    // Return new root 
    return y; 
} 
  
// Get Balance factor of node N 
int getBalance_man(struct salesman *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height_salesman(N->left) - height_salesman(N->right); 
} 
  
// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
struct salesman* insert_salesman(struct salesman* node, int key,char name[]) 
{ 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
    {
 
        return(newNode_man(key,name)); 
    }	
    if (key < node->man.Id) 
        node->left  = insert_salesman(node->left, key,name); 
    else if (key > node->man.Id) 
        node->right = insert_salesman(node->right, key,name); 
    else // Equal keys are not allowed in BST 
	{
	printf("VIN Already exist\n");
        return node; 
	}
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height_salesman(node->left), 
                           height_salesman(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance_man(node); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && key < node->left->man.Id) 
        return rightRotate_man(node); 
  
    // Right Right Case 
    if (balance < -1 && key > node->right->man.Id) 
        return leftRotate_man(node); 
  
    // Left Right Case 
    if (balance > 1 && key > node->left->man.Id) 
    { 
        node->left =  leftRotate_man(node->left); 
        return rightRotate_man(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && key < node->right->man.Id) 
    { 
        node->right = rightRotate_man(node->right); 
        return leftRotate_man(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
}
void preOrder_salesman(struct salesman *root) 
{ 
    if(root != NULL) 
    { 
        preOrder_salesman(root->left); 
       printf("%d ", root->man.Id);
       printf("%s ",root->man.name);
        preOrder_salesman(root->right);   
    } 
} 


int height_customer(struct customer *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
// A utility function to get maximum of two integers 

  
/* Helper function that allocates a new node with the given key and 
    NULL left and right pointers. */
struct customer* newNode_customer(int key,char name[],char Mob[],char address[],float month ,float percent) 
{ 
    struct customer* node = (struct customer*) 
                        malloc(sizeof(struct customer)); 
    node->customers.VIN  = key;
    strcpy(node->customers.name,name); 
    strcpy(node->customers.Mob,Mob);
    strcpy(node->customers.address,address);
    node->customers.amount_per_month=month;
    node->customers.interest_percentage=percent;
    node->left   = NULL; 
    node->right  = NULL;
    
    node->height = 1;  // new node is initially added at leaf 
    return(node); 
} 
  
// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct customer *rightRotate_customer(struct customer *y) 
{ 
    struct customer *x = y->left; 
    struct customer *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
    y->height = max(height_customer(y->left), height_customer(y->right))+1; 
    x->height = max(height_customer(x->left), height_customer(x->right))+1; 
  
    // Return new root 
    return x; 
} 
  
// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct customer *leftRotate_customer(struct customer *x) 
{ 
    struct customer *y = x->right; 
    struct customer *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    //  Update heights 
    x->height = max(height_customer(x->left), height_customer(x->right))+1; 
    y->height = max(height_customer(y->left), height_customer(y->right))+1; 
  
    // Return new root 
    return y; 
} 
  
// Get Balance factor of node N 
int getBalance_customer(struct customer *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height_customer(N->left) - height_customer(N->right); 
} 
  
// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
struct customer* insert_customer(int key,struct customer* node, char name[],char Mob[],char address[],float month , float percent) 
{ 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
    {
 
        return(newNode_customer(key,name,Mob,address,month,percent)); 
    }   
    if (key < node->customers.VIN) 
        node->left  = insert_customer(key,node->left, name,Mob,address,month,percent); 
    else if (key > node->customers.VIN) 
        node->right = insert_customer(key,node->right,name,Mob,address,month,percent); 
    else // Equal keys are not allowed in BST 
    {
    printf("VIN Already exist\n");
        return node; 
    }
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height_customer(node->left), 
                           height_customer(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance_customer(node); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && key < node->left->customers.VIN) 
        return rightRotate_customer(node); 
  
    // Right Right Case 
    if (balance < -1 && key > node->right->customers.VIN) 
        return leftRotate_customer(node); 
  
    // Left Right Case 
    if (balance > 1 && key > node->left->customers.VIN) 
    { 
        node->left =  leftRotate_customer(node->left); 
        return rightRotate_customer(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && key < node->right->customers.VIN) 
    { 
        node->right = rightRotate_customer(node->right); 
        return leftRotate_customer(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
}
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
                    float percent;
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
						man->man.customer_list=insert_customer(temp_vin,man->man.customer_list,name,Mob,address,0,0.0);
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
							monthly_payment=(float)((temp_car->car.price/84)+((temp_car->car.price*(0.09))/12));
                            percent=9;
						}
						else if (loan_option==2)
						{
							monthly_payment=(float)((temp_car->car.price/60)+((temp_car->car.price*(0.0875))/12));
                            percent=8.75;
						}
						else if (loan_option==3)
						{
							monthly_payment=(float)((temp_car->car.price/36)+(temp_car->car.price*((0.085)))/12);
                            percent=8.5;
						}
						printf("%f\n",monthly_payment);
						man->man.customer_list=insert_customer(temp_vin,man->man.customer_list,name,Mob,address,monthly_payment,percent);
					}
					if (man->man.customer_list!=NULL)
					{
						temp_car->car.status=0;
						printf("\nData is successfully updated and the car is yours now\n");
						flag=0;
						man->man.num_of_cars_sold++;
						man->man.sales_achieved=temp_car->car.price;
						man->man.sales_commission=((temp_car->car.price)*0.02);
					}
			}
		}
	}
	s.stock_details=car;
	s.man=sales;	
	return s;
}
int countsoldcar(struct stocks *car_stock,int vin)
{
    int diff=0;
    int count=0;
    if(car_stock!=NULL)
    {
        if(vin>car_stock->car.VIN+10)
        {
            count+=countsoldcar(car_stock->right,vin);
        }
        else if(vin<car_stock->car.VIN-10)
        {
            count+=countsoldcar(car_stock->left,vin);
        }
        else
        {
            if (car_stock->car.status==0)
            {
                count=1;
            }
            else
            {
                count+=countsoldcar(car_stock->left,vin);
                count+=countsoldcar(car_stock->right,vin);
            }
        }
    }
        return count;
}
Car_Details PopularCar(struct showroom p[])
{
	int count[9][2];
	int vin=1,i=0;
	int j;
	while(i<9)
	{
		count[i][0]=vin;
		count[i][1]+=countsoldcar(p[0].stock_details,vin);
		count[i][1]+=countsoldcar(p[1].stock_details,vin);
		count[i][1]+=countsoldcar(p[2].stock_details,vin);
        if(count[i][1]>0)
            printf("Done %d\n",vin );
		i++;
		vin=vin+20;
	}
	int max=0;
	i=0;
	while(i<9)
	{
		if(count[i][1]>max)
		{
			max=count[i][1];
			j=i;
		}
		i++;
	}
    if (max>0)
    {
        /* code */  struct stocks *stock;
        stock=search_car(count[j][0],p[0].stock_details);
        printf("%d\t%s\n",stock->car.VIN,stock->car.car_name);
        return stock->car;
    }
    else
    {
       Car_Details carz;
       carz.VIN=5000;
       return carz; 
    }



}

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
	printf("Creation of B tree\n");
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
	        printf("4.Most Popular car in all 3 showroom\n");	        
	        printf("5.Most Successfull salesman in all showroom \n");	        
	        printf("6.Display of Car details through VIN number\n");	        
	        printf("7.Display Range of Cars \n");
	        printf("8.quit program\n");
	        scanf("%d",&choice1);
	        if(choice1==4)
	        {
	        	Car_Details car1;
	        	car1=PopularCar(s);
                if(car1.VIN>0 && car1.VIN<200)
	        	      printf("%d\t%s\t%li\t%s\t%s\t%s\n",car1.VIN,car1.car_name,car1.price,car1.color,car1.Fuel,car1.type);
                else 
                    printf("Can't be said for a single car\n");
	        	flag2=0;
	        }
	        else if (choice1==5)
	        {


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
	                        //printf("%d %d\n",s[choice1-1].stock_details->height,s[choice1-1].stock_details->car.VIN );
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