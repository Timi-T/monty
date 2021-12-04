#include "monty.h"

/**
 * swap - function1 to swap the two elements at the top of the stack
 *
 * @stack: stack to swap from
 * @line_number - line number in execution
 *
 * Return: nothing
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *stack_copy = *stack;
	int a, b;

	if (stack == NULL || stack_copy->next == NULL)
	{
		printf("L%d", line_number);
		write(2, ": can't swap, stack too short\n", 30);
		exit(EXIT_FAILURE);
	}
	a = stack_copy->n;
	stack_copy = stack_copy->next;
	b = stack_copy->n;
	stack_copy->n = a;
	(*stack)->n = b;
}

/**
 * add - function2 to add the two elements at the top of the stack
 *
 * @stack: stack to add from
 * @line_number - line number in execution
 *
 * Return: nothing
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *stack_copy = *stack;
	int a, b;

	if (stack == NULL || stack_copy->next == NULL)
	{
		printf("L%d", line_number);
		write(2, ": can't add, stack too short\n", 30);
		exit(EXIT_FAILURE);
	}
	a = stack_copy->n;
	stack_copy = stack_copy->next;
	b = stack_copy->n;
	pop(stack, line_number);
	(*stack)->n = (a - 48) + (b - 48);
}
