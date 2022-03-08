/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 15:31:40 by akramp        #+#    #+#                 */
/*   Updated: 2022/02/23 16:17:38 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

void	print_list(t_list **head)
{
	t_list	*current;

	current = *head;
	while (current)
	{
		printf("[%d] [%s]\n", current->type, current->token);
		current = current->next;
	}
}

void	free_list(t_list **head)
{
	t_list	*temp;
	t_list	*current;

	current = *head;
	while (current)
	{
		if (!current->token)
			return ;
		temp = current->next;
		free(current->token);
		free(current);
		current = temp;
	}
}

void	reset_list(t_list **head)
{
	t_list	*temp;
	t_list	*current;

	current = *head;
	while (current)
	{
		if (!current->token)
			return ;
		temp = current->next;
		free(current->token);
		free(current);
		current = temp;
	}
	*head = NULL;
	make_head(head);
}

void	make_head(t_list **head)
{
	t_list	*new_head;

	new_head = (t_list *)malloc(sizeof(t_list));
	if (new_head == NULL)
	{
		error_msg(MALLOC_FAIL, NULL);
		exit(EXIT_FAILURE);
	}
	*new_head = (t_list){0, NULL, NULL};
	*head = new_head;
}

void	add_token(int type, char *token, t_list **head)
{
	t_list	*new_node;
	t_list	*current;

	current = *head;
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
