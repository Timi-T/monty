#include "monty.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * push - function1 to push an integer to stack
 *
 * @stack: stack to be pushed to
 * @line_number - line number in execution
 *
 * Return: nothing
 */

void push(stack_t **stack, unsigned int line_number)
{
	stack_t *stack_copy = *stack;
	stack_t *head;

	head = malloc(sizeof(stack_t));
	if (head == NULL)
	{
		printf("Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	head->n = line_number;
	head->prev = NULL;
	head->next = NULL;
	if (stack_copy != NULL)
	{
		stack_copy->prev = head;
		head->next = stack_copy;
	}
	stack_copy = head;
	*stack = stack_copy;
}

/**
 * pall - function2 to print all items on a stack
 *
 * @stack: stack to print from
 * @line_number - line number in execution
 *
 * Return: nothing
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *stack_copy = *stack;
	while (stack_copy != NULL)
	{
		printf("%d\n", stack_copy->n);
		stack_copy = stack_copy->next;
	}
}

/**
 * pint - function3 to print item at the top of stack
 *
 * @stack: stack to print from
 * @line_number - line number in execution
 *
 * Return: nothing
 */

void pint(stack_t **stack, unsigned int line_number)
{
}

/**
 * pop - function4 to delete item at the top of stack
 *
 * @stack: stack to delete from
 * @line_number - line number in execution
 *
 * Return: nothing
 */

void pop(stack_t **stack, unsigned int line_number)
{
}
