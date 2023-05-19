/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:04:31 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/19 01:07:09 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**arrayjoin(char **array1, char **array2)
{
	char	**aux;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (array1[i++])
		;
	while (array2[j++])
		;
	aux = ft_calloc(sizeof(char *), (j + i + 1));
	if (!aux)
		return (NULL);
	i = -1;
	while (array1[++i])
		aux[i] = ft_strdup(array1[i]);
	j = 0;
	while (array2[j])
		aux[i++] = ft_strdup(array2[j++]);
	i = -1;
	ft_free_split(array1);
	return (aux);
}

int	check_pipes_cmd(t_token *token)
{
	int	cmd;
	int	pipe;

	pipe = 1;
	cmd = 0;
	while (token->next)
	{
		if (token->type == T_COMMAND)
		{
			cmd = 1;
			pipe = 1;
		}
		if (token->type == T_PIPE)
		{
			if (cmd == 0)
				return (0);
			cmd = 0;
			pipe = 0;
		}
		token = token->next;
	}
	if (pipe == 0)
		return (0);
	return (1);
}

int	check_parsing_errors(char cmd, int s_qte, int d_qte)
{
	if (cmd == ';' && s_qte % 2 == 0 && d_qte % 2 == 0)
		return (ft_putstr_fd("syntax error near unexpected token `;'\n", 2),
			g_state.last_return = 0, 0);
	if (cmd == '\\' && s_qte % 2 == 0 && d_qte % 2 == 0)
		return (ft_putstr_fd("syntax error near unexpected token `\\'\n", 2),
			g_state.last_return = 0, 0);
	return (1);
}

char	*expand_tilde(char *cmd, int i, int first)
{
	char	*expanded_cmd;
	t_env	*data;
	int		args_len;

	data = ft_envfind("HOME");
		args_len = 0;
	if (data || data->args)
		args_len = ft_strlen(data->args);
	expanded_cmd = ft_calloc(1, (ft_strlen(cmd) + args_len) + 3);
	if (!expanded_cmd)
		return (NULL);
	expanded_cmd = expansion_tools(cmd, expanded_cmd, ++i, data);
	if (first)
		free(cmd);
	return (expanded_cmd);
}

char	*remove_quotes(char *cmd, int first)
{
	char	*str;

	g_state.here_quote = 0;
	if (!cmd || ft_strlen(cmd) < 4)
		return (cmd);
	str = ft_strtrim(cmd, "\"");
	if (first == 1)
		free(cmd);
	return (str);
}
