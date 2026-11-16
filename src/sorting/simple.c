/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:18:40 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:18:40 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//selection sort adaptation (minimum extraction)
void	sort_simple(t_stack *a, t_stack *b)
{
	while (a->size > 1)
		push_minimum(a, b);
	while (b->size > 0)
		push_a(a, b);
}
