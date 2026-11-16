/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:17:38 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:17:38 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_stack(t_stack *stack)
{
	int	last;
	int	i;

	if (stack->size < 2)
		return ;
	last = stack->values[stack->size - 1];
	i = stack->size - 1;
	while (i > 0)
	{
		stack->values[i] = stack->values[i - 1];
		i--;
	}
	stack->values[0] = last;
}

void	reverse_a(t_stack *a)
{
	if (a->size < 2)
		return ;
	reverse_stack(a);
	print_operation(a, OP_RRA);
}

void	reverse_b(t_stack *b)
{
	if (b->size < 2)
		return ;
	reverse_stack(b);
	print_operation(b, OP_RRB);
}

void	reverse_both(t_stack *a, t_stack *b)
{
	if (a->size < 2 && b->size < 2)
		return ;
	reverse_stack(a);
	reverse_stack(b);
	print_operation(a, OP_RRR);
}
