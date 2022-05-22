#ifndef SAGE_SG_LIST_H
#define SAGE_SG_LIST_H
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct sg_list {
    struct sg_list *next;
    struct sg_list *prev;
} sg_list;

void sg_list_init(sg_list *l);

void sg_list_append(sg_list *add_to, sg_list *new);
void sg_list_prepend(sg_list *add_to, sg_list *new);

void sg_list_del(sg_list *l);

void sg_list_replace(sg_list *new, sg_list *old);

bool sg_list_is_last(sg_list *l, sg_list *head);
bool sg_list_empty(sg_list *l);

bool sg_list_is_singular(sg_list *l);

void sg_list_clear(sg_list *l);

size_t sg_list_count(sg_list *l);

sg_list *sg_list_pop_next(sg_list *l);
sg_list *sg_list_pop_prev(sg_list *l);
sg_list *sg_list_get_next(sg_list *l);
sg_list *sg_list_get_prev(sg_list *l);


/**
 * @brief Loop through all list items
 * 
 * lpos must be around before this call.
 * 
 * @param lpos A list pointer used for iterating
 * @param lhead The list being iterated against
 * 
 */
#define sg_list_foreach(lpos, lhead) \
    for ((lpos) = (lhead)->next; (lpos) != (lhead); (lpos) = (lpos)->next)

/**
 * @brief Loop through all list items going reverse
 * 
 * lpos must be around before this call.
 * 
 * @param lpos A list pointer used for iterating
 * @param lhead The list being iterated against
 * 
 */
#define sg_list_foreach_rev(lpos, lhead) \
    for ((lpos) = (lhead)->prev; (lpos) != (lhead); (lpos) = (lpos)->prev)

/**
 * @brief Loop through all list items with the ability to delete safely
 * 
 * lpos must be around before this call.
 * ltemp must be around before this call.
 * 
 * @param lpos A list pointer used for iterating
 * @param ltemp A list to use a temp storage
 * @param lhead The list being iterated against
 * 
 */
#define sg_list_foreach_safe(lpos, ltemp, lhead) \
    for ((lpos) = (lhead)->next, (ltemp) = (lpos)->next; (lpos) != (lhead); \
        (lpos) = (ltemp), (ltemp) = (lpos)->next)

/**
 * @brief Loop through all list items with the ability to delete safely in reverse
 * 
 * lpos must be around before this call.
 * ltemp must be around before this call.
 * 
 * @param lpos A list pointer used for iterating
 * @param ltemp A list to use a temp storage
 * @param lhead The list being iterated against
 * 
 */
#define sg_list_foreach_safe_rev(lpos, ltemp, lhead) \
    for ((lpos) = (lhead)->prev, (ltemp) = (lpos)->prev; (lpos) != (lhead); \
        (lpos) = (ltemp), (ltemp) = (lpos)->prev)

/**
 * @brief CONTAINING_RECORD macro
 * 
 * GFor getting the parent stuct
 */
#ifndef  CONTAINING_RECORD
#define  CONTAINING_RECORD( ptr, type, member )                 \
    ( (type *) ((char *) (ptr) - (char *)(&((type *)0)->member)) )
#endif

/**
 * @brief container_of macro
 * 
 * For getting the parent stuct
 */
#ifndef container_of
#define container_of(ptr, type, member) \
    ( (type *) ((char *) (ptr) - offsetof(type, member)))
#endif    

/**
 * @brief Gets the parent struct using a list
 * 
 * Uses CONTAINING_RECORD
 * 
 * @example sg_list_entry(ptr, struct ListTesting, list)
 * 
 * @param ptr Is point to an item in the struct you want to check against
 * @param type Is the actual struct being checked
 * @param member The a member of that struct, think it has to match the type of ptr
 * 
 */
#define sg_list_entry(ptr, type, member) \
    CONTAINING_RECORD(ptr,type,member)


/**
 * @brief Gets the parent struct using a list
 * 
 * Uses container_of
 * 
 * @example sg_list_entry2(ptr, struct ListTesting, list)
 * 
 * @param ptr Is point to an item in the struct you want to check against
 * @param type Is the actual struct being checked
 * @param member The a member of that struct, think it has to match the type of ptr
 * 
 */
#define sg_list_entry2(ptr, type, member) \
    container_of(ptr,type,member)

#endif
