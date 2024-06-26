/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:41:43 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/25 22:16:27 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signals.h"

void	ignore_process(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
}
void	quit_process(t_parser *parser)
{
	struct sigaction sig_quit;

	ft_memset(&sig_quit, 0, sizeof(sig_quit));
	sig_quit.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sig_quit, NULL);
}
void	handle_signals(t_parser *parser)
{
	struct sigaction sig_ignore;

	ft_memset(&sig_ignore, 0, sizeof(sig_ignore));
	sig_ignore.sa_handler = ignore_process;
	sigaction(SIGINT, &sig_ignore, NULL);
	// quit_process(parser);
	return ;
}