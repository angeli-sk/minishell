/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 16:00:58 by akramp        #+#    #+#                 */
/*   Updated: 2022/02/12 10:12:02 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"
#include <stdlib.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != '\0')
		i++;
	return (i);
}

static void	*ft_mymemcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (d == 0 && s == 0)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;

	if (src == 0)
		return (0);
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	dstlen = dstsize - 1;
	if (srclen < dstsize)
		dstlen = srclen;
	ft_mymemcpy(dst, src, dstlen);
	dst[dstlen] = '\0';
	return (srclen);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (s2 == 0)
		return (0);
	ft_strlcpy(s2, s1, len + 1);
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*str;
	int		i;

	if ((int) start > ft_strlen(s))
		return (ft_strdup(""));
	str = malloc(sizeof(*s) * len + 1);
	if (str == 0 || s == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
