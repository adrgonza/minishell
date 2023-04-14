/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:40:13 by amejia            #+#    #+#             */
/*   Updated: 2023/04/07 00:20:28 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state g_state;

int main(int argc, char **argv, char **envp)
{
	t_token *token;
	
	ft_init(argc, argv, envp);
	token = NULL;
	ft_tknadd_back(&token,ft_tknnew("COMMAND",ft_split("ls -l", ' ')));
	ft_tknadd_back(&token,ft_tknnew("COMMAND",ft_split("cat -e", ' ')));
	ft_exectkn(token);
	return(0)
}