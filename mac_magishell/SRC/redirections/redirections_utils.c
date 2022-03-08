/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/12 15:59:20 by epanholz      #+#    #+#                 */
/*   Updated: 2022/02/23 20:26:43 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

void	redir_exit_status(t_magi *magi, int *ret)
{
	if (WIFEXITED(ret))
		magi->exit_status = WEXITSTATUS(ret);
	if (WIFSIGNALED(ret))
		magi->exit_status = 1;
}

void	read_heredoc(int herdoc_fd, char *end)
{
	char	*line;

	signal_heredoc();
	line = NULL;
	while (true)
	{
		line = readline("> ");
		if (ft_strcmp(line, end) == 0 || line == NULL)
		{
			free(line);
			exit(0);
		}
		write(herdoc_fd, line, ft_strlen(line));
		write(herdoc_fd, "\n", 1);
		free(line);
	}
}

int	check_if_file_exists(const char *file, t_magi *magi)
{
	if (access(file, F_OK) == 0)
		return (0);
	else
	{
		magi->redir_error = -1;
		error_msg(LS_ERR, (char *)file);
	}
	return (1);
}

int	find_redir_type(char *redir)
{
	if (redir[0] == '<' && !redir[1])
		return (REDIR_INPUT);
	else if (redir[0] == '>' && !redir[1])
		return (REDIR_OUT);
	else if (redir[0] == '>' && redir[1] && redir[1] == '>')
		return (REDIR_OUT_APP);
	else if (redir[0] == '<' && redir[1] && redir[1] == '<')
		return (READ_INPUT);
	return (0);
}
