#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define c 4

struct customer_details
{
	char name[20];
	char Mob[10];
	char address[50];
	int VIN;
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

int max(int , int ); 

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
struct customer* newNode_customer(int key,char name[],char Mob[],char address[],float month) 
{ 
    struct customer* node = (struct customer*) 
                        malloc(sizeof(struct customer)); 
    node->customers.VIN  = key;
    strcpy(node->customers.name,name); 
    strcpy(node->customers.Mob,Mob);
    strcpy(node->customers.address,address);
    node->customers.amount_per_month=month;
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
struct customer* insert_customer(int key,struct customer* node, char name[],char Mob[],char address[],float month) 
{ 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
    {
 
        return(newNode_customer(key,name,Mob,address,month)); 
    }   
    if (key < node->customers.VIN) 
        node->left  = insert_customer(key,node->left, name,Mob,address,month); 
    else if (key > node->customers.VIN) 
        node->right = insert_customer(key,node->right,name,Mob,address,month); 
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
