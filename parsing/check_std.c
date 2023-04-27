#include "../minishell.h"

int check_stdin(char *command)
{
	int i;

	i = -1;
	while (command[++i])
		if (command[i] == '<')
			return 0;
	return 1;
}

int check_stdout(char *command)
{
	int i;

	i = -1;
	while (command[++i])
		if (command[i] == '>')
			return 0;
	return 1;
}
