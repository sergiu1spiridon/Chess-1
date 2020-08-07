#include "Linked_List.h"
#include <string.h>

// create the list

void deleteList(List* currentList){

    if (!currentList)
    {
        printf("List it  on existent\n");
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
    Node* newHead = (Node*)malloc(sizeof(Node));

    if(NULL == newHead)
        return;

    newHead->info = info;
    newHead->next = currentList->head;
    currentList->head = newHead;
    currentList->size++;


}

// manipulate data from rear
void insertRear(List* currentList, InfoNode* info){
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
    Node* currentElement = currentList->head;

    while(strcmp(currentElement->info->key, key) != 0){
        currentElement = currentElement->next;
    }
    return currentElement;
}