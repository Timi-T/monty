#include "monty.h"
/**
 * main - Entry point
 *
 * @ac: number of arguements in stdin
 * @av: array of arguments in stdin
 *
 * Return: nothing
 */
int main(int ac, char **av)
{
	char *line = NULL;
	FILE *monty_file;
	size_t n = 0;
	int line_no;

	check_args(ac);
	monty_file = open_file(av[1], "r");
	while ((getline(&line, &n, monty_file)) != -1)
	{
		/*printf("Line: %s\n", line);*/
		line_no++;
		evaluate(line, line_no);
	}
	fclose(monty_file);
	free(line);
	return (0);
}
