/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:31:16 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/22 15:20:19 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*inter_expansion(char *cmd, int i, int first)
{
	char	*expanded_cmd;
	char	*rest;
	int		nb;
	int		j;

	nb = g_state.last_return;
	j = 0;
	while (nb > 0 && j++ < 12)
		nb /= 10;
	expanded_cmd = ft_calloc(sizeof(char), ft_strlen(cmd) - 2 + j + 1);
	if (!expanded_cmd)
		return (malloc_fail_proc(), NULL);
	ft_strlcpy(expanded_cmd, cmd, ++i);
	expanded_cmd = ft_strjoin_s(expanded_cmd, "\"");
	rest = ft_itoa(g_state.last_return);
	expanded_cmd = ft_strjoin_s(expanded_cmd, rest);
	free(rest);
	expanded_cmd = ft_strjoin_s(expanded_cmd, "\"");
	rest = ft_substr(cmd, i + 1, ft_strlen(cmd) - i);
	expanded_cmd = ft_strjoin_s(expanded_cmd, rest);
	if (first)
		free(cmd);
	return (free(rest), expanded_cmd);
}

char	*expansion_tools2(char **splitted, t_env *data, char *xp_cmd)
{
	int	j;

	j = -1;
	while (splitted[++j])
	{
		if (j != 0 || data->args[0] == ' ')
			xp_cmd = ft_strjoin_s(xp_cmd, " ");
		xp_cmd = ft_strjoin_s(xp_cmd, "\"");
		xp_cmd = ft_strjoin_s(xp_cmd, splitted[j]);
		if (!splitted[j + 1] && (data->args[ft_strlen(data->args) - 1] == ' ' ))
			xp_cmd = ft_strjoin_s(xp_cmd, " ");
		xp_cmd = ft_strjoin_s(xp_cmd, "\"");
	}
	return (xp_cmd);
}

char	*expansion_tools(char *cmd, char *xp_cmd, int i, t_env *data)
{
	char	*var;
	char	**splitted;

	ft_strlcpy(xp_cmd, cmd, i++);
	if (data && data->args)
	{
		splitted = ft_split(data->args, ' ');
		if (!splitted[0])
			if (data->args[0] == ' ')
				xp_cmd = ft_strjoin_s(xp_cmd, " ");
		xp_cmd = expansion_tools2(splitted, data, xp_cmd);
		ft_free_split(splitted);
	}
	while (cmd[i] && cmd[i - 2] != '~' && (ft_isalnum(cmd[i]) || cmd[i] == '_'))
		i++;
	if (cmd[i - 2] == '~')
		i--;
	var = ft_substr(cmd, i, ft_strlen(cmd) - i + 1);
	xp_cmd = ft_strjoin_s(xp_cmd, var);
	free(var);
	return (xp_cmd);
}

char	*variable_expansion_tools(char *cmd, int *len, int i, char *var)
{
	*len = ++i;
	while (cmd[*len] && (ft_isalnum(cmd[*len]) || cmd[*len] == '_'))
		(*len)++;
	var = ft_substr(cmd, i, *len - i);
	return (var);
}

char	*variable_expansion(char *cmd, int i, int first)
{
	t_env	*data;
	char	*var;
	char	*expanded_cmd;
	int		len;
	int		args_len;

	var = NULL;
	if (cmd[i + 1] == '?')
		return (inter_expansion(cmd, i, first));
	var = variable_expansion_tools(cmd, &len, i++, var);
	data = ft_envfind(var);
	free(var);
	args_len = 0;
	if (!data || !data->args)
		len = 0;
	else
		args_len = ft_strlen(data->args);
	expanded_cmd = ft_calloc(1, (ft_strlen(cmd) + args_len - (len - i) + 3));
	if (!expanded_cmd)
		return (malloc_fail_proc(), NULL);
	expanded_cmd = expansion_tools(cmd, expanded_cmd, i, data);
	if (first || g_state.here_quote == 1)
		free(cmd);
	return (expanded_cmd);
}
