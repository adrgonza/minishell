/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:52:32 by amejia            #+#    #+#             */
/*   Updated: 2023/05/16 22:39:57 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_state	g_state;

int	main(int argc, char **argv, char **envp)
{
	if (!ft_init(argc, argv, envp))
		return (0);
	if (DEBUG != 1)
		prompt();
	else
		prompt_debug();
	return (g_state.last_return);
}
