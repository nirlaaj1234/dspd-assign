#include<stdio.h>
#include<stdlib.h>
#define c 4
struct stocks
{
        int n;
	int keys[c];
	//Car_Details car[c];
	struct stocks *node[c+1];
	struct stocks *parent;
};

enum KeyStatus { Duplicate,SearchFailure,Success,InsertIt,LessKeys };

int searchPos(int key, int *key_arr, int n)
{
        int pos=0;
        while (pos < n && key > key_arr[pos])
        pos++;
        return pos;
};/*End of searchPos()*/

enum KeyStatus ins(struct stocks *ptr, int key, int *upKey,struct stocks **newnode)
{
        struct stocks *newPtr, *lastPtr;
        int pos, i, n,splitPos;
        int newKey, lastKey;
        enum KeyStatus value;
        if (ptr == NULL)
        {
                *newnode = NULL;
                *upKey = key;
                return InsertIt;
        }
        n = ptr->n;
        pos = searchPos(key, ptr->keys, n);
        if (pos < n && key == ptr->keys[pos])
        return Duplicate;
        value = ins(ptr->node[pos], key, &newKey, &newPtr);
        if (value != InsertIt)
        return value;
        /*If keys in node is less than M-1 where M is order of B tree*/
        if (n < c )
        {
                pos = searchPos(newKey, ptr->keys, n);
                /*Shifting the key and pointer right for inserting the new key*/
                for (i=n; i>pos; i--)
                {
                        ptr->keys[i] = ptr->keys[i-1];
                        ptr->node[i+1] = ptr->node[i];
                }
                /*Key is inserted at exact location*/
                ptr->keys[pos] = newKey;
                ptr->node[pos+1] = newPtr;
                ++ptr->n; /*incrementing the number of keys in node*/
                return Success;
        }/*End of if */
        /*If keys in nodes are maximum and position of node to be inserted is
        last*/
        if (pos == c)
        {
                lastKey = newKey;
                lastPtr = newPtr;
        }
        else /*If keys in node are maximum and position of node to be inserted
        is not last*/
        {
                lastKey = ptr->keys[c-1];
                lastPtr = ptr->node[c];
                for (i=c-1; i>pos; i--)
                {
                        ptr->keys[i] = ptr->keys[i-1];
                        ptr->node[i+1] = ptr->node[i];
                }
                ptr->keys[pos] = newKey;
                ptr->node[pos+1] = newPtr;
        }
        splitPos = (c)/2;
        (*upKey) = ptr->keys[splitPos];

        (*newnode)=malloc(sizeof(struct stocks));/*Right node after split*/
        ptr->n = splitPos; /*No. of keys for left splitted node*/
        (*newnode)->n = c-splitPos;/*No. of keys for right splitted node*/
        for (i=0; i < (*newnode)->n; i++)
        {
                (*newnode)->node[i] = ptr->node[i + splitPos + 1];
                if(i < (*newnode)->n - 1)
                (*newnode)->keys[i] = ptr->keys[i + splitPos + 1];
                else
                (*newnode)->keys[i] = lastKey;
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
        printf("%d ",ptr->keys[i]);
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
        printf(" %d",ptr->keys[i]);
        printf("\n");
        pos = searchPos(key, ptr->keys, n);
        if (pos < n && key == ptr->keys[pos])
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
        int upKey;
        enum KeyStatus value;
        value = ins(root, key, &upKey, &newnode);
        if (value == Duplicate)
        printf("Key already available\n");
        if (value == InsertIt)
        {
        struct stocks *uproot = root;
        root=malloc(sizeof(struct stocks));
        root->n = 1;
        root->keys[0] = upKey;
        root->node[0] = uproot;
        root->node[1] = newnode;
        }
        return root;
};
