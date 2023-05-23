/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:14:56 by amejia            #+#    #+#             */
/*   Updated: 2023/05/23 23:45:25 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	builtin_export_nargs(void)
{
	t_env	*env;

	env = g_state.envp;
	while (env != NULL)
	{
		ft_printf("declare -x %s=%s\n", env->name, env->args);
		env = env->next;
	}
	return (0);
}

int	checkarg_export(char *arg)
{
	char	*eq_sign;

	eq_sign = ft_strchr(arg, '=');
	if (eq_sign == arg)
		return (1);
	return (0);
}

int	not_vallid_id(char *txt)
{
	write (STDERR_FILENO, "Minishell: export: ", 19);
	write (STDERR_FILENO, txt, ft_strlen(txt));
	write (STDERR_FILENO, ": not a valid identifier \n", 27);
	return (1);
}

int	checkarg_export2(char *arg)
{
	long	find;

	find = (long)ft_strchr(arg, '-') + (long)ft_strchr(arg, '?')
		+ (long)ft_strchr(arg, '{') +  (long)ft_strchr(arg, '}')
		+ (long)ft_strchr(arg, '.') + (long)ft_strchr(arg, '*')
		+ (long)ft_strchr(arg, '#') + (long)ft_strchr(arg, '@');
	if (ft_isdigit(arg[0]))
		find++;
	if (find != 0)
		return (-1);
	if (find != 0)
		return (-1);
	return (0);
}

int	builtin_export(t_token *token)
{
	t_env	*env;
	int		ct;
	char	*str[3];

	ct = 1;
	if (token->args[ct] == NULL)
		return (builtin_export_nargs());
	while (token->args[ct] != NULL)
	{
		if (checkarg_export(token->args[ct]))
			return (not_vallid_id(token->args[ct]));
		export_if(token, str, ct);
		if (str[0] == NULL || str[1] == NULL)
			return (builtin_error());
		if (checkarg_export2(str[0]))
			return (free(str[0]), free(str[1]), not_vallid_id(token->args[ct]));
		env = ft_envnew(str[0], str[1]);
		if (env == NULL)
			return (builtin_error());
		ft_envset(env);
		free(str[0]);
		free(str[1]);
		ct++;
	}
	return (0);
}
