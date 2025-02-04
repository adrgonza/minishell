/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:08:57 by amejia            #+#    #+#             */
/*   Updated: 2023/05/25 17:14:34 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_echosetfd(t_token *token, int *fd)
{
	if (g_state.am_child == 0)
	{
		*fd = set_pipeoutput(token, NULL);
		if (*fd == -1)
			return (1);
	}
	else
		*fd = STDOUT_FILENO;
	return (0);
}

int	option_checker(char **original_args, int ct)
{
	int		ct2;
	char	*old;

	ct2 = 1;
	while (original_args[ct][ct2] == 'n')
		ct2++;
	if (original_args[ct][ct2] != '\0')
		return (0);
	old = original_args[ct];
	ct2 = -1;
	while (original_args[ct + ++ct2] != 0)
		original_args[ct + ct2] = original_args[ct + ct2 + 1];
	free(old);
	return (1);
}

int	args_options(char **original_args)
{
	int	mode;
	int	modeb;
	int	ct;

	mode = 0;
	ct = 1;
	while (original_args[ct] != NULL)
	{
		if (original_args[ct][0] == '-')
		{
			modeb = option_checker(original_args, ct);
			if (modeb == 1)
				mode = ft_max(modeb, mode);
			else
				ct++;
		}
		else
			break ;
	}
	return (mode);
}

int	builtin_echo(t_token *token)
{
	int	ct;
	int	mode;
	int	fd;

	mode = 0;
	ct = 1;
	if (builtin_echosetfd(token, &fd) == 1)
		return (1);
	if (token->args != NULL)
	{
		mode = args_options(token->args);
		while (token->args[ct] != NULL)
		{
			write(fd, token->args[ct], ft_strlen(token->args[ct]));
			if (token->args[++ct] != NULL)
				write(fd, " ", 1);
		}
	}
	if (mode == 0)
		write(fd, "\n", 1);
	return (0);
}

int	builtin_exit(t_token *token)
{
	int	a;

	a = 0;
	write(STDERR_FILENO, "exit\n", 5);
	if (token->args[1] != NULL && check_valid(token->args[1]))
	{
		a = 255;
		write(STDERR_FILENO, "Minishell: exit: numeric argument needed\n", 42);
	}
	else if (token->args[1] != NULL)
		a = ft_atoi(token->args[1]);
	if (token->args[1] != NULL && token->args[2] != NULL && a != 255)
	{
		write(STDERR_FILENO, "Minishell: Exit: too many arguments\n", 30);
		return (1);
	}
	ft_first_tkn(&token);
	ft_tknclear(&token);
	ft_envclear(&g_state.envp);
	free(g_state.home_dir);
	free(g_state.id);
	clear_history();
	return (exit (a), a);
}
