/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list_part2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ubuntu <ubuntu@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/04 14:48:36 by ubuntu        #+#    #+#                 */
/*   Updated: 2022/02/23 16:16:56 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

int	type_helper(t_magi *magi, char *token)
{
	int	ret;

	ret = 4;
	if (magi->quotes == 1)
		ret = QUOTED_ARG;
	else if (token[0] == '|')
		ret = PIPE;
	else if (token[0] == '<' || token[0] == '>')
		ret = REDIRECTION;
	return (ret);
}

void	add_token_x(int type, char *token, t_magi *magi)
{
	t_list	*new_node;
	t_list	*current;

	current = magi->head;
	type = type_helper(magi, token);
	if (current->token == NULL)
		*current = (t_list){type, token, NULL};
	else
	{
		new_node = (t_list *)malloc(sizeof(t_list));
		if (new_node == NULL)
		{
			error_msg(MALLOC_FAIL, NULL);
			exit(EXIT_FAILURE);
		}
		*new_node = (t_list){type, token, NULL};
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}
