/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 21:39:18 by epanholz      #+#    #+#                 */
/*   Updated: 2022/02/23 21:44:31 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

/*
rl_on_new_line
	--> we have moved onto a new (empty) line
rl_replace_line
	--> Clear the previous text (Replace the contents of rl_line_buffer with text.)
rl_redisplay
	--> Change what's displayed on the screen to reflect the current contents of
	rl_line_buffer
*/

void	handle_signal(int sig)
{
	int	*status;

	status = NULL;
	if (waitpid(g_pid, status, WNOHANG) == 0)
		kill(g_pid, SIGTERM);
	else if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_heredoc(int sig)
{
	if (sig == SIGINT)
		exit (sig);
}
