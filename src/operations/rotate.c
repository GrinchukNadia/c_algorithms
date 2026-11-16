/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:17:44 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:17:44 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_stack(t_stack *stack)
{
	int	first;
	int	i;

	if (stack->size < 2)
		return ;
	first = stack->values[0];
	i = 0;
	while (i < stack->size - 1)
	{
		stack->values[i] = stack->values[i + 1];
		i++;
	}
	stack->values[stack->size - 1] = first;
}

void	rotate_a(t_stack *a)
{
	if (a->size < 2)
		return ;
	rotate_stack(a);
	print_operation(a, OP_RA);
}

void	rotate_b(t_stack *b)
{
	if (b->size < 2)
		return ;
	rotate_stack(b);
	print_operation(b, OP_RB);
}

void	rotate_both(t_stack *a, t_stack *b)
{
	if (a->size < 2 && b->size < 2)
		return ;
	rotate_stack(a);
	rotate_stack(b);
	print_operation(a, OP_RR);
}
