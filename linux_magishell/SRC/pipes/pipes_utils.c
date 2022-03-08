/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elisabeth <elisabeth@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/04 15:00:22 by elisabeth     #+#    #+#                 */
/*   Updated: 2022/02/23 20:29:25 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"
#include <unistd.h> /*pid*/
#include <sys/types.h>
#include <sys/wait.h>

int	count_pipes(t_list	*current)
{
	int	i;

	i = 0;
	while (current)
	{
		if (current->type == PIPE)
			i++;
		current = current->next;
	}
	return (i);
}

int	**fd_pipe_maker(t_magi	*magi)
{
	t_list	*current;
	int		pipes_num;
	int		i;
	int		**fd;

	current = magi->head;
	pipes_num = count_pipes(current);
	i = 0;
	fd = malloc (sizeof(int *) * pipes_num);
	if (fd == NULL)
	{
		error_msg(MALLOC_FAIL, NULL);
		exit(EXIT_FAILURE);
	}
	while (i < pipes_num)
	{
		fd[i] = malloc (sizeof(int) * 2);
		if (fd[i] == NULL)
		{
			error_msg(MALLOC_FAIL, NULL);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (fd);
}

void	free_fd(int **fd, t_list	*current)
{
	int		pipes_num;
	int		i;

	i = 0;
	pipes_num = count_pipes(current);
	while (i < pipes_num)
	{
		free (fd[i]);
		i++;
	}
	free (fd);
}

void	exec(t_list *token, t_magi	*magi)
{
	int	argc;

	argc = countlist(&(token));
	if (magi->redirect != 1 && argc != -1)
		checksies(token, magi, argc);
	else if (redir_fill_lists(&magi->head, magi) == 0 && argc != -1)
	{
		handle_fd(magi, DUPLICATE);
		remove_redir(&token);
		fd_redir_output(&magi->out_head);
		fd_redir_input(&magi->in_head, magi);
		checksies(token, magi, countlist(&(token)));
		handle_fd(magi, RESET);
		magi->redirect = 0;
		reset_list(&magi->out_head);
		reset_list(&magi->in_head);
		reset_list(&magi->read_input);
	}
}

t_list	*split_list(t_list *orig_head, t_list *new_head, t_magi *magi)
{
	t_list	*current;

	current = orig_head;
	while (current)
	{
		if (current->type == REDIRECTION)
			magi->redirect = 1;
		if (current->type == PIPE)
			return (current->next);
		add_token(current->type, ft_strdup(current->token), &new_head);
		current = current->next;
	}
	return (NULL);
}
