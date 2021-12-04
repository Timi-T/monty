#include "monty.h"

/*global declaration of stack linked list and line number*/
stack_t *stack = NULL;
unsigned int line_no = 0;

/*push function to push an integer to stack*/
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
        head->n = line_no;
        head->prev = NULL;
        head->next = NULL;
        if (stack_copy != NULL)
        {
                stack_copy->prev = head;
                head->next = stack_copy;
        }                                                                                                       stack_copy = head;                                                                                      *stack = stack_copy;                                                                            }

/*pall function to print all items in the stack*/
void pall(stack_t **stack, unsigned int line_number)
{
        stack_t *stack_copy = *stack;
        while (stack_copy != NULL)
        {
                printf("%d\n", stack_copy->n);
                stack_copy = stack_copy->next;
        }
}

void pint(stack_t **stack, unsigned int line_number)
{
}

void pop(stack_t **stack, unsigned int line_number)
{
}

void swap(stack_t **stack, unsigned int line_number)
{
}

void add(stack_t **stack, unsigned int line_number)
{
}

void nop(stack_t **stack, unsigned int line_number)
{
}

/*function to check number of arguments*/
void check_args(int ac)
{
        if (ac != 2)
        {
                write(2, "USAGE: monty file\n", 18);
                exit(EXIT_FAILURE);
        }
}

/*function to open a file where the name is the file path*/
FILE *open_file(char *name, char *mode)
{
        FILE *monty;

        monty = fopen(name, mode);
        if (monty == NULL)
        {
                write(2, "Error: Can't open file ", 23);
                write(2, name, strlen(name));
                write(2, "\n", 1);
                exit(EXIT_FAILURE);
        }
        return (monty);
}

/*function to check for an integer after an instruction has been found in a line*/
/*this function is called in the  checkline function*/
/*line is the line that is being checked*/
/*pointer_location is where the pointer is after seeing an instruction*/
int check_int(char *line, int pointer_location)
{
        char *line_copy = line;
        int p = pointer_location, number;
        char line_str = (char)line_no;

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

/*function to execute an instruction*/
/*opcode - instruction*/
/*function_index - position of function in the array of function names*/
/*line_number - integer pushed to stack*/
void execute_instr(char *opcode, int func_index, unsigned int line_number)
{
        instruction_t *exec;

        /*declaration of an array of function pointers*/
        /*the function pointers are in the same order as the array of function names*/
        void (*func_ptr[7])(stack_t**, unsigned int) =
        {push, pall, pint, pop, swap, add, nop};

        exec = malloc(sizeof(instruction_t));
        if (exec == NULL)
                exit(EXIT_FAILURE);
        exec->opcode = opcode;
        /*assigning the instruction_t function pointer to the function pointer in the array*/
        exec->f = func_ptr[func_index];
        /*passing the arguments to the function pointer*/
        exec->f(&stack, line_number);
}

/*function to check each line for instructions*/
int check_line(char *line)
{
        char *line_copy = line;
        /*definition of array for function names*/
        char *instr[8] = {
                                "push",
                                "pall",
                                "pint",
                                "pop",
                                "swap",
                                "add",
                                "nop",
                                NULL
                        };
        char **instr_copy = instr;
        int i = 0, j = 0, l = 0, l2 = 0, diff = 0, number;
        char *command = NULL;
        instruction_t *exec;

        exec = malloc(sizeof(instruction_t));
        /*looping through the array of function names*/
        while (instr_copy[i] != NULL)
        {
                l = 0;
                l2 = 0;
                /*loopign through the line*/
                while (line_copy[l] != '\0')
                {
                        diff = 0;
                        j = 0;
                        l = l2;
                        /*looping tru each function name and comparing with line characters*/
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
                                number = check_int(line_copy, l);
                                command = instr_copy[i];
                                execute_instr(command, i, line_no);
                        }
                        l2++;
                }
                i++;
        }
        return (line_no);
}

int main(int ac, char **av)
{
        char *file_name;
        int fd, i = 0;
        char *line = NULL;
        char ch;
        FILE *monty;
        ssize_t no_of_bytes;
        size_t n = 0;

        check_args(ac);
        monty = open_file(av[1], "r");
        while (no_of_bytes = getline(&line, &n, monty) != -1)
        {
                line_no++;
                /*printf("line %d: %s", line_no, line);*/
                line_no = check_line(line);
        }
        fclose(monty);
        free(line);
        return (0);
}
