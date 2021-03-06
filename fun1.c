#include "monty.h"

/**
 * check_args - function1 to check number of arguments
 *
 * @ac: number of arguments
 *
 * Return: nothing
 */
void check_args(int ac)
{
	if (ac != 2)
	{
		write(2, "USAGE: monty file\n", 18);
		exit(EXIT_FAILURE);
	}
}

/**
 * open_file - function2 to open a file
 *
 * @path: file path
 * @mode: mode to open file in
 *
 * Return: pointer to file stream
 */
FILE *open_file(char *path, char *mode)
{
	FILE *monty_file;

	monty_file = fopen(path, mode);
	if (monty_file == NULL)
	{
		write(2, "Error: Can't open file ", 23);
		write(2, path, strlen(path));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	return (monty_file);
}

/**
 * evaluate - function3 to check line for instructions
 *
 * @line: line to check for instructions
 * @line_no: line number
 *
 * Return: nothing
 */
void evaluate(char *line, int line_no)
{
	char *opcode;
	int instr_index, integer, done = 0;
	int s = 0, i = 0, begin = 0;

	opcode = malloc((strlen(line) + 100) * sizeof(char));
	while (line[s] != '\0')
	{
		if (line[s] != 32 && line[s] != 9 && begin == 0)
			begin = 1;
		if (begin == 1)
		{
			while (line[s] != 32 && line[s] != 9 && line[s] != '\0')
			{
				opcode[i] = line[s];
				s++;
				i++;
			}
			opcode[i] = '\0';
			done = 1;
			break;
		}
		if (done == 1)
			break;
		s++;
	}
	instr_index = opcode_index(opcode, line_no);
	if (instr_index != 6)
	{
		integer = check_int(line, line_no, s, instr_index);
		execute_instr(opcode, instr_index, line_no, integer);
	}
}

/**
 * check_int - function4 to check line for integer after instruction
 *
 * @line: line to check for integer
 * @pointer_location: location of pointer after instruction
 * @line_no: line number of instruction
 * @func_index: index of the opcode used
 *
 * Return: integer
 */
int check_int(char *line, int line_no, int pointer_location, int func_index)
{
	char *line_copy = line;
	int p = pointer_location, number, i = 0;

	while (line_copy[i] != '\0')
	{
		if (p != -1)
		{
			i++;
			p--;
		}
		else
		{
			if (line_copy[i] != 32)
			{
				number = (int)(line_copy[i]);
				return (number);
			}
			i++;
		}
	}
	if (func_index == 0)
	{
		printf("Line %d->", line_no);
		write(2, "Error: No integer to operate on\n", 31);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * execute_instr - function5 to execute instruction
 *
 * @opcode: opcode if instruction
 * @func_index: index of function to be executed
 * @line_number: line number of the instruction
 * @integer: number to be entered into the stack
 *
 * Return: nothing
 */
void execute_instr(char *opcode, int func_index, unsigned int line_number,
		   int integer)
{
	instruction_t *exec;

	void (*func_ptr[7])(stack_t**, unsigned int) = {
		push, pall, pint, pop, swap, add};

	exec = malloc(sizeof(instruction_t) + (1 * sizeof(char *)));
	if (exec == NULL)
	{
		exit(EXIT_FAILURE);
	}
	exec->opcode = opcode;
	exec->f = func_ptr[func_index];
	if (func_index == 0)
		exec->f(&stack, integer);
	else
		exec->f(&stack, line_number);
}
