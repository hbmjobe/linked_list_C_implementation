/*------------------------------------------------------------------------
An exercise with a self-referenced structrue and malloc/free: a simple
stack with push() and pop() functions, implemented with a linked list.

Same as 'Stack_Linked_list_1.c', but with more functions

Usage: progr_name (and follow the instructions)

Remark: observe/debug the memory allocation/deallocation with gdb !
------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

void push(int data);
int pop(void);
void foo();
void foo2(int data);

int is_empty();
int size1();
int size2();

void traverse_loop(void);
void traverse_rec(void);
void traverse_rec_inv(void);

void print_usage(){

  printf("\n");
  printf("push/pop/foo   : p)push(i)        o)pop           f)foo      F)foo2(i)\n");
  printf("Other functions: e)is_empty       s)size1         S)size2\n");
  printf("                 x)traverse_loop  y)traverse_rec  z)traverse_rec_inv\n");
  printf("Test progr     : H)Help           Q)Quit\n\n");
}


int main(){ //--- test program without error treatment
  char c; 
  int i;

  char *prompt = ">";

  print_usage();
  printf("%s", prompt);
  
  while ( (c = getchar()) ) { // main loop
    switch(c) {

      /*-----   push, pop, foo   -----*/
      case 'p': // push(i)
        scanf("%d", &i);
        push(i);
        break;

      case 'o': // pop()
        //----- generates a 'Segmentation fault: 11' at runtime if stack is empty
        printf("%d\n", pop());
        break;

      case 'f': // foo
        foo();
        break;

      case 'F': // foo2
        scanf("%d", &i);
        foo2(i);
        break;

      /*-----   other functions   -----*/
      case 'e': // is_empty()
        printf("%i\n", is_empty());
        break;
 
      case 's': // size1()
        printf("%i\n", size1());
        break;

      case 'S': // size2()
        printf("%i\n", size2());
        break;

      case 'x': // traverse_loop
        traverse_loop();
        break;

      case 'y': // traverse_rec
        traverse_rec();
        break;

      case 'z': // traverse_rec_inv
        traverse_rec_inv();
        break;

      /*-----   Test program utilities   -----*/
      case 'H': // Help
        print_usage();
        break;

      case 'Q': // Quit
        return 0;

      default:
        print_usage();
        break;
    } // end switch

    while (getchar() != '\n') {} /* skip end of line */
    printf("%s", prompt);

  } // end main loop
  return 0;
}

/*------------------------------------------------------------------------
                        shared data structures
------------------------------------------------------------------------*/
struct node_t{ // declaration of a stack node of type 'struct node_t'
  
   int data;                  // data to be stored
   struct node_t *previous;   // points to the previous node
}; 

typedef struct node_t node_t; // 'struct_node' and 'node_t' are synonyms

node_t *stack_ptr = NULL;     // 'stack_ptr' variable points to the top node;
                              // it is shared variable used by push(), pop() !!!

node_t *recursion_ptr = NULL;  //pointer that stores a copy of the value of the stack_ptr for the recursion
     /*-----------------------------------------------------------
              stack_ptr --> | * | --> | * | --> | * | --|
                              t    p
     -----------------------------------------------------------*/

/*------------------------------------------------------------------------
           push(), pop(), foo() implementation with a linked list
------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------
    global variable to be inceremented by one on every call to the push() function
    and decremented by one on every call to the pop() function.
----------------------------------------------------------------------------------*/
int shared_count = 0; 

void push(int data) {

   node_t *ptr;                   // local pointer ptr to a node of type 'node_t'
   ptr = malloc(sizeof(node_t));  // allocate a memory region of type 'node_t', pointed by ptr

   ptr->data = data;           // initialize the 'data' and 'previous' members
   ptr->previous = stack_ptr;  // of the new top stack node

   stack_ptr = ptr;            // update 'stack_ptr' to the new top node

   shared_count++;             //increment shared variable on push.

   recursion_ptr = ptr;         //update recursion pointer.
}

int pop(void) {//----- generates a 'Segmentation fault: 11' at runtime if stack is empty

   int temp_data = stack_ptr->data;  // temporary variable to hold the data of the old top node
   node_t *temp_ptr = stack_ptr;     // temporary pointer to the old top node
   
   stack_ptr = stack_ptr->previous; // update 'stack_ptr' to the new top node

   free(temp_ptr);   // free memory hold by the old top node, pointed by temp_ptr

   shared_count--;   //decrement shared variable on pop.

   recursion_ptr = stack_ptr;  //update recursion_ptr

   return temp_data; // return the data of the old top node

}

// inverse the top node with its previous node
void foo() {

   //printf("not yet implemented\n");
   // Draw a picture !!!
   printf("pop to view inversion\n");  
   
   node_t *temp_ptr = stack_ptr;

   stack_ptr = stack_ptr->previous;

   stack_ptr->previous = temp_ptr;

}

// add 'data' just behind the top node  
void foo2(int data){

   //printf("not yet implemented\n");
   // Draw a picture !!!  

   node_t *ptr;
   ptr = malloc(sizeof(node_t));

   ptr->data = data;

   if (stack_ptr->previous == NULL){
     /* code */
    stack_ptr->previous = ptr;

   }else{

    node_t *temp_ptr = stack_ptr->previous;
    stack_ptr->previous = ptr;
    ptr->previous = temp_ptr;

   }
}

/*------------------------------------------------------------------------
                     is_empty() and size() implementation
------------------------------------------------------------------------*/
int is_empty(){

   // printf("not yet implemented\n");    
   // return -1; // not yet implemented
  if (stack_ptr == NULL) {
    /* code */
    return 1;
  }
  return 0;
}

// with a shared variable size
int size1() {

   //printf("not yet implemented\n"); 
   printf("current size");   
   return shared_count; // not yet implemented   
}

// by traversing the stack
int size2() {

   // printf("not yet implemented\n");    
   // return -1; // not yet implemented   
  int count = 0;

  node_t *ptr = stack_ptr;

  while(ptr != NULL){

    count+=1;
    ptr = ptr->previous;

  }

  return count;
}

/*------------------------------------------------------------------------
     traverse_loop(), traverse_rec(), traverse_rec_inv implementation
------------------------------------------------------------------------*/
void traverse_loop(){

   //printf("not yet implemented\n");  

   node_t *ptr = stack_ptr;

   while(ptr != NULL){

    printf("%i\n", ptr->data);

    ptr = ptr->previous;
   }  
}


void traverse_rec(){

  //printf("not yet implemented\n"); 

   if(recursion_ptr != NULL){
    printf("%i\n", recursion_ptr->data);
    recursion_ptr = recursion_ptr->previous;
    traverse_rec();
   }
   
    recursion_ptr = stack_ptr;
}

void traverse_rec_inv(){

   printf("not yet implemented\n");    

   
}
