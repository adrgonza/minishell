#include "../minishell.h"

void	prompt(char **envp)
{
	char	*command;
	t_token *tokens;

	command = (char *)1;
	while (command != NULL)
	{
		command = readline("(>\'-\')> ");
		if (command == NULL)
			break ;
		add_history(command);
		tokens = ft_parsing(command);
		ft_executer(tokens);
		ft_free_tokens(tokens);
		ft_free_command(command);
	}
}
