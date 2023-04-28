/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:54:00 by amejia            #+#    #+#             */
/*   Updated: 2023/04/27 18:40:07 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef DEBUG
#  define DEBUG 0
# endif

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h> //change to mac on campus


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
	struct s_env	*last;
	struct s_env	*next;
}	t_env;

typedef struct s_state{
	t_env	*envp;
	int		last_return;
	int		exit;
}	t_state;

typedef struct s_token{
	int				type;
	char			**args;
	struct s_token	*last;
	struct s_token	*next;
}	t_token;

/* mix */
/*tkn*/
void	ft_tknadd_back(t_token **lst, t_token *new);
void	ft_tknadd_front(t_token **lst, t_token *new);
void	ft_tknclear(t_token **lst);
void	ft_tkndelone(t_token *lst);
t_token	*ft_tknlast(t_token *lst);
t_token	*ft_tknnew(int type, char **args);
int		ft_tknsize(t_token *lst);
void	split_cpy(char ***dst, char **src);
//void 	ft_print_tkn(char *cmd, int type, char **args);
void	ft_tknswap_last(t_token *token);
void	ft_tknswap_next(t_token *token);
void	ft_print_tkn(t_token *token);
void	ft_print_tkns(t_token *token);

/*env*/
void	ft_envadd_back(t_env **lst, t_env *new);
void	ft_envadd_front(t_env **lst, t_env *new);
void	ft_envclear(t_env **lst);
void	ft_envdelone(t_env *lst);
t_env	*ft_envlast(t_env *lst);
t_env 	*ft_envfind(char *name);
void 	ft_envunset(t_env *token);
void 	ft_envset(t_env *token);
t_env	*ft_envnew(char *name, char *args);
void 	ft_envprint(void);
int		ft_envsize(t_env *lst);
t_env	*env_split_to_list(char **env);
char	**env_list_to_split(t_env *token);

/*prompt*/
void	prompt(void);
void	prompt_debug(void);
void	here_doc_prompt(int *pip, t_token *token);
int		ft_init(int argc, char **argv, char **envp);

/* parsing */
t_token	*parsing(char *command);
char	**get_cmd_args(char *command, int i);
int		get_type(char *command, int i);
int		next_arg(int type, char *cmd, int i);
int		count_letters(char *cmd, int i);
int		check_stdout(char *command);
int		check_stdin(char *command);
int		count_words(char *cmd, int i);
int		redict_word_count(char *cmd, int j);
char	**get_args(int	type, char *command, int i);
char	*check_quotes(char *cmd);
char	**get_redict_args(char *cmd, int i, int type);
void	ft_free_args(char **args);
void	command_double_quotes(char *cmd, int *i, char *arg, int *k);
void	command_simple_quotes(char *cmd, int *i, char *arg, int *k);


/* executing*/
void	ft_executer(t_token *ẗoken);
int		ft_exectkn(t_token *token);
int		pipe_counter(t_token *token);
int		**pipe_generator(int npipes);
void	pipe_con_before_forks(t_token *token, int **pip, int n_pipes);
void 	pipe_left_greatgreat(int *pipe, t_token *token);
t_token	*redirect_order_sort(t_token *token);

/* built ins*/
int		check_builtin(t_token *token, int ct2);
void	ft_builtinexec(t_token *token);
int		builtin_cd(t_token *token);
int		builtin_export(t_token *token);
int		builtin_unset(t_token *token);
int		builtin_pwd();
int		builtin_error();
int 	builtin_exit(t_token *token);
void 	malloc_fail_proc(void);
t_token *redirect_check(t_token *token);


/* declare global var*/
extern t_state g_state;

#endif
