/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:17:49 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:17:49 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack *stack)
{
	int	tmp;

	if (stack->size < 2)
		return ;
	tmp = stack->values[0];
	stack->values[0] = stack->values[1];
	stack->values[1] = tmp;
}

void	swap_a(t_stack *a)
{
	if (a->size < 2)
		return ;
	swap(a);
	print_operation(a, OP_SA);
}

void	swap_b(t_stack *b)
{
	if (b->size < 2)
		return ;
	swap(b);
	print_operation(b, OP_SB);
}

void	swap_both(t_stack *a, t_stack *b)
{
	if (a->size < 2 && b->size < 2)
		return ;
	swap(a);
	swap(b);
	print_operation(a, OP_SS);
}
