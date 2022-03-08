/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   findlist.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Angi <Angi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/19 12:51:55 by Angi          #+#    #+#                 */
/*   Updated: 2022/01/08 14:35:57 by ubuntu        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

static char	*findlist_if(t_list *current, char *pwd)
{
	free(current->token);
	current->token = tokenmaker("OLDPWD=", pwd);
	return (NULL);
}

static void	find_list_del_1(t_list *current, char *str, char *pwd)
{
	free(current->token);
	current->token = tokenmaker(str, pwd);
}

char	*findlist(t_list **head, char *str, int del, char *pwd)
{
	t_list	*current;

	current = *head;
	while (current && ft_strncmp(current->token, str, ft_strlen(str)) != 0)
	{
		if (ft_strncmp(current->token, "OLDPWD", 6) == 0
			&& ft_strlen(current->token) == 6
			&& ft_strncmp(str, "OLDPWD=", 7) == 0)
			return (findlist_if(current, pwd));
		current = current->next;
	}
	if (current == NULL)
		return (NULL);
	if (del > 0)
	{
		if (del == 1)
			find_list_del_1(current, str, pwd);
		if (del == 2 && (ft_strlen(str) == \
			chrfinder(current->token, '=', 0)))
			del_elem(head, current);
		return (NULL);
	}
	return (current->token);
}
