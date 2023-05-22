/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:30:48 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/22 15:06:37 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_prompt(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\r\n", 2);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_heredoc(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\r\n", 2);
	rl_on_new_line();
	g_state.status = S_STOP;
}

void	sig_hnd(int par)
{
	if (par == SIGINT && g_state.status == S_PROMPT)
		sig_prompt();
	if (par == SIGINT && g_state.status == S_HEREDOC)
		sig_heredoc();
}
