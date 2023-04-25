#include "../minishell.h"

char *expand_variables(char *cmd)
{
	int i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '$' && cmd[i + 1] != ' ' && cmd[i + 1] != '\t')
		{
		}
	}
	return (cmd);
}
int p_check_quotes(char *command) /* cheks if there is an open quote, semicolon or '\' */
{
	int i;
	int count_q;
	int count_simple_q;

	count_q = 0;
	count_simple_q = 0;
	i = -1;
	while (command[++i])
	{
		if (command[i] == ';' && count_simple_q % 2 == 0 && count_q % 2 == 0)
			return (printf("syntax error near unexpected token `;'\n"), 0);
		if (command[i] == '\\' && count_simple_q % 2 == 0 && count_q % 2 == 0)
			return (printf("syntax error near unexpected token `\\'\n"), 0);
		if (command[i] == '"' && (count_simple_q % 2 == 0))
				count_q++;
		if (command[i] == '\'' && (count_q % 2 == 0))
				count_simple_q++;
	}
	if (count_q % 2 != 0 || count_simple_q % 2 != 0) /* checks if quotes nb is not pair */
		return (printf("Error, cierra las comillas!!\n"), 0);
	return (1);
}

