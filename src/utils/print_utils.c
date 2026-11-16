/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:19:27 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:19:27 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	putstr_fd(const char *str, int fd)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

void	print_unsigned_fd(unsigned long long number, int fd)
{
	char	digit;

	if (number >= 10)
		print_unsigned_fd(number / 10, fd);
	digit = '0' + number % 10;
	write(fd, &digit, 1);
}

static void	print_number_fd(long long number, int fd)
{
	char	digit;

	if (number < 0)
	{
		write(fd, "-", 1);
		number = -number;
	}
	if (number >= 10)
		print_number_fd(number / 10, fd);
	digit = '0' + number % 10;
	write(fd, &digit, 1);
}

void	print_stack(t_stack *stack)
{
	int	i;

	i = 0;
	while (i < stack->size)
	{
		if (i > 0)
			write(2, " ", 1);
		print_number_fd(stack->values[i], 2);
		i++;
	}
	write(2, "\n", 1);
}
