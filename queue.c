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
    INIT_LIST_HEAD(&q->entry);
    q->iSize = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    struct list_head *node, *safe;
    if (!q)
        return;

    list_for_each_safe(node, safe, &q->entry)
    {
        free(container_of(node, queue_t, entry)->value);
        free(container_of(node, queue_t, entry));
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
    queue_t *newh;
    if (!q)
        return false;

    newh = malloc(sizeof(queue_t));
    if (!newh)
        return false;

    newh->value = malloc(sizeof(char) * strlen(s) + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);

    list_add(&newh->entry, &q->entry);
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
    queue_t *newh;

    if (!q)
        return false;

    newh = malloc(sizeof(queue_t));
    if (!newh)
        return false;

    newh->value = malloc(sizeof(char) * strlen(s) + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);

    list_add_tail(&newh->entry, &q->entry);
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
    if (!q || list_empty(&q->entry))
        return (false);
    struct list_head *first = q->entry.next;

    if (sp && container_of(first, queue_t, entry)->value) {
        strncpy(sp, container_of(first, queue_t, entry)->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    list_del(first);
    free(container_of(first, queue_t, entry)->value);
    free(container_of(first, queue_t, entry));
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
    if (!q || list_empty(&q->entry))
        return;

}
