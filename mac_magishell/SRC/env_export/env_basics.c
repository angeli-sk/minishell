/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_basics.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 11:05:25 by akramp        #+#    #+#                 */
/*   Updated: 2022/02/23 16:15:02 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> /*int chdir(const char *path);*/
#include "../magi.h"

static void	shlvl_changer(t_magi *magi, int i)
{
	int		lvl;
	char	*lv;
	char	*str;

	lvl = 0;
	lvl = ft_atoi(&environ[i][6]) + 1;
	str = malloc(sizeof(char) * ft_strlen(environ[i]) + 2);
	if (str == NULL)
	{
		error_msg(MALLOC_FAIL, NULL);
		exit(EXIT_FAILURE);
	}
	ft_memcpy(str, environ[i], 6);
	str[ft_strlen(environ[i]) - 3] = '=';
	str[ft_strlen(environ[i]) - 2] = '\0';
	lv = ft_itoa(lvl);
	if (ft_strlen(lv) != ft_strlen(&environ[i][6]))
		str[ft_strlen(environ[i]) - 1] = '\0';
	add_token(0, ft_strjoin(str, lv), &magi->env);
	free (str);
	free (lv);
}

void	env_init(t_magi *magi)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "OLDPWD=", 7) == 0)
			add_token(0, ft_strdup("OLDPWD"), &magi->env);
		else if (ft_strncmp(environ[i], "SHLVL=", 6) == 0)
			shlvl_changer(magi, i);
		else
			add_token(0, ft_strdup(environ[i]), &magi->env);
		i++;
	}
}

char	*get_home_env(t_magi *magi)
{
	return (findlist(&magi->env, "HOME=", 0, NULL) + 5);
}

void	env(t_magi *magi)
{
	printlist(&magi->env, 1);
}

int	count_env(t_list *current)
{
	int	i;

	i = 0;
	while (current)
	{
		if (!current->token)
			break ;
		i++;
		current = current->next;
	}
	return (i);
}
