/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:52:32 by amejia            #+#    #+#             */
/*   Updated: 2023/04/05 17:32:53 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_init(int argc, char **argv, char **envp)
{
	if (argc != 1) /* check there is only an argument */
		return (0);
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	if (!ft_init(argc, argv, envp)) /* inicializate args */
		return (0);
	prompt(envp); /* execute prompt */
	return (0);
}
