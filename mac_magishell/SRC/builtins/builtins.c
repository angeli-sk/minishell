/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 13:16:32 by akramp        #+#    #+#                 */
/*   Updated: 2022/02/16 15:39:55 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"
#include <string.h> /*char *strerror(int errnum);*/
#include <errno.h> /*int errno;*/

void	change_env_cd(char *str, char *pwd, char **new_pwd, t_list **head)
{
	if (ft_strncmp(str, "OLDPWD=", 7) == 0)
		findlist(head, "OLDPWD=", 1, pwd);
	else if (ft_strncmp(str, "PWD=", 4) == 0)
	{
		*new_pwd = getcwd(pwd, sizeof(pwd));
		findlist(head, "PWD=", 1, *new_pwd);
		free (*new_pwd);
	}
}

void	update_env_cd(t_list **head, char *str, char *pwd)
{
	t_list	*current;
	char	*new_pwd;

	current = *head;
	new_pwd = NULL;
	while (current)
	{
		if (ft_strncmp(current->token, "OLDPWD", 6) == 0
			&& ft_strlen(current->token) == 6)
		{
			findlist(head, "OLDPWD=", 1, pwd);
			return ;
		}
		else if (ft_strncmp(current->token, str, ft_strlen(str)) == 0)
		{
			change_env_cd(str, pwd, &new_pwd, head);
			return ;
		}
		current = current->next;
	}
}

int	ft_mod(const char *str, const char *cmp)
{
	int			i;

	i = 0;
	if (!str || !cmp)
		return (-1);
	while (cmp[i])
	{
		if (str[i] != cmp[i])
			return (1);
		i++;
	}
	return (0);
}

int	cd(const char *path, t_magi *magi)
{
	int	err_msg;

	err_msg = 0;
	magi->old_pwd = NULL;
	magi->old_pwd = getcwd(magi->old_pwd, sizeof(magi->old_pwd));
	if (ft_mod("cd", (char *)path) == 0)
		chdir(get_home_env(magi));
	else
		err_msg = chdir(path);
	if (err_msg == -1)
	{
		magi->exit_status = 1;
		error_msg(CD_ERR1, (char *)path);
	}
	else
	{
		update_env_cd(&magi->env, "OLDPWD=", magi->old_pwd);
		update_env_cd(&magi->env, "PWD=", NULL);
		magi->exit_status = 0;
	}
	free (magi->old_pwd);
	return (errno);
}

void	unset_token(t_list *token, t_magi	*magi, int argc)
{
	t_list	*current;

	current = token;
	if (argc == 1)
		return ;
	else
	{
		current = current->next;
		while (current)
		{
			if (!current->token)
				break ;
			findlist(&magi->env, current->token, 2, NULL);
			current = current->next;
		}
	}
}
