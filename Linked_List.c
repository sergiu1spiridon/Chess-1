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

// manipulate data from front
void push(List* currentList, InfoNode* info){
    if(NULL == currentList)
        return;
    if(NULL == info)
        return;
    Node* newHead = (Node*)malloc(sizeof(Node));

    if(NULL == newHead)
        return;

    newHead->info = info;
    newHead->next = currentList->head;
    currentList->head = newHead;
    currentList->size++;


}
InfoNode * popList(List* currentList)
{
    if(NULL == currentList)
        return NULL;

    InfoNode* newInfo = currentList->head;
    currentList->head = currentList->head->next;
    currentList->size--;

    return newInfo;
}
// manipulate data from rear
void insertRear(List* currentList, InfoNode* info){
    if(NULL == currentList)
        return;

    if(NULL == info)
        return;

    Node* currentNode = (Node*)malloc(sizeof(Node));
    currentNode->next = NULL;

    currentNode->info = info;
    currentList->tail->next = currentNode;
    currentList->tail = currentNode;
    currentList->size ++;

    free(currentNode); 
}


// manipulate at index
Node* getElementByKey(List* currentList, unsigned char *key){
    if(NULL == currentList )
        return NULL;

    if(NULL == key)
        return NULL;

    Node* currentElement = currentList->head;

    while(currentElement != NULL && strcmp((const char *)(currentElement->info->key), (const char *)key) != 0){
        currentElement = currentElement->next;
    }
    return currentElement;
}