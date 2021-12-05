#include "monty.h"

/**
 * opcode_index - function1 to get the opcode index in an array
 *
 * @opcode: opcode to check for
 * @line_no: line number in execution
 *
 * Return: a data structure holding the index and a pointer location
 */
int opcode_index(char *opcode, unsigned int line_no)
{
	int i = 0, j = 0, s = 0, diff = 0;
	char *ops[8] = {"push", "pall", "pint", "pop", "swap", "add", "nop", NULL};
	int index;

	while (ops[i] != NULL)
	{
		j = 0;
		diff = 0;
		s = 0;
		while (ops[i][j] != '\0')
		{
			if (opcode[s] != ops[i][j])
			{
				diff++;
				break;
			}
			s++;
			j++;
		}

		if (diff == 0)
		{
			if (opcode[s + 1] != 32 && opcode[s + 1] != 9
				&& opcode[s + 1] != '\0')
				break;
			index = i;
			return (index);
		}
		i++;
	}
	printf("%d", line_no);
	write(2, "L", 1);
	/*write(2, line_no, strlen(line_no));*/
	write(2, ": unknown instruction ", 22);
	write(2, opcode, strlen(opcode));
	write(2, "\n", 1);
	free(opcode);
	exit(EXIT_FAILURE);
}

/**
 * push - function2 to push an integer to stack
 *
 * @stack: stack to be pushed to
 * @line_number: line number in execution
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
 * pall - function3 to print all items on a stack
 *
 * @stack: stack to print from
 * @line_number: line number in execution
 *
 * Return: nothing
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *stack_copy = *stack;
	unsigned int ln = line_number;

	while (stack_copy != NULL)
	{
		printf("%d\n", (stack_copy->n - 48) + (ln - ln));
		stack_copy = stack_copy->next;
	}
}

/**
 * pint - function4 to print item at the top of stack
 *
 * @stack: stack to print from
 * @line_number: line number in execution
 *
 * Return: nothing
 */
void pint(stack_t **stack, unsigned int line_number)
{
	stack_t *stack_copy = *stack;
	unsigned int ln = line_number;

	if (stack == NULL)
	{
		printf("L%d", ln);
		write(2, ": can't pint, stack empty\n", 26);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (stack_copy->n - 48));
}

/**
 * pop - function5 to delete item at the top of stack
 *
 * @stack: stack to delete from
 * @line_number: line number in execution
 *
 * Return: nothing
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *stack_copy = *stack;

	if (stack == NULL || stack_copy->n == 0)
	{
		printf("L%d", line_number);
		write(2, ": can't pop an empty stack\n", 27);
		exit(EXIT_FAILURE);
	}
	stack_copy->n = line_number;
	(*stack) = (*stack)->next;
	if ((*stack) != NULL)
		(*stack)->prev = NULL;
	free(stack_copy);
}
