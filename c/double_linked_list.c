/*
* Double linked list
* ------------------
*
* This program implements a double linked list with list head and list element.
*
* The following functions have been implemented:
* - Initialize empty list.
* - Create new enty after a list head.
* - Create new enty before a list head.
* - Remove an entry from the list (next = prev = 0 ) and return its pointer
* - Remove an entry from the list and insert after given list head.
* - Remove an entry from the list and insert before given list head.
* - Test if list is entry.
*
* Compiling on console with:
* gcc -Wall -c double_linked_list.c
* gcc -o double_linked_list double_linked_list.o
*
* Author: c0d145
* Created: 2009-12-08
* Updated: 2022-08-24: Reworked the comments.
*/

#include <stdio.h>
// Needed for memory allocation.
#include <stdlib.h> 

struct list_head {
	struct list_head *next, *prev;
};

/*
* struct for a list element / process information.
*/
struct proc_info {
	struct list_head head;
	int pid;
	int counter;
	int priority;
};

/*
* Initialize the "list anchor".
*/
void list_init(struct list_head *new) {
	new->next = new;
	new->prev = new;
}

/*
* Inserts an entry after given list head and updates the next and prev entries of the precursor and successor.
*/
void list_add(struct list_head *new, struct list_head *head) {
	// Sets previous entry (reference).
	new->prev		= head;
	// Sets next entry (reference).
	new->next		= head->next;
	// Sets next (reference) for the head to the new entry.
	head->next	 	= new;
	// Sets prev (reference) of the formerly successor to the new entry.
	new->next->prev = new;	
}

/*
* Inserts an entry before given list head and updates the next and prev entries of the precursor and successor.
*/
void list_add_tail(struct list_head *new, struct list_head *head) {
	// Sets precursor for the new entry to the formerly precursor of the head.
	new->prev		= head->prev;
	// Sets the successor of the new entry to the head.
	new->next		= head;
	// Sets the precursor for the head after the new entry has been inserted.
	head->prev	 	= new;
	// Sets next of the formerly successor to the head of the new element.
	new->prev->next = new;	
}

/*
* "Removes" an element from the list. In fact it is bypassed; 
* 'prev' of the successor element and 'next' of the precursor element
* are set onto each other.
*/
struct list_head* list_del(struct list_head *entry) {
	// Sets prev of the successor's head to the precursor of the removed element.
	entry->next->prev = entry->prev;
	// Sets next of the precursor's head to the successor of the removed element.
	entry->prev->next = entry->next;
	// Set prev and next of the element whicht should be removed to 0.
	entry->next = entry->prev = 0;
	
	return entry;
}

/*
* Removes entry an and moves / reinserts it after given head.
*/
void list_move(struct list_head *entry, struct list_head *head) {
	// Sets prev of successor's head to precursor of the element which should be removed.
	entry->next->prev = entry->prev;
	// Sets next of precursor's head to successor of the element which should be removed.
	entry->prev->next = entry->next;

	list_add(entry,head);
}

/*
* Removes an entry and moves / reinserts it before given head.
*/
void list_move_tail(struct list_head *entry, struct list_head *head) {
	// Sets prev of successor's head to precursor of the removed element.
	entry->next->prev = entry->prev;
	// Sets next of precursor's head to successor of the removed element.
	entry->prev->next = entry->next;

	list_add_tail(entry,head);
}

/*
* Tests if list ist empty. True if prev and next point onto it self.
*/
int list_empty(struct list_head *head) {
	if (head->prev == head->next && head->next == head) {
		return 1;
	} else {
		return 0;
	}
}

/*
* Prints the process list on the console.
*/
void print_list(struct list_head *anchor) {
	
	// Saves the current element of the list. 
	struct list_head *current = anchor->next;
	
	/* 
	* As long as the next element isn't the anchor keep on printing the elements on the console.
	*/
	while (current != anchor) {
		// Cast to list element.
		struct proc_info *element = (struct proc_info *) current;
		// Output the preocess data.
		printf( "ProcessID: %d \nCounter: %d \nPriority: %d\nOwn address: %p\nAddress next: %p\n\n", element->pid, element->counter, element->priority, element, current->next);
		//if (anchor != current->next) {
			current = current->next;
		//}
	}
}

/*
* Creates a process list for testing and than calls all functions.
* After every call the changed list is printed on the console.
* The test list consists of five elements with 'pid' from 0 to 4.
*/
int main()
{
	// 1. Create anchor.
	struct list_head *anchor = malloc(sizeof(struct list_head));
		
	// 2. Create list with processes.
	struct proc_info p1;
		p1.pid = 0;
		p1.counter = 1;
		p1.priority = 3;
	struct proc_info p2;
		p2.pid = 1;
		p2.counter = 2;
		p2.priority = 0;
	struct proc_info p3;
		p3.pid = 2;
		p3.counter = 3;
		p3.priority = 2;
	struct proc_info p4;
		p4.pid = 3;
		p4.counter = 4;
		p4.priority = 0;
	struct proc_info p5;
		p5.pid = 4;
		p5.counter = 5;
		p5.priority = 5;
	
	// 3. Call functions and print on console.
	
	// Initialize anchor.
	list_init(anchor);
	
	/* 
	* Add the process information to the (end of the) list one after another.
	* For that the struct is casted to "list_head".
	* Because of that we are working with two process heads which
	* can be linked.
	*/

	// Add first element after anchor.
	list_add((struct list_head *)&p1,anchor);
	printf("First element added:\n");
	print_list(anchor);
	printf("\n----------------------------\n\n");

	// Add second element after first element.
	list_add((struct list_head *)&p2,(struct list_head *)&p1);
	printf("Second element added\n");
	print_list(anchor);
	printf("\n----------------------------\n\n");
	
	// Add third element after second element.
	list_add((struct list_head *)&p3,(struct list_head *)&p2);
	printf("Third element added\n");
	print_list(anchor);
	printf("\n----------------------------\n\n");

	// Add fifth element after third element.
	list_add((struct list_head *)&p5,(struct list_head *)&p3);
	printf("Fifth element added");
	print_list(anchor);
	printf("\n----------------------------\n\n");

	// Add fourth element before fifth element.
	list_add_tail((struct list_head *)&p4,(struct list_head *)&p5);
	printf("Fourth element added before fifth element:\n");
	print_list(anchor);
	printf("\n----------------------------\n\n");

	// "Delete" an entry.
	list_del((struct list_head *)&p3);
	printf("Entry deleted:");
	print_list(anchor);
	printf("\n----------------------------\n\n");
 
	// Move an entry after given list head.
	list_move((struct list_head *)&p4,(struct list_head *)&p5);
	printf("Entry moved in front of list head:\n");
	print_list(anchor);
	printf("\n----------------------------\n\n");
	
	// Move an entry before given list head.
	printf("Entry moved after list head:\n");
	list_move_tail((struct list_head *)&p1,anchor);
	print_list(anchor);
	printf("\n----------------------------\n\n");

	// Test list_empty function.
	printf("Empty = %d\n", list_empty(anchor));
	list_del((struct list_head *)&p1);
	list_del((struct list_head *)&p2);
	list_del((struct list_head *)&p4);
	list_del((struct list_head *)&p5);
	printf("Empty = %d\n", list_empty(anchor));

    return 0;
}
