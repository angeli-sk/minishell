/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 10:14:56 by akramp        #+#    #+#                 */
/*   Updated: 2022/03/08 13:25:57 by ubuntu        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

int	find_replace_exp(t_list	**head, char *env, char *str)
{
	t_list	*current;

	current = *head;
	env[chrfinder(env, '=', 0)] = '\0';
	while (current)
	{
		if (ft_strncmp(current->token, env, ft_strlen(env)) == 0)
		{
			if (chrfinder(env, '=', 0) == chrfinder(current->token, '=', 0))
			{
				if (chrfinder(str, '=', 0) == ft_strlen(str))
					return (1);
				free(current->token);
				current->token = tokenmaker("", str);
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

int	chrfinder(const char *str, char c, int start)
{
	int	i;

	i = start;
	if (i > ft_strlen(str))
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
		{
			if (i == start && i + 1 == ft_strlen(str))
				return (i + 1);
			return (i);
		}
		i++;
	}
	return (i);
}

static void	export_token_argc_2_if_valid(t_list	*current, int i, char **temp, \
	char **env_token)
{
	if ((current->token)[i] == '=' && i > 0 && \
		(current->token)[i - 1] == '$')
	{
		error_msg(EXP_ERR, current->token);
		(*env_token) = ft_substr(current->token, 0, i);
		return ;
	}
	(*temp) = malloc(sizeof(char) * (ft_strlen(current->token) + 3));
	if ((*temp) == NULL)
	{
		error_msg(MALLOC_FAIL, NULL);
		exit(EXIT_FAILURE);
	}
	ft_memcpy((*temp), current->token, i + 1);
	(*temp)[i + 1] = '\"';
	ft_memcpy(&(*temp)[i + 2], &current->token[i + 1], \
		ft_strlen(current->token) - (i + 1));
	(*temp)[ft_strlen(current->token) + 1] = '\"';
	(*temp)[ft_strlen(current->token) + 2] = '\0';
	free (current->token);
	current->token = (*temp);
	(*env_token) = ft_substr(current->token, 0, i);
}

int	export_token_argc_2(t_list	*current, int i, char **temp, \
	char **env_token)
{
	i = chrfinder(current->token, '=', 0);
	if (i != ft_strlen(current->token) && \
		!((current->token)[i + 1] == '=') \
			&& !((current->token)[i] == '=' && i == 0))
		export_token_argc_2_if_valid(current, i, temp, env_token);
	else
	{
		if ((i == ft_strlen(current->token) && \
		(current->token)[i - 1] == '=') || (i != ft_strlen(current->token) && \
		(current->token)[i + 1] == ' ') || (i != ft_strlen(current->token) && \
		(current->token)[i + 1] == '=') || ((current->token)[i] == '=' && \
		i == 0))
		{
			error_msg(ENV_ERR2, NULL);
			return (-1);
		}
		free (*env_token);
		(*env_token) = ft_strdup(current->token);
	}
	return (0);
}
