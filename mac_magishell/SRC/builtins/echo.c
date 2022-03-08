/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/26 10:15:35 by akramp        #+#    #+#                 */
/*   Updated: 2022/01/08 14:35:57 by ubuntu        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

int	write_echo_pipes(char **argv)
{
	int		count;
	int		check;

	check = 0;
	count = 0;
	if (!(ft_strncmp(argv[1], "-n", 2)) && count == 0)
		check = 1;
	else
	{
		write(1, argv[1], ft_strlen(argv[1]));
		if (argv[2] != NULL)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
	return (check);
}

static void	write_echo(t_magi *magi, t_list *current)
{
	while (current)
	{
		write(1, current->token, ft_strlen(current->token));
		if (current->next != NULL)
			write(1, " ", 1);
		current = current->next;
	}
	if (magi->echo_n == 0)
		write(1, "\n", 1);
}

void	echo_token(t_list *token, t_magi	*magi, int argc)
{
	t_list	*current;

	if (magi->argv_pipes == NULL)
	{
		if (argc == 1)
		{
			write(1, "\n", 1);
			return ;
		}
		current = token->next;
		if (!ft_strncmp(current->token, "-n", 2) && argc == 2)
			return ;
		if (!ft_strncmp(current->token, "-n", 2) && argc > 2)
		{
			magi->echo_n = 1;
			current = current->next;
		}
		write_echo(magi, current);
	}
	else
		write_echo_pipes(magi->argv_pipes);
}
