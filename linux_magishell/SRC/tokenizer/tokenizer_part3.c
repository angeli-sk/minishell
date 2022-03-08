/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_part3.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Angi <Angi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/19 13:07:45 by Angi          #+#    #+#                 */
/*   Updated: 2022/02/23 16:18:46 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

int	flag_check(char c, t_magi *magi)
{
	if (c == '"'
		&& magi->single_quote != SINGLE_QUOTE_FOUND
		&& magi->double_quote != DOUBLE_QUOTE_FOUND)
		magi->double_quote = DOUBLE_QUOTE_FOUND;
	if (c == '\''
		&& magi->double_quote != DOUBLE_QUOTE_FOUND
		&& magi->single_quote != SINGLE_QUOTE_FOUND)
		magi->single_quote = SINGLE_QUOTE_FOUND;
	if (c == '<' || c == '>' || c == '|')
		return (SPLIT_TOKEN);
	return (DONT_SPLIT_TOKEN);
}

static void	sfs_replacer(char *replace_with, int *i_rw, int *i, char *new_str)
{
	while (replace_with[*i_rw])
	{
		new_str[*i] = replace_with[*i_rw];
		(*i)++;
		(*i_rw)++;
	}
}

void	str_from_str_replacer(char **str, char *replace_with, int str_pos, \
	int len_to_be_replaced)
{
	int		i_rw;
	int		i;
	char	*new_str;
	int		new_str_len;

	i_rw = 0;
	i = str_pos;
	new_str_len = (ft_strlen(*str) - len_to_be_replaced) + \
		ft_strlen(replace_with);
	new_str = malloc (sizeof(char) * new_str_len + 1);
	if (new_str == NULL)
	{
		error_msg(MALLOC_FAIL, NULL);
		exit(EXIT_FAILURE);
	}
	new_str[new_str_len] = '\0';
	if (str_pos != 0)
		ft_memcpy(new_str, *str, str_pos);
	if (ft_strlen(replace_with) != 0)
		sfs_replacer(replace_with, &i_rw, &i, new_str);
	if (i < new_str_len)
		ft_memcpy(&new_str[i], &(*str)[str_pos + len_to_be_replaced], \
		(ft_strlen(*str) - (str_pos + len_to_be_replaced)));
	free (*str);
	*str = new_str;
}

int	loop_through_env_list(t_magi *magi, char **line, char *env, \
	int env_pos)
{
	t_list	*env_list;

	env_list = magi->env;
	if ((*line)[(env_pos)] == '$' && ((*line)[(env_pos) + 1] == ' ' \
		|| (*line)[(env_pos) + 1] == '\0' || (*line)[(env_pos) + 1] == '"' \
		|| (*line)[env_pos + 1] == '=' || (*line)[env_pos + 1] == '?'))
		return (0);
	while (env_list)
	{
		if (!env_list->token)
			return (0);
		if (ft_strncmp
			(env_list->token, &env[1], chrfinder(env_list->token, '=', 0)) == 0
			&& chrfinder(env_list->token, '=', 0) == ft_strlen(&env[1]))
		{
			str_from_str_replacer(line, \
			&env_list->token[chrfinder(env_list->token, '=', 0) + 1], \
			env_pos, ft_strlen(env));
			return (0);
		}
		env_list = env_list->next;
	}
	return (-1);
}
