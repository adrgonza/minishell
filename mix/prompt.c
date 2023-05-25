/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:12:35 by amejia            #+#    #+#             */
/*   Updated: 2023/05/23 22:58:53 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prompt_chooser(void)
{
	static int	mode;

	if (g_state.last_return == 0)
	{
		mode++;
		if (mode % 5 == 1)
			return ("\033[0;35m(>^.^)> \033[0;37m");
		if (mode % 5 == 2)
			return ("\033[0;35m<(^.^<) \033[0;37m");
		if (mode % 5 == 3)
			return ("\033[0;35m<(^.^)> \033[0;37m");
		if (mode % 5 == 4)
			return ("\033[0;35m^(^.^)^ \033[0;37m");
		if (mode % 5 == 0)
			return ("\033[0;35mv(^.^)v \033[0;37m");
	}
	return ("\033[0;31m(>x.x)> \033[0;37m");
}

void	prompt(void)
{
	char	*command;
	t_token	*tokens;

	command = (char *)1;
	while (command != NULL)
	{
		g_state.status = S_PROMPT;
		command = readline(prompt_chooser());
		if (command == NULL)
			break ;
		tokens = parsing(command);
		if (tokens)
		{
			ft_executer(tokens);
			ft_tknclear(&tokens);
		}
		if (ft_strlen(command) > 0)
			add_history(command);
		free(command);
	}
}

void	prompt_debug(void)
{
	char	*command;
	t_token	*tokens;
	t_token	*last;
	//char	*prompt;
	int		w;

	w = 0;
	command = (char *)1;
	while (command != NULL)
	{
		command = ft_strdup("echo 1 | <tm_out");
		if (command == NULL)
			break ;
		tokens = parsing(command);
		if (tokens)
		{
			ft_print_tkns(tokens);
			ft_executer(tokens);
			ft_tknclear(&tokens);
		}
		free(command);
		command = NULL;
		w++;
	}
}
void    prompt_linux(void)
{
    char    *command;
    t_token *tokens;
    t_token *last;
    char    *prompt;
    //signal(SIGINT, sig_hnd);
    //signal(SIGQUIT, sig_hnd);
    command = (char *)1;
    while (command != NULL)
    {
        //ft_printf("%d\n",g_state.last_return);
        command = get_next_line(STDIN_FILENO);
        if(command == NULL)
            break ;
        if (ft_strlen(command) == 0)
            continue ;
        if (ft_strchr(command, '\n') > 0)
            ft_delete_char(ft_strchr(command, '\n'));
        if (!command)
        {
            if (isatty(STDIN_FILENO))
            write(2, "exit\n", 6);
            exit (g_state.last_return);
        }
        if (command == NULL)
            break ;
        add_history(command);
        tokens = parsing(command);
        if (tokens)
        {
            //ft_print_tkns(tokens);
            ft_executer(tokens);
            ft_tknclear(&tokens);
        }
        free(command);
    }
}

