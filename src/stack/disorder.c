/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:19:14 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:19:14 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	compute_disorder(const t_stack *a)
{
	int		i;
	int		j;
	double	mistakes;
	double	total_pairs;

	mistakes = 0.0;
	total_pairs = 0.0;
	i = 0;
	while (i < a->size)
	{
		j = i + 1;
		while (j < a->size)
		{
			total_pairs++;
			if (a->values[i] > a->values[j])
				mistakes++;
			j++;
		}
		i++;
	}
	if (total_pairs == 0.0)
		return (0.0);
	return (mistakes / total_pairs);
}
