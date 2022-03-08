/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/21 14:06:53 by akramp        #+#    #+#                 */
/*   Updated: 2022/02/23 16:16:38 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"
#include <stdlib.h>

void	printlist(t_list **head, int x)
{
	t_list	*current;

	current = *head;
	while (current)
	{
		if (!current->token)
			return ;
		if (x == 0 || x == 2)
		{
			if (x == 2)
				write(1, "declare -x ", 11);
			write(1, current->token, ft_strlen(current->token));
			write(1, "\n", 1);
		}
		if (ft_strchr(current->token, '=') != NULL && x == 1)
		{
			write(1, current->token, ft_strlen(current->token));
			write(1, "\n", 1);
		}
		current = current->next;
	}
}

int	countlist(t_list **head)
{
	t_list	*current;
	int		count;

	current = *head;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	*tokenmaker(char *env_to_change, char *pwd)
{
	char	*new_token;

	new_token = malloc
		(sizeof(char ) * (ft_strlen(pwd) + ft_strlen(env_to_change)) + 1);
	if (new_token == NULL)
	{
		error_msg(MALLOC_FAIL, NULL);
		exit(EXIT_FAILURE);
	}
	ft_memcpy(new_token, env_to_change, ft_strlen(env_to_change));
	ft_memcpy(new_token + ft_strlen(env_to_change), pwd, ft_strlen(pwd));
	ft_memcpy(new_token
		+ (ft_strlen(pwd) + ft_strlen(env_to_change)), "\0", 1);
	return (new_token);
}

void	del_elem(t_list **head, t_list *to_delete)
{
	t_list	*previous;
	t_list	*iter;

	iter = *head;
	previous = NULL;
	while (iter != to_delete)
	{
		previous = iter;
		iter = iter->next;
	}
	if (!iter)
		return ;
	if (!previous)
		*head = to_delete->next;
	else
		previous->next = to_delete->next;
	free(to_delete->token);
	free(to_delete);
}

int	find_red_type(t_list **head)
{
	t_list	*current;

	current = *head;
	while (current)
	{
		if (current->token[0] == '<' && !current->token[1])
			return (REDIR_INPUT);
		else if (current->token[0] == '>' && !current->token[1])
			return (REDIR_OUT);
		else if (current->token[0] == '>' && current->token[1] \
			&& current->token[1] == '>')
			return (REDIR_OUT_APP);
		else if (current->token[0] == '<' && current->token[1] \
			&& current->token[1] == '<')
			return (READ_INPUT);
		current = current->next;
	}
	return (0);
}
