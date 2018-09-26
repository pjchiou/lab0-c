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
        // free(q->head->value);
        ptr = q->head;
        q->head = q->head->next;
        free(ptr);
    }

    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
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
    /* What should you do if the q is NULL?
       Ans: if q is null or malloc failed, then return false.*/
    if (!q)
        return false;

    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    newh->value = strdup(s);
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL?
       Ans: strdup returns NULL when failed.*/
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
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newh;

    if (!q)
        return false;

    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    newh->next = NULL;

    newh->value = strdup(s);
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
        // free(q->head->value);
    }

    list_ele_t *ptr = q->head;
    q->head = q->head->next;
    if (!q->head)
        q->tail = NULL;
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
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->iSize;
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

    /* You need to write the code for this function */
}
