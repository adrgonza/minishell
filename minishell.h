/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:54:00 by amejia            #+#    #+#             */
/*   Updated: 2023/03/14 13:55:48 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/wait.h>
# include <stdio.h>
# include "libft/libft.h"
# include <string.h>

int 	ft_execchar(char *command, char **envp);
char	**argv_generator(char *command);
int     argv_generator_ap(char *command, char lim, t_list **argv_args);
void	prompt(char **envp);


#endif
