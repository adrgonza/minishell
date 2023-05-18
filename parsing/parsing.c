/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:37:06 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/18 20:35:01 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//parsing errors
//mallocs protections
//leaks
//norminette

char	*parsing_tools(char **cmd)
{
	g_state.here_quote = 0;
	*cmd = check_quotes(*cmd);
	if (!(*cmd))
		return (NULL);
	return (*cmd);
}

void leaks()
{
	system("leaks -q minishell");
}

t_token	*parsing(char *cmd)
{
	t_token	*token;
	char	**args;
	int		type;
	int		i;

	//leaks();
	token = NULL;
	if (!parsing_tools(&cmd))
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		if (i == ft_strlen(cmd))
			return (NULL);
		type = get_type(cmd, i);
		args = get_args(type, cmd, i);
		ft_tknadd_back(&token, ft_tknnew(type, args));
		i = next_arg(type, cmd, i, args);
	}
	if (check_stdout(token))
		ft_tknadd_back(&token, ft_tknnew(T_STDOUT, NULL));
	if (check_stdin(token))
		ft_tknadd_front(&token, ft_tknnew(T_STDIN, NULL));
	//leaks();
	return (reordenate_tokens(&token), token);
}
