/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_functions_part2.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ubuntu <ubuntu@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/04 15:32:36 by ubuntu        #+#    #+#                 */
/*   Updated: 2022/02/12 10:46:18 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

char	*redir_file_name(t_list **head)
{
	t_list	*current;

	current = *head;
	while (current)
	{
		if (current->token[0] == '<' || current->token[0] == '>' )
		{
			current = current->next;
			if (!current)
			{
				error_msg(SYNTAX_ERR, "newline");
				break ;
			}
			return (current->token);
		}
		current = current->next;
	}
	return (NULL);
}

int	count_pip_type(t_list **head, int ret_on_first)
{
	t_list	*current;
	int		count;
	int		node_count;

	current = *head;
	count = 0;
	node_count = 0;
	if (!(count_env(*head) > 0))
		return (-1);
	while (current)
	{
		if (current->token[0] == '|')
			count++;
		if (ret_on_first == YES && count == 1)
			return (node_count);
		current = current->next;
		node_count++;
	}
	return (count);
}

void	fill_charp_with_list(t_list	*list, char **charp, char *bin_token)
{
	int		i;

	i = 0;
	while (list)
	{
		if (!list->token)
			break ;
		if (i == 0)
			charp[i] = ft_strdup(bin_token);
		else
			charp[i] = ft_strdup(list->token);
		i++;
		list = list->next;
	}
	free(bin_token);
	charp[i] = NULL;
}
