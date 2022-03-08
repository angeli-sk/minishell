/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: elisabeth <elisabeth@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/04 14:31:26 by elisabeth     #+#    #+#                 */
/*   Updated: 2022/02/23 21:42:12 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

void	signal_main(void)
{
	struct sigaction	sigterm_action;

	sigemptyset(&sigterm_action.sa_mask);
	sigterm_action.sa_flags = 0;
	sigterm_action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigterm_action, NULL);
	sigterm_action.sa_flags = 0;
	sigterm_action.sa_handler = &handle_signal;
	sigaction(SIGINT, &sigterm_action, NULL);
}

void	signal_int(void)
{
	struct sigaction	sigterm_action;

	sigterm_action.sa_flags = 0;
	sigterm_action.sa_handler = &handle_signal;
	sigaction(SIGINT, &sigterm_action, NULL);
}

void	signal_ing_int(void)
{
	struct sigaction	sigterm_action;

	sigterm_action.sa_flags = 0;
	sigterm_action.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sigterm_action, NULL);
}

void	signal_heredoc(void)
{
	struct sigaction	sigterm_action;

	sigterm_action.sa_flags = 0;
	sigterm_action.sa_handler = &handle_heredoc;
	sigaction(SIGINT, &sigterm_action, NULL);
}
