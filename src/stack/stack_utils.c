/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:19:19 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:19:19 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *a)
{
	int	i;

	i = 0;
	while (i < a->size - 1)
	{
		if (a->values[i] > a->values[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	sort_stack(t_stack *a, t_stack *b, t_strategy strategy)
{
	if (strategy != STRATEGY_SIMPLE && strategy != STRATEGY_MEDIUM
		&& strategy != STRATEGY_COMPLEX && strategy != STRATEGY_ADAPTIVE)
		return (0);
	if (a->size < 2 || is_sorted(a))
		return (1);
	if (a->size <= 5)
		sort_small(a, b);
	else if (strategy == STRATEGY_SIMPLE)
		sort_simple(a, b);
	else if (strategy == STRATEGY_MEDIUM)
		return (sort_medium(a, b));
	else if (strategy == STRATEGY_COMPLEX)
		return (sort_complex(a, b));
	else if (strategy == STRATEGY_ADAPTIVE)
		return (sort_adaptive(a, b));
	return (1);
}
