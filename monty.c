#define _GNU_SOURCE
#include "monty.h"

int main(int ac, char **av)
{
	char *line = NULL;
	FILE *monty_file;
	size_t n = 0;
	ssize_t line_no;

	check_args(ac);
	monty_file = fopen(av[1], "r");
	while ((line_no = getline(&line, &n, monty_file)) != -1)
	{
		line_no++;
		evaluate(line, line_no);
	}
	fclose(monty_file);
	free(line);
	return (0);
}
