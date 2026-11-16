/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:18:08 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:18:08 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static unsigned int	find_rank(int *sorted, int size, int value)
{
	int	low;
	int	high;
	int	middle;

	low = 0;
	high = size;
	while (low < high)
	{
		middle = low + (high - low) / 2;
		if (sorted[middle] == value)
			return (middle);
		if (sorted[middle] < value)
			low = middle + 1;
		else
			high = middle;
	}
	return (low);
}

static void	radix_pass(t_stack *a, t_stack *b, int *sorted,
		unsigned int mask)
{
	int				size;
	int				remaining;
	unsigned int	rank;

	size = a->size;
	remaining = size;
	while (remaining > 0)
	{
		rank = find_rank(sorted, size, a->values[0]);
		if ((rank & mask) == 0)
			push_b(a, b);
		else
			rotate_a(a);
		remaining--;
	}
	while (b->size > 0)
		push_a(a, b);
}

int	sort_complex(t_stack *a, t_stack *b)
{
	int				*sorted;
	unsigned int	mask;

	if (a->size < 2 || is_sorted(a))
		return (1);
	sorted = sorted_values(a);
	if (!sorted)
		return (0);
	mask = 1;
	while (mask <= (unsigned int)(a->size - 1))
	{
		radix_pass(a, b, sorted, mask);
		mask <<= 1;
	}
	free(sorted);
	return (1);
}
