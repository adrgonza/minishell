/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:54:00 by amejia            #+#    #+#             */
/*   Updated: 2023/04/21 16:13:39 by amejia           ###   ########.fr       */
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


# define	T_STDOUT		1
# define	T_STDIN			2
# define	T_COMMAND		3
# define	T_PIPE			4
# define	T_SEMICOLON		5
# define	T_LESS 			6
# define	T_LESSLESS		7
# define	T_GREAT			8
# define	T_GREATGREAT	9

typedef struct s_env{
	char			*name;
	char			*args;
	struct s_token	*last;
	struct s_token	*next;
}	t_env;

typedef struct s_state {
	t_env	*envp;
	int		last_return;
}	t_state;

typedef struct s_token{
	int				type;
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
t_token	*ft_tknnew(int type, char **args);
int		ft_tknsize(t_token *lst);
void	split_cpy(char ***dst, char **src);
void	ft_envadd_back(t_env **lst, t_env *new);
void	ft_envadd_front(t_env **lst, t_env *new);
void	ft_envclear(t_env **lst);
void	ft_envdelone(t_env *lst);
t_env	*ft_envlast(t_env *lst);
t_env 	*ft_envfind(t_env *token, char *name);
void 	ft_unsetkn(t_token *token);
void 	ft_settoken(t_token *token);
t_env	*ft_envnew(char *name, char *args);
int	ft_envsize(t_env *lst);
t_env *env_split_to_list(char **env);
char **env_list_to_split(t_env *token);

void	prompt(char **envp);
int		ft_init(int argc, char **argv, char **envp);
void	here_doc_prompt(int *pip, t_token *token);
/* parsing */

t_token	*parsing(char *command);
int		p_get_type(char *command, int i);
char	**get_cmd_args(char *command, int i);
int		count_letters(char *cmd, int i);
int		count_words(char *cmd, int i);
void 	ft_free_args(char **args);

/* executing*/
void	ft_executer(t_token *ẗoken);
int		ft_exectkn(t_token *token);
int		pipe_counter(t_token *token);
int		**pipe_generator(int npipes);
void	pipe_con_before_forks(t_token *token, int **pip, int n_pipes);
void 	pipe_left_greatgreat(int *pipe, t_token *token);

/* declare global var*/
extern t_state g_state;

#endif
