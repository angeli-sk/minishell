/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bin_token.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/25 14:54:41 by epanholz      #+#    #+#                 */
/*   Updated: 2022/02/23 16:11:38 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"
#include <limits.h>
#include <sys/wait.h>
#include <unistd.h> /*getcwd();*/

static void	free_charp(char **charp)
{
	int	i;

	i = 0;
	while (charp[i] != NULL)
	{
		free(charp[i]);
		i++;
	}
	free(charp);
}

static char	*bin_token_fill(t_magi	*magi, t_list	**current, char	**argv)
{
	char	*bin_token;

	bin_token = check_path_list(&magi->env, (*current)->token);
	if (bin_token == NULL)
		bin_token = ft_strdup((*current)->token);
	fill_charp_with_list(*current, argv, bin_token);
	return (bin_token);
}

static int	malloc_argv(t_list *token, char	***argv)
{
	if (count_env(token) > 0)
		*argv = malloc (sizeof (char *) * (count_env(token) + 1));
	else
		return (-1);
	if (*argv == NULL)
	{
		error_msg(MALLOC_FAIL, NULL);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	bin_token(t_list *token, t_magi	*magi)
{
	int		err;
	int		ret;
	t_list	**current;
	char	**argv;
	char	*bin_token;

	argv = NULL;
	ret = 0;
	if (malloc_argv(token, &argv) == -1)
		return ;
	current = &token;
	bin_token = bin_token_fill(magi, current, argv);
	err = 0;
	exec_subpros(magi, argv, &err, &ret);
	if (WIFEXITED(ret))
		magi->exit_status = WEXITSTATUS(ret);
	if (WIFSIGNALED(ret))
		magi->exit_status = (128 + WTERMSIG(ret));
	if (WIFSIGNALED(ret) && WTERMSIG(ret) == SIGSEGV)
		write(STDERR_FILENO, "Segmentation fault", 19);
	free_charp(argv);
	signal_int();
}
