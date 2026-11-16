/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:16:33 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:16:33 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_benchmark(t_benchmark *benchmark, t_stack *a, t_stack *b,
		const t_options *options)
{
	int	i;

	i = 0;
	while (i < 11)
		benchmark->counts[i++] = 0;
	benchmark->total = 0;
	benchmark->disorder = a->disorder;
	benchmark->strategy = options->strategy;
	a->benchmark = NULL;
	b->benchmark = NULL;
	if (options->benchmark)
	{
		a->benchmark = benchmark;
		b->benchmark = benchmark;
	}
}

static const char	*strategy_name(t_strategy strategy)
{
	if (strategy == STRATEGY_SIMPLE)
		return ("Simple");
	if (strategy == STRATEGY_MEDIUM)
		return ("Medium");
	if (strategy == STRATEGY_COMPLEX)
		return ("Complex");
	return ("Adaptive");
}

static void	print_strategy(const t_benchmark *benchmark)
{
	t_strategy	strategy;

	strategy = benchmark->strategy;
	putstr_fd("strategy: ", 2);
	putstr_fd(strategy_name(strategy), 2);
	if (strategy == STRATEGY_ADAPTIVE)
		strategy = adaptive_strategy(benchmark->disorder);
	if (strategy == STRATEGY_SIMPLE)
		putstr_fd(" / O(n^2)\n", 2);
	else if (strategy == STRATEGY_MEDIUM)
		putstr_fd(" / O(nsqrtn)\n", 2);
	else
		putstr_fd(" / O(nlogn)\n", 2);
}

static void	print_counts(const t_benchmark *benchmark)
{
	int	i;

	i = 0;
	while (i < 11)
	{
		putstr_fd(operation_name(i), 2);
		putstr_fd(": ", 2);
		print_unsigned_fd(benchmark->counts[i], 2);
		if (i == OP_PB || i == OP_RRR)
			write(2, "\n", 1);
		else
			write(2, " ", 1);
		i++;
	}
}

void	print_benchmark(const t_benchmark *benchmark)
{
	unsigned int	percent;

	percent = (unsigned int)(benchmark->disorder * 10000.0 + 0.5);
	putstr_fd("disorder: ", 2);
	print_unsigned_fd(percent / 100, 2);
	write(2, ".", 1);
	if (percent % 100 < 10)
		write(2, "0", 1);
	print_unsigned_fd(percent % 100, 2);
	putstr_fd("%\n", 2);
	print_strategy(benchmark);
	putstr_fd("total_ops: ", 2);
	print_unsigned_fd(benchmark->total, 2);
	write(2, "\n", 1);
	print_counts(benchmark);
}
