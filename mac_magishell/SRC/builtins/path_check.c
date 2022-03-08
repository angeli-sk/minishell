/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 13:05:31 by akramp        #+#    #+#                 */
/*   Updated: 2022/02/21 15:45:43 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

static char	*go_thru_env_to_find_path(t_list **head)
{
	t_list	*current;

	current = *head;
	while (current)
	{
		if (ft_mod(current->token, "PATH=") == 0)
			return (current->token);
		current = current->next;
	}
	return (NULL);
}

static void	free_splitted_str(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free (path);
}

static char	*check_access(char	**path, char	*test, char	*temp)
{
	free (test);
	if (access(temp, X_OK) == 0)
	{
		free_splitted_str(path);
		return (temp);
	}
	free (temp);
	return (NULL);
}

static void	quote_rm_path(char	**path)
{
	if (chrfinder(path[0], '"', 0) == 0 && \
		chrfinder(path[0], '"', 1) == (ft_strlen(path[0]) - 4))
	{
		remove_chr(&path[0], chrfinder(path[0], '"', 0));
		remove_chr(&path[0], chrfinder(path[0], '"', 1));
	}
}

char	*check_path_list(t_list **head, char *command)
{
	int		i;
	char	*str;
	char	**path;
	char	*test;
	char	*temp;

	str = go_thru_env_to_find_path(head);
	if (str == NULL)
		return (NULL);
	i = 0;
	path = ft_split(str, ':');
	test = ft_strjoin(&path[i][5], "/");
	temp = ft_strjoin(test, command);
	quote_rm_path(&temp);
	while (path[i])
	{
		if (check_access(path, test, temp) != NULL)
			return (temp);
		test = ft_strjoin(path[i], "/");
		temp = ft_strjoin(test, command);
		i++;
	}
	free_splitted_str(path);
	return (NULL);
}

//export PATH=/Users/akramp/Codam/4-MINISHELL/gitver/d1/lol
