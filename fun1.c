#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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
 * @@mode: mode to open file in
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
 * check_line - function3 to check line for instructions
 *
 * @line: line to check for instructions
 * @line_no: line number
 *
 * Return: line number
 */
int check_line(char *line, int line_no)
{
	char *line_copy = line, *instruction = NULL;
	char *instr[8] = {"push", "pall", "pint", "pop", "swap",
				"add", "nop", NULL};
	char **instr_copy = instr;
	int i = 0, j = 0, l = 0, l2 = 0, diff = 0, integer;

	while (instr_copy[i] != NULL)
	{
		l = 0;
		l2 = 0;
		while (line_copy[l] != '\0')
		{
			diff = 0;
			j = 0;
			l = l2;
			while (instr_copy[i][j] != '\0')
			{
				if (instr_copy[i][j] != line_copy[l])
				{
					diff++;
					break;
				}
				l++;
				j++;
			}
			if (diff == 0)
			{
				integer = check_int(line_copy, l, line_no);
				instruction = instr_copy[i];
				execute_instr(instruction, i, integer);
			}
			l2++;
		}
		i++;
	}
	return (line_no);
}

/**
 * check_int - function4 to check line for integer after instruction
 *
 * @line: line to check for integer
 * @pointer_location: location of pointer after instruction
 *
 * Return: integer
 */

int check_int(char *line, int pointer_location, int line_no)
{
	char *line_copy = line;
	int p = pointer_location, number;

	while (p != -1)
	{
		*line_copy++;
		p--;
	}
	while (*line_copy != '\0')
	{
		if (*line_copy != 32)
		{
			number = (int)(*line_copy);
			return (number);
		}
		*line_copy++;
	}
	write(2, "Error: No integer to operate on", 31);
	exit(EXIT_FAILURE);
}

/**
 * execute_instr - function5 to execute instruction
 *
 * @opcode: opcode if instruction
 * @func_index: index of function to be executed
 * @line_number: 
 *
 * Return: nothing
 */
void execute_instr(char *opcode, int func_index, unsigned int line_number)
{
	instruction_t *exec;

	void (*func_ptr[7])(stack_t**, unsigned int) =
	{push, pall, pint, pop, swap, add, nop};

	exec = malloc(sizeof(instruction_t));
	if (exec == NULL)
		exit(EXIT_FAILURE);
	exec->opcode = opcode;
	exec->f = func_ptr[func_index];
	exec->f(&stack, line_number);
	free(exec);
}
