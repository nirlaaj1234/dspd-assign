#include<stdio.h>
#include<stdlib.h>
#define c 4

enum Fuel_type { Petrol,Deisel,Electric,CNG };

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

struct stocks
{
        int n;
	Car_Details car[c];
	struct stocks *node[c+1];
	struct stocks *parent;
};

enum KeyStatus { Duplicate,SearchFailure,Success,InsertIt,LessKeys };

int searchPos(int key, Car_Details *key_arr, int n)
{
        int pos=0;
        while (pos < n && key > key_arr[pos].VIN)
        pos++;
        return pos;
};/*End of searchPos()*/

enum KeyStatus ins(struct stocks *ptr, int key, Car_Details *upKey,struct stocks **newnode)
{
        struct stocks *newPtr, *lastPtr;
        int pos, i, n,splitPos;
        int fuel,avail;
        Car_Details newKey, lastKey;
        enum KeyStatus value;
        if (ptr == NULL)
        {
                *newnode = NULL;
                upKey->VIN = key;
                printf("Enter the following details of car\n");
                printf("Name colour price Fuel_type(0.Petrol 1.Deisel 2.Electric 3.CNG) Car_Type Avail_cars");
                scanf("%s%s%li%d%s%d",upKey->car_name,upKey->color,&(upKey->price),&fuel,upKey->type,&avail);
                upKey->Fuel=fuel;
                upKey->avail_cars=avail;
                upKey->sold_cars=0;                
                return InsertIt;
        }
        n = ptr->n;
        pos = searchPos(key, ptr->car, n);
        if (pos < n && key == ptr->car[pos].VIN)
        return Duplicate;
        value = ins(ptr->node[pos], key, &newKey, &newPtr);
        if (value != InsertIt)
        return value;
        /*If car in node is less than M-1 where M is order of B tree*/
        printf("Enter the following details of car\n");
        printf("Name colour price Fuel_type(0.Petrol 1.Deisel 2.Electric 3.CNG) Car_Type Avail_cars");
        scanf("%s%s%li%d%s%d",newKey.car_name,newKey.color,&(newKey.price),&fuel,newKey.type,&avail);
        newKey.Fuel=fuel;
        newKey.avail_cars=avail;
        newKey.sold_cars=0;  
        if (n < c )
        {
                pos = searchPos(newKey.VIN, ptr->car, n);
                /*Shifting the key and pointer right for inserting the new key*/
                for (i=n; i>pos; i--)
                {
                        ptr->car[i] = ptr->car[i-1];
                        ptr->node[i+1] = ptr->node[i];
                }
                /*Key is inserted at exact location*/
               
                ptr->car[pos] = newKey;
                ptr->node[pos+1] = newPtr;
                ++ptr->n; /*incrementing the number of car in node*/
                return Success;
        }/*End of if */
        /*If car in nodes are maximum and position of node to be inserted is
        last*/
        if (pos == c)
        {
                lastKey = newKey;
                lastPtr = newPtr;
        }
        else /*If car in node are maximum and position of node to be inserted
        is not last*/
        {
                lastKey = ptr->car[c-1];
                lastPtr = ptr->node[c];
                for (i=c-1; i>pos; i--)
                {
                        ptr->car[i] = ptr->car[i-1];
                        ptr->node[i+1] = ptr->node[i];
                }
                ptr->car[pos] = newKey;
                ptr->node[pos+1] = newPtr;
        }
        splitPos = (c)/2;
        (*upKey) = ptr->car[splitPos];

        (*newnode)=malloc(sizeof(struct stocks));/*Right node after split*/
        ptr->n = splitPos; /*No. of car for left splitted node*/
        (*newnode)->n = c-splitPos;/*No. of car for right splitted node*/
        for (i=0; i < (*newnode)->n; i++)
        {
                (*newnode)->node[i] = ptr->node[i + splitPos + 1];
                if(i < (*newnode)->n - 1)
                (*newnode)->car[i] = ptr->car[i + splitPos + 1];
                else
                (*newnode)->car[i] = lastKey;
        }
        (*newnode)->node[(*newnode)->n] = lastPtr;
        return InsertIt;
};/*End of ins()*/

void display(struct stocks *ptr, int blanks)
{
        if (ptr)
        {
        int i;
        for (i=0; i < ptr->n; i++)
        printf("%d ",ptr->car[i].VIN);
        printf("\n");
        for (i=0; i <= ptr->n; i++)
        display(ptr->node[i], blanks+10);
        }/*End of if*/
};/*End of display()*/

void search(int key , struct stocks *root)
{
        int pos, i, n;
        struct stocks *ptr = root;
        printf("Search path:\n");
        while (ptr)
        {
        n = ptr->n;
        for (i=0; i < n; i++)
        printf(" %d",ptr->car[i].VIN);
        printf("\n");
        pos = searchPos(key, ptr->car, n);
        if (pos < n && key == ptr->car[pos].VIN)
        {
        printf("Key %d found in position %d of last dispalyed node\n",key,pos+1);
        return;
        }
        ptr = ptr->node[pos];
        }
        printf("Key %d is not available\n",key);
};/*End of search()*/



struct stocks * insert (int key,struct stocks *root)
{
        struct stocks *newnode;
        Car_Details upKey;
        enum KeyStatus value;
        value = ins(root, key, &upKey, &newnode);
        if (value == Duplicate)
        printf("Key already available\n");
        if (value == InsertIt)
        {
        struct stocks *uproot = root;
        root=malloc(sizeof(struct stocks));
        root->n = 1;
        root->car[0] = upKey;
        root->node[0] = uproot;
        root->node[1] = newnode;
        }
        return root;
};
