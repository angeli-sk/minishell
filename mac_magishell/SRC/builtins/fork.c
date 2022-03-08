/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/12 15:52:19 by epanholz      #+#    #+#                 */
/*   Updated: 2022/02/23 21:53:21 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"
#include <limits.h>
#include <sys/wait.h>
#include <unistd.h> /*getcwd();*/

void	first_pipe(t_list *token, t_magi	*magi, int **fd)
{
	pipe(fd[0]);
	g_pid = fork();
	if (g_pid == -1)
	{
		error_msg(FORK_FAIL, NULL);
		exit(1);
	}
	if (g_pid == 0)
	{
		dup2(fd[0][WRITE], 1);
		close(fd[0][READ]);
		close(fd[0][WRITE]);
		exec(token, magi);
		exit(1);
	}
	signal_ing_int();
}

void	last_pipe(t_list *token, t_magi	*magi, int **fd)
{
	int		i;
	int		status;

	status = 0;
	i = count_pipes(magi->head) - 1;
	g_pid = fork();
	if (g_pid == 0)
	{
		dup2(fd[i][READ], STDIN_FILENO);
		close(fd[i][READ]);
		close(fd[i][WRITE]);
		exec(token, magi);
		exit(1);
	}
	signal_ing_int();
	close(fd[i][READ]);
	close(fd[i][WRITE]);
	while (1)
	{
		if (waitpid(-1, &status, WNOHANG) < 0)
			break ;
	}
}

void	inbetween_pipes(t_list *token, int **fd, int i, t_magi	*magi)
{
	const int	previous_command = i;
	const int	current_command = i + 1;

	g_pid = fork();
	if (g_pid == -1)
	{
		error_msg(FORK_FAIL, NULL);
		exit(1);
	}
	if (g_pid == 0)
	{
		dup2(fd[previous_command][READ], STDIN_FILENO);
		dup2(fd[current_command][WRITE], STDOUT_FILENO);
		close(fd[previous_command][READ]);
		close(fd[previous_command][WRITE]);
		close(fd[current_command][READ]);
		close(fd[current_command][WRITE]);
		exec(token, magi);
		exit(1);
	}
	signal_ing_int();
	close(fd[i][READ]);
	close(fd[i][WRITE]);
}

void	redirect_input_stream(t_magi *magi, char *end)
{
	int		i;
	int		fd[2];
	int		ret;

	i = 0;
	magi->heredoc = 1;
	pipe(fd);
	g_pid = fork();
	if (g_pid == -1)
	{
		error_msg(FORK_FAIL, NULL);
		exit(1);
	}
	if (g_pid == 0)
	{
		close(fd[0]);
		read_heredoc(fd[1], end);
		close(fd[1]);
		exit(0);
	}
	waitpid(g_pid, &ret, 0);
	redir_exit_status(magi, &ret);
	close(fd[1]);
	magi->heredoc_fd = fd[0];
	signal_int();
}

void	exec_subpros(t_magi	*magi, char **argv, int *err, int *ret)
{
	extern char	**environ;

	g_pid = fork();
	if (g_pid == -1)
	{
		error_msg(FORK_FAIL, NULL);
		exit(1);
	}
	if (g_pid == 0)
	{
		update_my_environ(magi);
		*err = execve(argv[0], argv, environ);
		exit (0);
	}
	if (*err == -1)
		exit (1);
	if (g_pid > 0)
	{
		signal_ing_int();
		waitpid(g_pid, ret, 0);
	}
}
