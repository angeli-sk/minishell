/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_tokens.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/25 14:57:37 by epanholz      #+#    #+#                 */
/*   Updated: 2022/02/16 15:30:02 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"
#include <limits.h>
#include <unistd.h> /*getcwd();*/

void	env_token(t_list *token, t_magi	*magi, int argc)
{
	if (ft_mod(token->token, "env") == 0 && argc == 1)
	{
		env(magi);
		magi->exit_status = 0;
	}
	else
	{
		token = token->next;
		magi->exit_status = 127;
		error_msg(ENV_ERR, token->token);
	}
}

void	pwd_token(void)
{
	char	cwd[PATH_MAX];

	(void)
	getcwd(cwd, sizeof(cwd));
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
}

void	cd_token(t_list *token, t_magi	*magi, int argc)
{
	t_list	*current;

	current = token;
	if (ft_mod(token->token, "cd") == 0 && argc <= 2)
	{
		if (argc != 1)
		{
			current = token->next;
			if (ft_mod("cd", current->token) == 0)
			{
				magi->exit_status = 127;
				error_msg(CD_ERR2, current->token);
				return ;
			}
		}
		cd(current->token, magi);
	}
	else
	{
		magi->exit_status = 127;
		error_msg(CD_ERR, NULL);
	}
}
