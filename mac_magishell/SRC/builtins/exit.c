/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 20:14:36 by epanholz      #+#    #+#                 */
/*   Updated: 2022/02/16 16:05:00 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"
#include <limits.h>
#include <unistd.h> /*getcwd();*/

static int	is_digit(char *token)
{
	int	i;

	i = 0;
	if (token[i] == '-')
		i++;
	while (token[i])
	{
		if (token[i] < '0' || token[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	calc_exit_code(int exit_status)
{
	if (exit_status > 255)
		return (exit_status % 256);
	if (exit_status < 0)
	{
		while (exit_status < -256)
			exit_status = exit_status + 256;
		exit_status = 256 + exit_status;
	}	
	return (exit_status);
}

void	exit_token(t_list *token, t_magi *magi, int argc)
{
	t_list	*current;

	if (magi->redirect == 1)
		dup2(magi->saved_stdout, 1);
	if (!token->next)
	{
		printf("exit\n");
		exit (0);
	}
	current = token->next;
	if (argc > 2 && is_digit(current->token) == 0)
	{
		error_msg(EXIT_ERR, NULL);
		magi->exit_status = 1;
		return ;
	}
	printf("exit\n");
	if (is_digit(current->token) == 1)
	{
		error_msg(NUM_ERR, current->token);
		exit (255);
	}
	if (argc == 2)
		magi->exit_status = calc_exit_code(ft_atoi(current->token));
	exit (magi->exit_status);
}
