/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 13:29:41 by akramp        #+#    #+#                 */
/*   Updated: 2022/02/09 15:36:22 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"
#include <stdlib.h>

static char	**ft_free(char **split, int x)
{
	while (x >= 0)
	{
		free(split[x]);
		x--;
	}
	free(split);
	return (0);
}

static char	**ft_write_string(char *s, char c, char **split, int max_y)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (s[i] != '\0' && y < max_y)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			split[y][x] = s[i];
			x++;
			i++;
		}
		split[y][x] = '\0';
		y++;
		x = 0;
	}
	return (split);
}

static char	**ft_char_count(char *s, char c, char **split, int y)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		while (*s != c && *s != '\0')
		{
			count++;
			s++;
		}
		if (x < y)
		{
			split[x] = (char *)malloc(sizeof(char) * count + 1);
			if (split[x] == 0)
				return (ft_free(split, x));
			x++;
		}
		count = 0;
	}
	return (split);
}

static int	ft_string_count(char *s, char c, int y)
{
	int	i;
	int	m;

	i = 0;
	m = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && m == 0)
		{
			y++;
			m = 1;
		}
		if (s[i] == c && m == 1)
			m = 0;
		i++;
	}
	return (y);
}

char	**ft_split(char const *s, char c)
{
	int		y;
	int		len;
	char	*copy_s;
	char	**split;

	y = 0;
	len = 0;
	copy_s = (char *)s;
	if (s == 0)
		return (0);
	y = ft_string_count(copy_s, c, y);
	split = (char **)malloc(sizeof(char *) * (y + 1));
	if (split == 0)
		return (0);
	split = ft_char_count(copy_s, c, split, y);
	if (split == 0)
		return (0);
	split = ft_write_string(copy_s, c, split, y);
	split[y] = 0;
	return (split);
}
