/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_redirect.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 13:57:33 by akramp        #+#    #+#                 */
/*   Updated: 2022/02/23 20:16:12 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>
#include <unistd.h> /*getcwd();*/

static const t_lookup	g_lookup_table[] = {
{0, &exit_token},
{1, &cd_token},
{2, &pwd_token},
{3, &env_token},
{4, &unset_token},
{5, &export_token},
{6, &echo_token}
};

int	token_cmp(char *token, const char *cmd)
{
	int			i;

	i = 0;
	if (!token || !cmd)
		return (-1);
	if (ft_strlen(token) > ft_strlen(cmd) || ft_strlen(token) < ft_strlen(cmd))
		return (1);
	while (token[i])
	{
		if (token[i] != cmd[i])
			return (1);
		i++;
	}
	return (0);
}

static int	access_check(t_magi *magi, char *token)
{
	char		*bin_token;

	bin_token = check_path_list(&magi->env, token);
	if (access(token, X_OK) == 0 \
		|| access(bin_token, X_OK) == 0)
	{
		free(bin_token);
		return (0);
	}
	free(bin_token);
	return (1);
}

int	redir_check(char *token, t_magi *magi)
{
	if (find_redir_type(token) != 0)
	{
		magi->redirect = 1;
		return (0);
	}
	return (1);
}

int	check_token(char *token, int argc, t_magi *magi)
{
	const char	*cmds[] = {"exit", "cd", "pwd", "env", "unset", "export", \
		"echo", "eva-00", "eva-01", "eva-02", "dmysys"};
	const int	size_of_cmds = sizeof(cmds) / sizeof(char*);
	int			i;

	i = 0;
	while (i < size_of_cmds)
	{
		if (token_cmp(token, cmds[i]) == 0)
		{
			if (argc > 1 && i > 6)
			{
				error_msg(EVA_ERROR, NULL);
				return (1);
			}
			return (0);
		}
		i++;
	}
	if (access_check(magi, token) == 0 || redir_check(token, magi) == 0)
		return (0);
	error_msg(CMD_ERROR, token);
	return (1);
}

void	checksies(t_list *token, t_magi *magi, int argc)
{
	const char	*cmds[] = {"exit", "cd", "pwd", "env", "unset", \
		"export", "echo"};
	const int	size_of_cmds = sizeof(cmds) / sizeof(char*);
	int			i;
	t_function	*func;

	i = 0;
	if (ft_strncmp((const char *)token->token, "eva", 3) == 0 \
		|| ft_strncmp((const char *)token->token, "dmysys", 6) == 0)
	{
		clear_screen();
		entry_plug(magi, token->token);
		return ;
	}
	while (i < size_of_cmds)
	{
		if (token_cmp(token->token, cmds[i]) == 0)
		{
			func = g_lookup_table[i].func;
			(*func)(token, magi, argc);
			return ;
		}
		i++;
	}
	bin_token(token, magi);
}
