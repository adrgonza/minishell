/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:37:06 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/16 20:44:02 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//heredoc comillas
// syntax erorres

t_token	*parsing(char *cmd)
{
	t_token	*token = NULL;
	char	**args;
	int		type;
	int		i;

	cmd = check_quotes(cmd, 0);
	if (!cmd)
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
		ft_free_args(args);
		i = next_arg(type, cmd, i);
	}
	if (check_stdout(token))
		ft_tknadd_back(&token, ft_tknnew(T_STDOUT, NULL));
	if (check_stdin(token))
		ft_tknadd_front(&token, ft_tknnew(T_STDIN, NULL));
	reordenate_tokens(&token);
	//ft_print_tkns(token);
	return (token);
}
