/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:52:32 by amejia            #+#    #+#             */
/*   Updated: 2023/04/24 14:54:20 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_state g_state;

int main(int argc, char **argv, char **envp)
{
	if (!ft_init(argc, argv, envp)) /* inicializate args */
		return (0);
	prompt(envp); /* execute prompt */
	return (0);
}

