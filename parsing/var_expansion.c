/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:31:16 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/09 02:12:47 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_s(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		return (0);
	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	return (str);
}

char	*inter_expansion(char *cmd, int i)
{
	char	*expanded_cmd;
	char	*rest;
	int		nb;
	int		j;

	nb = g_state.last_return;
	j = 0;
	while (nb > 0)
	{
		nb /= 10;
		j++;
	}
	expanded_cmd = ft_calloc(sizeof(char), strlen(cmd) - 2 + j + 1);
	if (!expanded_cmd)
		return (NULL);
	ft_strlcpy(expanded_cmd, cmd, ++i);
	expanded_cmd = ft_strjoin_s(expanded_cmd, "\"");
	rest = ft_itoa(nb);
	expanded_cmd = ft_strjoin_s(expanded_cmd, rest);
	free(rest);
	expanded_cmd = ft_strjoin_s(expanded_cmd, "\"");
	rest = ft_substr(cmd, i + 1, ft_strlen(cmd) - i);
	expanded_cmd = ft_strjoin_s(expanded_cmd, rest);
	free(rest);
	return (expanded_cmd);
}

char	*variable_expansion(char *cmd, int i, int first)
{
	t_env	*data;
	char	*var;
	char	*expanded_cmd;
	int		var_len;
	int		args_len;

	if (cmd[i + 1] == '?')
		return (inter_expansion(cmd, i));
	var_len = ++i;
	while (cmd[var_len] && ft_isalnum(cmd[var_len]))
		var_len++;
	var = ft_substr(cmd, i, var_len - i);
	data = ft_envfind(var);
	free(var);
	if (!data)
		var_len = 0;
	else
		args_len = ft_strlen(data->args);
	expanded_cmd = ft_calloc(sizeof(char), (ft_strlen(cmd) + args_len - (var_len - i) + 3));
	if (!expanded_cmd)
		return (NULL);
	ft_strlcpy(expanded_cmd, cmd, i++);
	expanded_cmd = ft_strjoin_s(expanded_cmd, "\"");
	if (data)
		expanded_cmd = ft_strjoin_s(expanded_cmd, data->args);
	expanded_cmd = ft_strjoin_s(expanded_cmd, "\"");
	while (cmd[i] && ft_isalnum(cmd[i]))
		i++;
	var = ft_substr(cmd, i, ft_strlen(cmd) - i + 1);
	expanded_cmd = ft_strjoin_s(expanded_cmd, var);
	free(var);
	if (first)
		free(cmd);
	return (expanded_cmd);
}
