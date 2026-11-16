/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:17:27 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:17:27 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	push_a(t_stack *a, t_stack *b)
{
	int	i;

	if (b->size == 0)
		return ;
	i = a->size;
	while (i > 0)
	{
		a->values[i] = a->values[i - 1];
		i--;
	}
	a->values[0] = b->values[0];
	i = 0;
	while (i < b->size - 1)
	{
		b->values[i] = b->values[i + 1];
		i++;
	}
	a->size++;
	b->size--;
	print_operation(a, OP_PA);
}

void	push_b(t_stack *a, t_stack *b)
{
	int	i;

	if (a->size == 0)
		return ;
	i = b->size;
	while (i > 0)
	{
		b->values[i] = b->values[i - 1];
		i--;
	}
	b->values[0] = a->values[0];
	i = 0;
	while (i < a->size - 1)
	{
		a->values[i] = a->values[i + 1];
		i++;
	}
	b->size++;
	a->size--;
	print_operation(b, OP_PB);
}
