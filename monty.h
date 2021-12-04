#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

/**
* struct stack_s - doubly linked list representation of a stack (or queue)
* @n: integer
* @prev: points to the previous element of the stack (or queue)
* @next: points to the next element of the stack (or queue)
*
* Description: doubly linked list node structure
* for stack, queues, LIFO, FIFO
*/
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

stack_t *stack;
void check_args(int ac);
FILE *open_file(char *path, char *mode);
int check_line(char *line, int line_no);
int check_int(char *line, int pointer_location, int line_no);
void execute_instr(char *opcode, int func_index, unsigned int line_number);
void push(stack_t **stack, unsigned int integer);
void pall(stack_t **stack, unsigned int integer);
void pint(stack_t **stack, unsigned int integer);
void pop(stack_t **stack, unsigned int integer);
void swap(stack_t **stack, unsigned int integer);
void add(stack_t **stack, unsigned int integer);
void nop(stack_t **stack, unsigned int integer);

#endif
