/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:37:06 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/09 18:38:18 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//mallocs frees
//signals
//parsing errors
//norminette

t_token	*parsing(char *cmd)
{
	t_token	*token = NULL;
	char	**args;
	int		type;
	int		i;

	cmd = check_quotes(cmd);
	if (!cmd)
		return (token);
	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		type = get_type(cmd, i);
		args = get_args(type, cmd, i);
		ft_tknadd_back(&token, ft_tknnew(type, args));
		ft_free_args(args);
		i = next_arg(type, cmd, i);
	}
	if (check_stdout(token))
		ft_tknadd_back(&token, ft_tknnew(T_STDOUT, NULL));
	reordenate_tokens(&token);
	if (check_stdin(token))
		ft_tknadd_front(&token, ft_tknnew(T_STDIN, NULL));
	return (token);
}
//system("leaks -q minishell | head -5 | tail -1 ; echo \"\n\"-----------leaks------------\"\n\"");
//system("echo \"\n\"-----------leaks------------\"\n\" && leaks -q minishell | head -5 | tail -1 ");
