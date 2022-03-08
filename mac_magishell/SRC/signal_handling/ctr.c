/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ctr.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/12 16:01:47 by epanholz      #+#    #+#                 */
/*   Updated: 2022/02/12 16:01:58 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

void	ctr_handle(void)
{
	struct termios	attributes;
	struct termios	saved;

	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}

/*tcsetattr(0, TCSANOW, &magi->saved)*/
/*use reset to reset terminal settings*/