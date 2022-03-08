/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/09 19:21:32 by akramp        #+#    #+#                 */
/*   Updated: 2021/07/20 11:49:48 by Angi          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_calc(int n, char *num, int len)
{
	int	res;

	res = 0;
	while (n > 0)
	{
		res = n % 10;
		num[len - 1] = res + '0';
		n = n / 10;
		len--;
	}
	return (num);
}

static int	ft_num_len(int n, int *sign)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		*sign = -1;
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		sign;
	int		len;

	sign = 1;
	len = ft_num_len(n, &sign);
	num = (char *)malloc(sizeof(*num) * len + 1);
	if (num == 0)
		return (0);
	if (n == 0)
		num[0] = '0';
	if (n == -2147483648)
	{
		num[0] = '-';
		num[1] = '2';
		n = 147483648;
	}
	if (sign < 0)
	{
		num[0] = '-';
		n = n * -1;
	}
	num[len] = '\0';
	num = ft_calc(n, num, len);
	return (num);
}
