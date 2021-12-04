#include "monty.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av)
{
	char *line = NULL;
	FILE *monty_file;
	size_t n = 0;
	int line_no = 0;

	check_args(ac);
	monty_file = open_file(av[1], "r");
	while (getline(&line, &n, monty_file) != -1)
	{
		line_no++;
		evaluate(line, line_no);
	}
	fclose(monty_file);
	free(line);
	return (0);
}
