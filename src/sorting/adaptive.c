/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:17:57 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:17:57 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_strategy	adaptive_strategy(double disorder)
{
	if (disorder < 0.2)
		return (STRATEGY_SIMPLE);
	if (disorder < 0.5)
		return (STRATEGY_MEDIUM);
	return (STRATEGY_COMPLEX);
}

int	sort_adaptive(t_stack *a, t_stack *b)
{
	t_strategy	strategy;

	a->disorder = compute_disorder(a);
	if (a->size < 2 || is_sorted(a))
		return (1);
	strategy = adaptive_strategy(a->disorder);
	if (strategy == STRATEGY_SIMPLE)
		sort_simple(a, b);
	else if (strategy == STRATEGY_MEDIUM)
		return (sort_medium(a, b));
	else
		return (sort_complex(a, b));
	return (1);
}
