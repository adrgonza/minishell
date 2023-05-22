/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:04:31 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/22 15:16:22 by adrgonza         ###   ########.fr       */
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
		return (malloc_fail_proc(), NULL);
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

char	*expansion_tools_tilde(char *cmd, char *xp_cmd, int i, t_env *data)
{
	char	*var;
	char	**splitted;

	if (cmd[i] && cmd[i] == '~' && i > 0)
		i--;
	ft_strlcpy(xp_cmd, cmd, ++i);
	xp_cmd = ft_strjoin_s(xp_cmd, " ");
	if (data && data->args)
	{
		splitted = ft_split(data->args, ' ');
		if (!splitted[0])
			if (data->args[0] == ' ')
				xp_cmd = ft_strjoin_s(xp_cmd, " ");
		xp_cmd = expansion_tools2(splitted, data, xp_cmd);
		ft_free_split(splitted);
	}
	while (cmd[i] && (ft_isalnum(cmd[i])
			|| cmd[i] == '_') && cmd[i - 2] && cmd[i - 2] != '~')
		i++;
	var = ft_substr(cmd, i + 1, ft_strlen(cmd) - i + 1);
	xp_cmd = ft_strjoin_s(xp_cmd, var);
	free(var);
	return (xp_cmd);
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
		return (malloc_fail_proc(), NULL);
	expanded_cmd = expansion_tools_tilde(cmd, expanded_cmd, i, data);
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

char	*ft_strjoin_s(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		return (0);
	str = (char *)ft_calloc(sizeof(*s1), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (malloc_fail_proc(), NULL);
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
