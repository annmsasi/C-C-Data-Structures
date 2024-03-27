/****************************************************************************************
Ann Sasi
pa4
CruzID asasi
List.c

*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

typedef int ListElement;

Node NewNode(void* data)
{
    Node N = malloc(sizeof(NodeObj));
    assert(sizeof(NodeObj) != 0);
    assert(N != NULL);
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return (N);
}

List newList(void)
{
    List L;
    L = (List)malloc(sizeof(ListObj));
    assert(L != NULL);
    L->front = NULL;
    L->length = 0;
    L->back = NULL;
    L->index = -1;
    L->cursor = NULL;
    return L;

}
bool isEmpty(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling isEmpty() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->length == 0);
}
// Creates and returns a new empty List.
void freeNode(Node *node) {
    // Ensure that the node is not NULL before attempting to free
    if (node != NULL && *node != NULL) {
        free(*node);
        *node = NULL;
        node = NULL;
    }
}

void freeList(List *pL)
{
    if (pL != NULL && *pL != NULL)
    {
        clear(*pL);
        free(*pL);
        *pL = NULL;
        pL = NULL;
    }
}
// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
// Access functions -----------------------------------------------------------

int length(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling Length() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->length);
} // Returns the number of elements in L.
int index(List L)
{
    if (L -> cursor != NULL)
    {
        return (L->index);
    }
    return -1;
} // Returns index of cursor element if defined, -1 otherwise.
void* front(List L)
{
    if (L == NULL || L->length <= 0)
    {
        printf("List Error: calling front() on an empty or NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
} // Returns front element of L. Pre: length()>0
void* back(List L)
{
    if (L == NULL || L->length <= 0)
    {
        printf("List Error: calling back() on an empty or NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data; // Returns back element of L. Pre: length()>0
}
void* get(List L)
{
    if (L == NULL || L->length <= 0 || (L->index) < 0)
    {
        printf("List Error: calling get() on an empty or NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == NULL) {
        printf("Cannot get(), cursor is null\n");
        exit(EXIT_FAILURE);
    }

    return (L->cursor->data);
} // Returns cursor element of L. Pre: length()>0, indexx()>=0


// Returns true iff Lists A and B contain the same
// sequence of elements, returns false otherwise.
// Manipulation procedures ----------------------------------------------------
void clear(List L)
{
   if ((L == NULL) || L->length == 0) {
    return;
   }
   Node cur = L->front;
   Node nextNode;
   
   while (cur != NULL) {
    nextNode = cur->next;
    freeNode(&cur);
    cur = nextNode;
   }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
} // Resets L to its original empty state.

void set(List L, void* x)
{
    if (L == NULL || L->length <= 0 || (L->index) < 0)
    {
        printf("List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
} // Overwrites the cursor element’s data with x.
  // Pre: length()>0, indexx()>=0
  
void moveFront(List L)
{
    if (L->length > 0)
    {
        L->cursor = L->front;
        L->index = 0;
    }
    else
    {
        L->cursor = NULL;
        L->index = -1;
    }
} // If L is non-empty, sets cursor under the front element,
  // otherwise does nothing.
void moveBack(List L)
{
    if (!isEmpty(L))
    {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
    else
    {
        L->cursor = NULL;
        L->index = -1;
    }
} // If L is non-empty, sets cursor under the back element,
  // otherwise does nothing.

void movePrev(List L)
{
    if (L->cursor == L->front)
    {
        L->cursor = NULL;
        L->index = -1;
    }
    else if (L->cursor == NULL)
    {
        return;
    }
    else
    {
        L->cursor = L->cursor->prev;
        L->index = L->index - 1;
    }
} // If cursor is defined and not at front, move cursor one
  // step toward the front of L; if cursor is defined and at
  // front, cursor becomes undefined; if cursor is undefined
  // do nothing
void moveNext(List L)
{
    if (L->cursor == L->back)
    {
        L->cursor = NULL;
        L->index = -1;
    }

    else if (L->cursor == NULL)
    {
        return;
    }
    else
    {
        L->cursor = L->cursor->next;
        L->index = L->index + 1;
    }

} // If cursor is defined and not at back, move cursor one
  // step toward the back of L; if cursor is defined and at
  // back, cursor becomes undefined; if cursor is undefined
  // do nothing

void prepend(List L, void* x)
{


    if (L == NULL)
    {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = NewNode(x);

    if (length(L) == 0)
    {
        L->front = N;
        L->back = N;
    }
    else
    {
        N -> next = L -> front;
        N -> prev = NULL;
        N -> next -> prev = N;
        L -> front = N;
        L -> index ++;
    }
    L->length++;
} // Insert new element into L. If L is non-empty,
  // insertion takes place before front element.
void append(List L, void* x)
{
    

    if (L == NULL)
    {
        printf("List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = NewNode(x);
    if (L->length > 0)
    {
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
    else
    {
        L->back = L->front = N;
    }
    L->length++;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void insertBefore(List L, void* x)
{
    
    if ((L->cursor == NULL) || (L->length <= 0) || (L->index) < 0)
    {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = NewNode(x);
    if (L->cursor == L->front)
    {
        N -> next = L -> front;
        N -> prev = NULL;
        N -> next -> prev = N;
        L -> front = N;
        L -> index ++;
    }
    else
    {
        N->next = L->cursor;
        N->prev = L->cursor->prev;
        L->cursor->prev->next = N;
        L->cursor->prev = N;
        if (L->index != -1)
        {
            L->index++;
        }
    }
    L->length++;
} // Insert new element before cursor.
  // Pre: length()>0, indexx()>=0
void insertAfter(List L, void* x)
{
    
    if ((L->cursor == NULL) || (L->length <= 0) || (L->index < 0))
    {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    
    if (L->cursor == L->back)
    {
        Node N = NewNode(x);
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
        L -> length += 1;
    }
    else
    {
        Node N = NewNode(x);   
        N->prev = L->cursor;
        N->next = L->cursor->next;
        L->cursor->next->prev = N;
        L->cursor->next = N;
        L -> length += 1;
    }
} // Insert new element after cursor.
  // Pre: length()>0, indexx()>=0
void deleteFront(List L)
{
    if ((L == NULL )|| (L->length <= 0))
    {
        printf("List Error: calling deleteFront() on empty or NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node temp = L->front;

    if (L->cursor == L->front)
    {
        L->cursor = NULL;
        L->index = -1;
    } else {
        L->index--;
    }

    if (L->length > 1)
    {
        L->front = temp->next;
        L->front->prev = NULL;
    }
    else if (L->length == 1)
    {
        L->cursor = NULL;
        L->back = NULL;
        L->front = NULL;
        L -> index = -1;
    }

    L->length--;

    // Free memory of the old front node
    freeNode(&temp);
}
// Delete the front element. Pre: length()>0

void deleteBack(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (isEmpty(L))
    {
        printf("List Error: calling deleteBack() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    Node temp = L -> back;

    if (L->cursor == L->back)
    {
        L->cursor = NULL;
        L->index = -1;
    } 
    if (length(L) > 1)
    {
        L->back = temp -> prev;
        L->back->next = NULL;

    }
    if (L->length == 1)
    {
        L->front = NULL;
        L->cursor = NULL;
        L->back = NULL;
        L->index = -1;
    }
    
    freeNode(&temp);
    L->length--;
}
// Delete the back element. Pre: length()>0

void delete(List L)
{
    if ((L->length <= 0) || (L -> index <0))
    {
        exit(EXIT_FAILURE);
    }
    if (L->cursor == L->front)
    {
        deleteFront(L);
    }
    else if (L->cursor == L->back)
    {
        deleteBack(L);
    }
    else{
        Node temp = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        freeNode(&temp);
        L->length--;
    }
    L->cursor = NULL;
    L->index = -1;
} // Delete cursor element, making cursor undefined.
  // Pre: length()>0, indexx()>=0

// Other operations -----------------------------------------------------------
void printList(FILE *out, List L)
{ 
    if (out == NULL || L == NULL)
    {
        printf("List Error: calling printList() with NULL parameters\n");
        exit(EXIT_FAILURE);
    }
    Node N = L -> front;
    while (N != NULL){
        fprintf(out, "%d ", N->data);
        N = N -> next;
    }
    freeNode(&N);

}
