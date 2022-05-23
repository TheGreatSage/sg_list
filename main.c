#include <stdio.h>
#include <stdlib.h>
#include "src/sg_list.h"
#include <assert.h>

struct ListTesting {
    int id;
    struct sg_list list;
} ListTesting;

static const int LIST_SIZE = 5;

void list_tests(void);

int main(void) {

    list_tests();

    return 0;
}

void list_tests(void) {

    printf("Starting List Tests\n");
   
    // Fixed
    struct ListTesting lists[LIST_SIZE];

    // The testing structs
    struct sg_list listHead;

    // Using pointers
    struct sg_list *tmp;        // tmp operations
    struct ListTesting *elem;  // element operations
    struct sg_list *ptr;        // Loops
    

    for (int i = 0; i < LIST_SIZE; i++) {
        sg_list_init(&lists[i].list);
        lists[i].id = i;
    }


    // Init the Empty list
    sg_list_init(&listHead);
    
    
    // Verify list count
    printf("Count 0: %zi\n", sg_list_count(&listHead));
    assert(sg_list_count(&listHead) == 0);

    // Verify Popping against NULL
    printf("==== Null Check ====\n");
    tmp = sg_list_pop_next(&listHead);
    assert(tmp == NULL);
    tmp = sg_list_pop_prev(&listHead);
    assert(tmp == NULL);

    printf("==== Prepend Check ====\n");    
    // Verify Count works with non-head of list.
    sg_list_prepend(&listHead, &lists[0].list);
    sg_list_prepend(&listHead, &lists[1].list);
    printf("Count 2: %zi\n", sg_list_count(&listHead));
    assert(sg_list_count(&listHead) == 2);

    sg_list_foreach(ptr, &listHead) {
		elem = sg_list_entry(ptr, struct ListTesting, list);
        printf("Checking List: %i\n", elem->id);
	}    

    printf("==== Popping Previous ====\n");
    tmp = sg_list_pop_prev(&listHead); // Should be id 1
    elem = sg_list_entry2(tmp, struct ListTesting, list);
    printf("elem == Popped: %i == %i\n", elem->id, lists[1].id);
    assert(elem->id == lists[1].id);

    sg_list_foreach(ptr, &listHead) {
		elem = sg_list_entry(ptr, struct ListTesting, list);
        printf("Checking List: %i\n", elem->id);
	}

    printf("Last Element: %i\n", elem->id);
    printf("Count 1: %zi\n", sg_list_count(&listHead));
    assert(sg_list_count(&listHead) == 1);

    // Lets add back some stuff
    sg_list_append(&listHead, &lists[1].list);
    sg_list_append(&listHead, &lists[2].list);

    sg_list_foreach_rev(ptr, &listHead) {
		elem = sg_list_entry(ptr, struct ListTesting, list);
        printf("R Checking List: %i\n", elem->id);
	}
    printf("Count 3: %zi\n", sg_list_count(&listHead));
    assert(sg_list_count(&listHead) == 3);

    // Lets Replace 1 again with 3
    sg_list_replace(&lists[3].list, &lists[1].list);
    // printf("Count ==: %zi\n", sg_list_count(&fixed));
    printf("==== Replace Check ====\n");
    // Loop through fixed to make sure it's not there
    sg_list_foreach_rev(ptr, &listHead) {
        elem = sg_list_entry(ptr, struct ListTesting, list);
        printf("R Checking: %i != %i\n", elem->id, lists[1].id);
        assert(elem->id != lists[1].id);
    }
    printf("Count 3: %zi\n", sg_list_count(&listHead));
    assert(sg_list_count(&listHead) == 3);

    printf("==== Popping Next ====\n");
    tmp = sg_list_pop_prev(&listHead); // Should be id 0
    tmp = sg_list_pop_next(&listHead); // Should be id 2
    elem = sg_list_entry2(tmp, struct ListTesting, list);
    printf("elem == Popped: %i == %i\n", elem->id, lists[2].id);
    assert(elem->id == lists[2].id);

    sg_list_foreach(ptr, &listHead) {
		elem = sg_list_entry(ptr, struct ListTesting, list);
        printf("Checking List: %i\n", elem->id);
	}

    printf("Last Element: %i\n", elem->id);
    printf("Count 1: %zi\n", sg_list_count(&listHead));
    assert(sg_list_count(&listHead) == 1);

    printf("==== List Is Singular ====\n");
    assert(sg_list_is_singular(&listHead));

    printf("==== List is Last ====\n");
    assert(sg_list_is_last(&listHead, &lists[3].list));

    printf("==== Clearing ====\n");
    sg_list_clear(&listHead);
    assert(sg_list_empty(&listHead));
    assert(sg_list_count(&listHead) == 0);
    assert(sg_list_get_next(&listHead) == NULL);
    assert(sg_list_get_prev(&listHead) == NULL);

    printf("==== Creating Big List ====\n");
    // 2 3 4 1 0
    sg_list_append(&listHead, &lists[0].list);
    sg_list_append(&listHead, &lists[1].list);
    sg_list_append(&listHead, &lists[2].list);
    sg_list_append(&listHead, &lists[2].list);
    sg_list_append(&listHead, &lists[2].list);
    sg_list_prepend(&listHead, &lists[3].list);
    sg_list_append(&listHead, &lists[1].list);
    sg_list_prepend(&listHead, &lists[4].list);
    sg_list_append(&listHead, &lists[2].list);
    sg_list_prepend(&listHead, &lists[1].list);
    sg_list_append(&listHead, &lists[3].list);
    sg_list_prepend(&listHead, &lists[4].list);
    sg_list_prepend(&listHead, &lists[2].list);
    sg_list_prepend(&listHead, &lists[0].list);
    sg_list_prepend(&listHead, &lists[3].list);
    sg_list_append(&listHead, &lists[0].list);
    sg_list_prepend(&listHead, &lists[2].list);
    

    // 0 1 2 3 4
    // sg_list_append(&fixed, &lists[0].list);
    // sg_list_append(&fixed, &lists[1].list);
    // sg_list_append(&fixed, &lists[2].list);
    // sg_list_append(&fixed, &lists[3].list);
    // sg_list_append(&fixed, &lists[4].list);

    assert(sg_list_get_next(&listHead) != NULL);
    assert(sg_list_get_prev(&listHead) != NULL);
    assert(!sg_list_empty(&listHead));
    printf("Count 5: %zi\n", sg_list_count(&listHead));
    assert(sg_list_count(&listHead) == 5);

    sg_list_foreach_rev(ptr, &listHead) {
		elem = sg_list_entry(ptr, struct ListTesting, list);
        printf("R Checking List: %i\n", elem->id);
	}

    // Was originally using other functions but
    // they ended up just being append/prepend
    printf("==== Reordering ====\n");
    sg_list_prepend(&lists[3].list, &lists[2].list);
    sg_list_prepend(&lists[4].list, &lists[3].list);
    sg_list_append(&lists[1].list, &lists[2].list);
    sg_list_append(&lists[0].list, &lists[1].list);

    sg_list_foreach_rev(ptr, &listHead) {
		elem = sg_list_entry(ptr, struct ListTesting, list);
        printf("R Checking List: %i\n", elem->id);
	}

    printf("Passed the List Testing\n");
}