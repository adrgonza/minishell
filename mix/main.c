/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:52:32 by amejia            #+#    #+#             */
/*   Updated: 2023/04/23 14:54:12 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_state g_state;

void leaks()
{
	system("leaks -q minishell");
}

int main(int argc, char **argv, char **envp)
{
	//atexit(leaks);
	if (!ft_init(argc, argv, envp)) /* inicializate args */
		return (0);
	prompt(envp); /* execute prompt */
	return (0);
}

