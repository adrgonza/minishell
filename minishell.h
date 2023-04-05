/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:54:00 by amejia            #+#    #+#             */
/*   Updated: 2023/04/05 18:47:49 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include "libft/libft.h"
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_state {
	char	**envp;
	char	*pwd;
	int		last_return;
} t_state;

typedef struct s_token{
	char			type[10];
	char			**args;
	struct s_token	*next;
} t_token;

/* mix */

void	prompt(char **envp);
int ft_init(int argc, char **argv, char **envp);

/* parsing */

t_token	*ft_parsing(char *command);

/* execute */
int 	ft_execchar(char *command, char **envp);
char	**argv_generator(char *command);
int     argv_generator_ap(char *command, char lim, t_list **argv_args);
t_state	g_state;

#endif


