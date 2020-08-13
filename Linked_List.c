#include "Linked_List.h"

// create and delete the list
List* createList()
{
    List* currentList = (List*)malloc(sizeof(List));
    currentList->head = NULL;
    currentList->tail = NULL;
    currentList->size = 0;

    if (!currentList)
    {
        printf("List is non-existent\n");
        return NULL;
    }
    return currentList;
}

void deleteList(List* currentList){

    if (!currentList)
    {
        printf("List is non-existent\n");
        return;
    }

    while(NULL != currentList->head){
        Node* currentNode = currentList->head;
        currentList->head = currentList->head->next;
        free(currentNode);
    }
}

// manipulate at index
Node* getElementByKey(List* currentList, unsigned char *key){
	NULL_PARAM_STRUCT_VALIDATION(currentList)
	NULL_PARAM_STRUCT_VALIDATION(key)
	
    Node* currentElement = currentList->head;
    int ok;
    while(currentElement != NULL) {
        ok = 1;
        
        for(int i = 0; i < 193; i++)
            if(currentElement->info->key[i] != key[i])
            {
                ok = 0;
                break;
            }

        
        if (ok == 1)
        {
            return currentElement;
        }

        currentElement = currentElement->next;
    }
    return NULL;
}

// manipulate data from front
void push(List* currentList, InfoNode* info){
	NULL_PARAM_STRUCT_VALIDATION(currentList)
	NULL_PARAM_STRUCT_VALIDATION(info)

    if (!getElementByKey(currentList,info->key))
    {
        Node* newHead = (Node*)malloc(sizeof(Node));

        if(NULL == newHead)
            return;

        newHead->info = info;
        newHead->next = currentList->head;
        currentList->head = newHead;
        currentList->size++;
    }

}
InfoNode * popList(List* currentList)
{
    
	NULL_PARAM_STRUCT_VALIDATION(currentList)
	NULL_PARAM_STRUCT_VALIDATION(currentList->head)
	
    InfoNode* newInfo = currentList->head->info;
    currentList->head = currentList->head->next;
    (currentList->size)--;

    return newInfo;
}
// manipulate data from rear
void insertRear(List* currentList, InfoNode* info){
    
	NULL_PARAM_STRUCT_VALIDATION(currentList)
	NULL_PARAM_STRUCT_VALIDATION(info)
	
    if(NULL == currentList)
        return;

    if(NULL == info)
        return;

    if(getElementByKey(currentList,info->key))
    {
        return;
    }

    Node* currentNode = (Node*)malloc(sizeof(Node));
    currentNode->next = NULL;

    currentNode->info = info;
    if(NULL == currentList->head)
    {
        currentList->tail = currentNode;
        (currentList->size) ++;
        currentList->head = currentNode;
        return;
    }
    currentList->tail->next = currentNode;
    currentList->tail = currentNode;
    (currentList->size) ++;

    return;
}