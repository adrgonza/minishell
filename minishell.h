/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:54:00 by amejia            #+#    #+#             */
/*   Updated: 2023/04/14 17:24:28 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_state {
	char	**envp;
	int		last_return;
}	t_state;

typedef struct s_token{
	char			type[10];
	char			**args;
	struct s_token	*last;
	struct s_token	*next;
}	t_token;

/* mix */
void	ft_tknadd_back(t_token **lst, t_token *new);
void	ft_tknadd_front(t_token **lst, t_token *new);
void	ft_tknclear(t_token **lst);
void	ft_tkndelone(t_token *lst);
t_token	*ft_tknlast(t_token *lst);
t_token	*ft_tknnew(char *type, char **args);
int		ft_tknsize(t_token *lst);
void	split_cpy(char ***dst, char **src);
void	prompt(char **envp);
int		ft_init(int argc, char **argv, char **envp);

/* parsing */

t_token	*parsing(char *command);


/* executing*/
void	ft_executer(t_token *ẗoken);
int		ft_exectkn(t_token *token);

/* declare global var*/
extern t_state g_state;

#endif
