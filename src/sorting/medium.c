/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:18:35 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:18:35 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_chunk(t_stack *a, t_stack *b, int minimum, int remaining)
{
	while (remaining > 0)
	{
		if (a->values[0] >= minimum)
			push_b(a, b);
		else
			rotate_a(a);
		remaining--;
	}
}

static void	restore_unsorted_prefix(t_stack *a, int unsorted_count)
{
	int	sorted_count;

	sorted_count = a->size - unsorted_count;
	if (unsorted_count <= sorted_count)
	{
		while (unsorted_count > 0)
		{
			reverse_a(a);
			unsorted_count--;
		}
	}
	else
	{
		while (sorted_count > 0)
		{
			rotate_a(a);
			sorted_count--;
		}
	}
}

static void	sort_chunks(t_stack *a, t_stack *b, int *sorted)
{
	int	chunk_size;
	int	upper;
	int	lower;

	chunk_size = 1;
	while (chunk_size < a->size / chunk_size)
		chunk_size++;
	upper = a->size;
	while (upper > 0)
	{
		lower = upper - chunk_size;
		if (lower < 0)
			lower = 0;
		push_chunk(a, b, sorted[lower], upper);
		while (b->size > 0)
			push_maximum(a, b);
		restore_unsorted_prefix(a, lower);
		upper = lower;
	}
}

int	sort_medium(t_stack *a, t_stack *b)
{
	int	*sorted;

	if (a->size < 2 || is_sorted(a))
		return (1);
	sorted = sorted_values(a);
	if (!sorted)
		return (0);
	sort_chunks(a, b, sorted);
	free(sorted);
	return (1);
}
