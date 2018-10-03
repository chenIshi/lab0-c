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
    /* What if malloc returned NULL? */

    if (q == NULL)
        return NULL;

    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    /* Free queue head first */
    if (q == NULL)
        return;

    list_ele_t *free_ptr;
    list_ele_t *temp;
    free_ptr = q->head;
    while (free_ptr != NULL) {
        temp = free_ptr;
        free_ptr = free_ptr->next;
        free(temp);
    }
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
    /* What should you do if the q is NULL? */
    if (q == NULL)
        return false;

    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (newh == NULL)
        return false;
    char *val;
    val = strdup(s);
    if (val == NULL) {
        free(newh);
        return false;
    }

    /* update queue size and head/ tail pointer */
    q->size++;
    /* To do: remove if statement to get stable line count */
    if (q->size <= 1)
        q->tail = newh;

    newh->next = q->head;
    newh->value = val;
    q->head = newh;
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
    if (q == NULL)
        return false;

    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;

    char *val;
    val = strdup(s);
    if (val == NULL) {
        free(newh);
        return false;
    }

    q->size++;
    if (q->size <= 1)
        q->head = newh;

    q->tail->next = newh;
    newh->value = val;
    newh->next = NULL;
    q->tail = newh;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    /* return false if queue is NULL or empty */
    if (q == NULL)
        return false;
    if (q->size <= 1)
        q->tail = NULL;

    if (q->head == NULL && q->tail == NULL)
        return false;

    list_ele_t *free_ptr = q->head;
    q->head = q->head->next;

    q->size--;

    if (sp == NULL) {
        free(free_ptr);
        return true;
    }
    // to do: unstable if execution time
    size_t str_len;
    if (strlen(free_ptr->value) >= bufsize) {
        str_len = bufsize - 1;
    } else {
        str_len = strlen(free_ptr->value);
    }

    strncpy(sp, free_ptr->value, str_len);
    sp[str_len] = '\0';

    /*
    if (strlen(free_ptr->value) >= bufsize) {
        strncpy(sp, free_ptr->value, bufsize - 1);
        sp[bufsize] = '\0';
    } else {
        strncpy(sp, free_ptr->value, bufsize);
    }
    */
    free(free_ptr);

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
    if (q == NULL)
        return 0;

    return q->size;
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
    /* You need to write the code for this function */

    if (q == NULL)
        return;

    list_ele_t *current;
    list_ele_t *temp;
    list_ele_t *prev;

    current = q->head;
    prev = NULL;
    temp = NULL;
    while (current != NULL) {
        temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }
    temp = q->head;
    q->head = q->tail;
    q->tail = temp;
}
