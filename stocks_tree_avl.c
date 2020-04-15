#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define c 4

struct showroom 
{
    struct salesman *man;
    struct stocks *stock_details;
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

typedef struct cars_Details
{
	int VIN;
	char car_name[30];
	char color[10];
	long int price;
	char Fuel[15];
	char type[30];
	int status;
    //int sold_cars;
	//int avail_cars;
}Car_Details;

struct stocks
{
    int height;
	Car_Details car;
	struct stocks *left;
	struct stocks *right;
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
}; 
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