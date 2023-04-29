/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:52:32 by amejia            #+#    #+#             */
/*   Updated: 2023/04/28 16:39:47 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_state g_state;

int main(int argc, char **argv, char **envp)
{
	if (!ft_init(argc, argv, envp)) /* inicializate args */
		return (0);
	if (DEBUG != 1)
		prompt(); /* execute prompt */
	else
		prompt();
	return (0);
}

