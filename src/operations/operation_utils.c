/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:17:06 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:17:06 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

const char	*operation_name(t_operation operation)
{
	const char	*names[11];

	names[OP_SA] = "sa";
	names[OP_SB] = "sb";
	names[OP_SS] = "ss";
	names[OP_PA] = "pa";
	names[OP_PB] = "pb";
	names[OP_RA] = "ra";
	names[OP_RB] = "rb";
	names[OP_RR] = "rr";
	names[OP_RRA] = "rra";
	names[OP_RRB] = "rrb";
	names[OP_RRR] = "rrr";
	return (names[operation]);
}

void	print_operation(t_stack *stack, t_operation operation)
{
	putstr_fd(operation_name(operation), 1);
	write(1, "\n", 1);
	if (stack->benchmark)
	{
		stack->benchmark->counts[operation]++;
		stack->benchmark->total++;
	}
}
