/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections_fd_func.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: elisabeth <elisabeth@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/04 14:02:46 by elisabeth     #+#    #+#                 */
/*   Updated: 2022/02/23 20:28:59 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

void	fd_redir_output(t_list **head)
{
	int		fd_out;
	t_list	*current;

	fd_out = -1;
	current = *head;
	while (current)
	{
		if (current->type == REDIR_OUT_APP)
			fd_out = open(current->token, O_CREAT | O_RDWR | O_APPEND, 0666);
		else if (current->type == REDIR_OUT)
			fd_out = open(current->token, O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (current->next && fd_out != -1)
			close(fd_out);
		current = current->next;
	}
	if (fd_out != -1)
		dup2(fd_out, STDOUT_FILENO);
}

void	fd_redir_input(t_list **head, t_magi *magi)
{
	int		fd;
	t_list	*current;

	fd = -1;
	current = *head;
	while (current)
	{
		if (current->type == REDIR_INPUT)
			fd = open(current->token, O_RDWR);
		else if (current->type == READ_INPUT)
			fd = magi->heredoc_fd;
		if (current->next && fd != -1)
			close(fd);
		current = current->next;
	}
	if (fd != -1)
		dup2(fd, STDIN_FILENO);
}
