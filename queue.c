/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return (NULL);
    q->head = q->tail = NULL;
    q->iSize = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;

    list_ele_t *ptr;
    while (q->head) {
        free(q->head->value);
        ptr = q->head;
        q->head = q->head->next;
        free(ptr);
    }

    q->iSize = 0;
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    int iStringSize = 0;
    if (!q)
        return false;

    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    while (s && s[iStringSize++] != '\0')
        ;
    newh->value = malloc(sizeof(char) * iStringSize);
    if (!newh->value) {
        free(newh);
        return false;
    }
    for (int i = 0; i < iStringSize; i++)
        newh->value[i] = s[i];

    newh->next = q->head;
    q->head = newh;
    if (!q->tail)
        q->tail = newh;
    q->iSize++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newh;
    int iStringSize = 0;

    if (!q)
        return false;

    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    newh->next = NULL;

    while (s && s[iStringSize++] != '\0')
        ;
    newh->value = malloc(sizeof(char) * iStringSize);
    if (!newh->value) {
        free(newh);
        return false;
    }
    for (int i = 0; i < iStringSize; i++)
        newh->value[i] = s[i];

    if (q->tail)
        q->tail->next = newh;
    q->tail = newh;
    if (!q->head)
        q->head = newh;
    q->iSize++;
    return true;
}

/*
  At tempt to remove element from head of queue.
  Re turn true if successful.
  Re turn false if queue is NULL or empty.
  If  sp is non-NULL and an element is removed, copy the removed string to *sp
  (u p to a maximum of bufsize-1 characters, plus a null terminator.)
  Th e space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (!q || !q->head)
        return (false);

    if (sp && q->head->value) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    list_ele_t *ptr = q->head;
    q->head = q->head->next;
    if (!q->head)
        q->tail = NULL;
    free(ptr->value);
    free(ptr);
    q->iSize--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q ? q->iSize : 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || !q->head)
        return;

    list_ele_t *ori_head, *ori_tail;
    list_ele_t *cur = q->head, *next = q->head->next, *prev;

    ori_head = q->head;
    ori_tail = q->tail;

    while (next) {
        prev = cur;
        cur = next;
        next = next->next;
        cur->next = prev;
    }

    q->head = ori_tail;
    q->tail = ori_head;
    q->tail->next = NULL;
}
