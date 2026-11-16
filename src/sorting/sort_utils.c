/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:19:09 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:19:09 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*sorted_values(t_stack *a)
{
	int	*sorted;
	int	i;
	int	j;

	sorted = malloc(sizeof(int) * a->size);
	if (!sorted)
		return (NULL);
	i = 0;
	while (i < a->size)
	{
		j = i;
		while (j > 0 && sorted[j - 1] > a->values[i])
		{
			sorted[j] = sorted[j - 1];
			j--;
		}
		sorted[j] = a->values[i];
		i++;
	}
	return (sorted);
}

static void	rotate_minimum(t_stack *a, int min_index)
{
	if (min_index > a->size / 2)
		min_index -= a->size;
	while (min_index < 0)
	{
		reverse_a(a);
		min_index++;
	}
	while (min_index > 0)
	{
		rotate_a(a);
		min_index--;
	}
}

void	push_minimum(t_stack *a, t_stack *b)
{
	int	i;
	int	min_index;

	min_index = 0;
	i = 1;
	while (i < a->size)
	{
		if (a->values[i] < a->values[min_index])
			min_index = i;
		i++;
	}
	rotate_minimum(a, min_index);
	push_b(a, b);
}

void	push_maximum(t_stack *a, t_stack *b)
{
	int	i;
	int	max_index;

	max_index = 0;
	i = 1;
	while (i < b->size)
	{
		if (b->values[i] > b->values[max_index])
			max_index = i;
		i++;
	}
	if (max_index > b->size / 2)
		max_index -= b->size;
	while (max_index < 0)
	{
		reverse_b(b);
		max_index++;
	}
	while (max_index-- > 0)
		rotate_b(b);
	push_a(a, b);
}
