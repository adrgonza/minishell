/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:37:06 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/09 02:15:25 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	leaks()
{
	system("leaks -q minishell");
}

t_token	*parsing(char *cmd)
{
	t_token	*token = NULL;
	char	**args;
	int		type;
	int		i;

	cmd = check_quotes(cmd); /* checks if there is any open quote and expand variables */
	if (!cmd)
		return (token);
	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t')) /* jump spaces */
			i++;
		type = get_type(cmd, i); /* get the type  */
		args = get_args(type, cmd, i); /* get the argumments */
		ft_tknadd_back(&token, ft_tknnew(type, args)); /* put values in the list */
		ft_free_args(args); /* free argumments */
		i = next_arg(type, cmd, i); /* jump to the next argument */
	}
	if (check_stdout(token)) /* Checks if there is a '>' */
		ft_tknadd_back(&token, ft_tknnew(T_STDOUT, NULL));
	reordenate_tokens(&token); /* reordenate tokens if it is necesary */
	if (check_stdin(token)) /* Checks if there is a '<' */
		ft_tknadd_front(&token, ft_tknnew(T_STDIN, NULL));
	return (token);
}



//system("leaks -q minishell | head -5 | tail -1 ; echo \"\n\"-----------leaks------------\"\n\"");
//system("echo \"\n\"-----------leaks------------\"\n\" && leaks -q minishell | head -5 | tail -1 ");
