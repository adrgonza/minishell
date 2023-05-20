/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:30:48 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/20 00:01:13 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	sig_hnd(int sig)
{
    rl_replace_line("", 0);
    rl_on_new_line();
    write(1 , "\r\n", 2);
    rl_on_new_line();
    rl_redisplay();
}
