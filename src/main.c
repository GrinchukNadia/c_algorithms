/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrinchu <nadezda.grinchuk@learner.42.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 15:32:03 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/09 15:01:18 by ngrinchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	prepare_stacks(t_stack *a, t_stack *b, char **arguments)
{
	int	count;

	count = parse_numbers(arguments, NULL);
	if (count <= 0 || (size_t)count > (size_t)-1 / sizeof(int))
		return (0);
	a->values = malloc(sizeof(int) * count);
	b->values = malloc(sizeof(int) * count);
	if (!a->values || !b->values)
		return (0);
	a->size = count;
	b->size = 0;
	if (parse_numbers(arguments, a->values) != count
		|| has_duplicates(a->values, count))
		return (0);
	a->disorder = compute_disorder(a);
	b->disorder = 0.0;
	return (1);
}

static int	finish(t_stack *a, t_stack *b, int status)
{
	free(a->values);
	free(b->values);
	if (status != 0)
		write(2, "Error\n", 6);
	return (status);
}

static int	run_sorting(t_stack *a, t_stack *b, const t_options *options)
{
	t_benchmark	benchmark;
	int			success;

	init_benchmark(&benchmark, a, b, options);
	success = sort_stack(a, b, options->strategy);
	if (success && options->benchmark)
		print_benchmark(&benchmark);
	a->benchmark = NULL;
	b->benchmark = NULL;
	return (success);
}

int	main(int argc, char **argv)
{
	t_options	options;
	t_stack		a;
	t_stack		b;
	int			first_number;

	if (argc == 1)
		return (0);
	a.values = NULL;
	b.values = NULL;
	first_number = parse_options(argv, &options);
	if (first_number < 0
		|| !prepare_stacks(&a, &b, argv + first_number))
		return (finish(&a, &b, 1));
	if (!run_sorting(&a, &b, &options))
		return (finish(&a, &b, 1));
	return (finish(&a, &b, 0));
}
