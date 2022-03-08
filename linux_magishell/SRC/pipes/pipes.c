/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/10 12:45:49 by akramp        #+#    #+#                 */
/*   Updated: 2022/02/23 20:54:06 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"
#include <unistd.h> /*pid*/
#include <sys/types.h>
#include <sys/wait.h>

void	forkie_boi(t_magi	*magi, int **fd, t_list *current, t_list *temp)
{
	int		i;

	i = 0;
	magi->redirect = 0;
	while (current)
	{
		magi->redirect = 0;
		current = split_list(current, temp, magi);
		if (current == NULL)
		{
			last_pipe(temp, magi, fd);
			free_list(&temp);
			return ;
		}
		pipe(fd[i + 1]);
		inbetween_pipes(temp, fd, i, magi);
		reset_list(&temp);
		i++;
	}
}

void	pipes(t_magi	*magi)
{
	t_list	*current;
	t_list	*temp;
	int		**fd;

	fd = fd_pipe_maker(magi);
	current = NULL;
	temp = NULL;
	make_head(&temp);
	magi->redirect = 0;
	current = split_list(magi->head, temp, magi);
	first_pipe(temp, magi, fd);
	if (current == NULL)
	{
		free_fd(fd, magi->head);
		free_list(&temp);
		return ;
	}
	reset_list(&temp);
	forkie_boi(magi, fd, current, temp);
	free_fd(fd, magi->head);
	signal_int();
}
