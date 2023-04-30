/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tkn3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 23:12:27 by amejia            #+#    #+#             */
/*   Updated: 2023/04/29 23:40:09 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_tkn(t_token *token)
{
	int	i;

	i = 0;
	ft_printf("\n----------------------------\n");
	ft_printf("   type ==> {%d}   \n", token->type);
	if (token->type == 4)
	{
		ft_printf("   args(%d) ==> {[%s]}   \n", i, token->args);
	}
	else if (token->args != NULL)
	{
		while (token->args[i])
		{
			ft_printf("   args(%d) ==> {[%s]}   \n", i, token->args[i]);
			i++;
		}
		ft_printf("   args(%d) ==> {[%s]}   \n", i, token->args[i]);
	}
	ft_printf("----------------------------\n\n");
}

void	ft_print_tkns(t_token *token)
{
	int	i;

	if (token == NULL)
		return ;
	i = 0;
	while (token->last != NULL)
	{
		token = token->last;
		i--;
	}
	while (token != NULL)
	{
		ft_printf("Token #%i\n", i);
		ft_print_tkn(token);
		token = token->next;
		i++;
	}
}
