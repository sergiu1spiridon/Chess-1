#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct Node
{
	void *info;
	struct Node *next;
}Node;

typedef struct List
{
    Node* head;
    int size;
}List;

// create and delete the list
void createList(List** currentList,int size);
void deleteList(List** currentList);

// manipulate data from front
void push(List** currentList, void*info);
void* pop(List** currentList);

// manipulate data from rear
void insertRear(List** currentList);
void* deleteRear(List** currentList); 

#endif /*LINKED_LIST*/