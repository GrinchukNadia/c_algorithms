/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 14:40:34 by ngrinchu          #+#    #+#             */
/*   Updated: 2026/11/10 14:54:14 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

int	is_whitespace(char character)
{
	return (character == ' ' || (character >= '\t' && character <= '\r'));
}

int	str_equal(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

static int	parse_digits(const char *str, int length, int sign, int *result)
{
	int			digit;
	long long	limit;
	long long	number;

	number = 0;
	limit = (long long)INT_MAX + (sign < 0);
	while (length > 0)
	{
		if (*str < '0' || *str > '9')
			return (0);
		digit = *str - '0';
		if (number > (limit - digit) / 10)
			return (0);
		number = number * 10 + digit;
		length--;
		str++;
	}
	*result = (int)(number * sign);
	return (1);
}

int	parse_integer(const char *str, int length, int *result)
{
	int	sign;

	sign = 1;
	if (length <= 0)
		return (0);
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
		length--;
	}
	if (length == 0)
		return (0);
	return (parse_digits(str, length, sign, result));
}

int	has_duplicates(const int *numbers, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (numbers[i] == numbers[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
