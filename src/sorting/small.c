/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:19:04 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:19:04 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static void	sort_three(t_stack *a)
{
	if (a->values[0] > a->values[1] && a->values[0] > a->values[2])
		rotate_a(a);
	else if (a->values[1] > a->values[0] && a->values[1] > a->values[2])
		reverse_a(a);
	if (a->values[0] > a->values[1])
		swap_a(a);
}

void	sort_small(t_stack *a, t_stack *b)
{
	if (a->size < 2 || is_sorted(a))
		return ;
	while (a->size > 3)
		push_minimum(a, b);
	if (a->size == 3)
		sort_three(a);
	else if (a->values[0] > a->values[1])
		swap_a(a);
	while (b->size > 0)
		push_a(a, b);
}
