#include "../minishell.h"

int check_stdin(t_token *token)
{
while (token)
	{
		if (token->type == T_LESS)
			return (0);
		token = token->next;
	}
	return (1);
}

int check_stdout(t_token *token)
{
	while (token)
	{
		if (token->type == T_GREAT)
			return (0);
		token = token->next;
	}
	return (1);
}
