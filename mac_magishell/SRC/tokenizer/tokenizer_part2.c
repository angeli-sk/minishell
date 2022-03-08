/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_part2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Angi <Angi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/19 12:55:54 by Angi          #+#    #+#                 */
/*   Updated: 2022/02/23 16:18:29 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

void	insert_str(char **edit_line, int insert_pos, char *to_insert)
{
	char	*temp;
	int		len;
	int		size;

	len = ft_strlen(*edit_line);
	size = ft_strlen(to_insert);
	temp = malloc(sizeof(char) * (len + size) + 1);
	if (insert_pos > 0)
		ft_memcpy(&temp[0], *edit_line, insert_pos);
	if (insert_pos <= len)
	{
		ft_memcpy(&temp[insert_pos], to_insert, size);
		if (len > 0)
			ft_memcpy(&temp[insert_pos + size], \
			&(*edit_line)[insert_pos], \
			(ft_strlen(&(*edit_line)[insert_pos])));
	}
	temp[len + size] = '\0';
	free (*edit_line);
	*edit_line = temp;
}

void	remove_chr(char **edit_line, int chr_pos)
{
	char	*temp;
	int		len;

	len = ft_strlen(*edit_line);
	temp = malloc(sizeof(char) * len);
	if (temp == NULL)
	{
		error_msg(MALLOC_FAIL, NULL);
		exit(EXIT_FAILURE);
	}
	ft_memcpy(temp, *edit_line, chr_pos);
	if (chr_pos < len - 1)
		ft_memcpy(&temp[chr_pos], \
			&(*edit_line)[chr_pos + 1], \
				(ft_strlen(&(*edit_line)[chr_pos + 1])));
	temp[len - 1] = '\0';
	free (*edit_line);
	*edit_line = temp;
}

void	env_replacer_loop_single_dollar(char **line, t_magi *magi, \
	int *env_pos, int *pos)
{
	if ((*line)[(*env_pos)] == '$' && ((*line)[((*env_pos)) + 1] \
		== '"' || (*line)[((*env_pos)) + 1] == '\'') \
		&& magi->double_quote != DOUBLE_QUOTE_FOUND \
		&& (*line)[((*env_pos)) + 1] != ' ' \
		&& (*line)[((*env_pos)) + 1] != '\0' )
	{
		remove_chr(line, (*env_pos));
		(*pos)--;
	}
	else
		(*env_pos)++;
}

int	int_len_counter(int num)
{
	int	len;

	len = 0;
	while (num > 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}
