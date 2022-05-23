// sg_list - v1

/*
Single file list

This is mostly a learning project so don't recommend using this.

USAGE:
Define SG_LIST_IMPLEMENTATION before including this file
or bundle it with sg_list.c / another implemenation

LICENSE:
I consider this public domain, but licenses are confusing so I will ignore it for now.

*/
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
    
#endif // SG_LIST_H

#ifdef SG_LIST_IMPLEMENTATION
// =============================================================================================
// sg_list.c - This is for having everything in a single file
// =============================================================================================
static inline void __sg_list_add(sg_list *l, sg_list *prev, sg_list *next);
static inline void __sg_list_del(sg_list *prev, sg_list *next);
static inline void __sg_list_del_init(sg_list *l);
static inline sg_list *__sg_list_pop(sg_list *l, sg_list *target);


/**
 * @brief Initialize a List
 * 
 * @param l The list being initialized
 */
void sg_list_init(sg_list *l) {
    l->next = l; 
    l->prev = l;
}


/**
 * @brief Adding into list l between prev and next
 * 
 * @param l The new list
 * @param prev The previous list
 * @param next The next list
 */
static inline void __sg_list_add(sg_list *l, sg_list *prev, sg_list *next) {
    next->prev = l;
    l->next = next;
    l->prev = prev;
    prev->next = l;
}

/**
 * @brief Append an item to a list
 * 
 * @param add_to The List to add after
 * @param new The new list item
 */
void sg_list_append(sg_list *add_to, sg_list *new) {
    sg_list_del(new);
    __sg_list_add(new, add_to, add_to->next);
}

/**
 * @brief Prepend an item to a list
 * 
 * @param add_to The List to add before
 * @param new The new list item
 */
void sg_list_prepend(sg_list *add_to, sg_list *new) {
    sg_list_del(new);
    __sg_list_add(new, add_to->prev, add_to);
}

/**
 * @brief Sets the prev and next lists to each other
 * 
 * This is for deleting lists but not recommended to use __sg_list_del_init
 * 
 * @param prev The prev of the lists
 * @param next The next of the lists
 */
static inline void __sg_list_del(sg_list *prev, sg_list *next) {
    next->prev = prev;
    prev->next = next;
}

/**
 * @brief Removes a list by pulling it out of the current list then initializing it
 * 
 * @param l The list to delete
 */
static inline void __sg_list_del_init(sg_list *l) {
    __sg_list_del(l->prev, l->next);
    sg_list_init(l);
}

/**
 * @brief Deletes a list item
 * 
 * Will remove the item from the list then re-initialize it.
 * 
 * @param l The list to delete
 */
void sg_list_del(sg_list *l) {
    __sg_list_del_init(l);
}

/**
 * @brief Will replace a item in a list with another
 * 
 * @param new The new item
 * @param old The item to remove (gets deleted)
 */
void sg_list_replace(sg_list *new, sg_list *old) {
    sg_list_append(old, new);
    sg_list_del(old);
}

/**
 * @brief Checks if a list is the last
 * 
 * @param l The list to check
 * @param head The known end of the list
 * @return true l->next == head
 * @return false l->next != head 
 */
bool sg_list_is_last(sg_list *l, sg_list *head) {
    return l->next == head;
}

/**
 * @brief Checks if list is empty
 * 
 * @param l The list to check
 * @return true If empty
 * @return false If not empty
 */
bool sg_list_empty(sg_list *l) {
    return l->next == l;
}

/**
 * @brief Checks if there is only 1 list item
 * 
 * @param l The list to check
 * @return true !empty && another list
 * @return false empty || multiple lists
 */
bool sg_list_is_singular(sg_list *l) {
    return !sg_list_empty(l) && (l->next == l->prev);
}

/**
 * @brief List size
 * 
 * @param l The list to count
 * @return size_t size of list
 */
size_t sg_list_count(sg_list *l) {
    size_t c = 0;
    sg_list *curr;
    sg_list_foreach(curr, l) {
        c++;
    }

    return c;
}

/**
 * @brief Utility for getting a list then deleting it.
 * 
 * @param l The list to check against
 * @param target The target of the deletion / return
 * @return sg_list* Either NULL if empty or the target
 */
static inline sg_list *__sg_list_pop(sg_list *l, sg_list *target) {
    sg_list *tmp = target;
    if (sg_list_empty(l)) {
        return NULL;
    }

    sg_list_del(target);

    return tmp;
}


/**
 * @brief Return the next list then pop it from the rest
 * 
 * @param l The list base
 * @return sg_list* NULL or l->next
 */
sg_list *sg_list_pop_next(sg_list *l) {
    return __sg_list_pop(l, l->next);
}

/**
 * @brief Return the prev list then pop it from the list
 * 
 * @param l The list base 
 * @return sg_list* NULL or l->prev
 */
sg_list *sg_list_pop_prev(sg_list *l) {
    return __sg_list_pop(l, l->prev);
}

/**
 * @brief Returns next List or NULL 
 * 
 * @param l List to check
 * @return sg_list* NULL or l->next
 */
sg_list *sg_list_get_next(sg_list *l) {
    return l->next != l ? l->next : NULL;
}

/**
 * @brief Returns the prev list or NULL
 * 
 * @param l List to check
 * @return sg_list* NULL or l->prev
 */
sg_list *sg_list_get_prev(sg_list *l) {
    return l->prev != l ? l->prev : NULL;
}

/**
 * @brief Deletes all items in list
 * 
 * @param l The list to clear
 */
void sg_list_clear(sg_list *l) {
    struct sg_list *pos, *temp;

    sg_list_foreach_safe(pos, temp, l) {
        sg_list_del(pos);
    }
}
#endif // SG_LIST_IMPLEMENTATION

