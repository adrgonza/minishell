/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tkn2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:01 by amejia            #+#    #+#             */
/*   Updated: 2023/04/24 15:21:32 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_tknnew(int type, char **args)
{
	t_token	*to_return;

	to_return = (t_token *)malloc(sizeof(t_token));
	if (to_return == 0)
		return (0);
	to_return->type = type;
	if (args != NULL)
		split_cpy(&(to_return->args), args);
	else
		to_return->args = NULL;
	to_return->next = NULL;
	to_return->last = NULL;
	return (to_return);
}

int	ft_tknsize(t_token *lst)
{
	int	counter;

	if (lst == NULL)
		return (0);
	counter = 1;
	while (lst->next != NULL)
	{
		if (lst->next != NULL)
			lst = lst-> next;
		counter++;
	}
	return (counter);
}

void	split_cpy(char ***dst, char **src)
{
	unsigned int	ct;

	ct = 0;
	while (src[ct] != NULL)
		ct++;
	*dst = ft_calloc(ct +1, sizeof(char *));
	if (*dst == NULL)
		return ;
	ct = 0;
	while (src[ct] != NULL)
	{
		(*dst)[ct] = ft_strdup(src[ct]);
		if ((*dst)[ct] == NULL)
		{
			ft_free_split(*dst);
			return ;
		}
		ct++;
	}
}
