/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 17:00:43 by ngrinchu          #+#    #+#             */
/*   Updated: 2026/11/11 11:33:52 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

static t_strategy	parse_strategy(const char *argument)
{
	if (str_equal(argument, "--simple"))
		return (STRATEGY_SIMPLE);
	if (str_equal(argument, "--medium"))
		return (STRATEGY_MEDIUM);
	if (str_equal(argument, "--complex"))
		return (STRATEGY_COMPLEX);
	if (str_equal(argument, "--adaptive"))
		return (STRATEGY_ADAPTIVE);
	return (STRATEGY_INVALID);
}

int	parse_options(char **argv, t_options *options)
{
	int	index;
	int	strategy_set;

	index = 1;
	strategy_set = 0;
	options->strategy = STRATEGY_ADAPTIVE;
	options->benchmark = 0;
	while (argv[index] && argv[index][0] == '-' && argv[index][1] == '-')
	{
		if (str_equal(argv[index], "--bench"))
			options->benchmark = 1;
		else
		{
			if (strategy_set)
				return (-1);
			options->strategy = parse_strategy(argv[index]);
			if (options->strategy == STRATEGY_INVALID)
				return (-1);
			strategy_set = 1;
		}
		index++;
	}
	return (index);
}

static int	parse_number_argument(const char *str, int *numbers, int *count)
{
	int	index;
	int	start;
	int	value;
	int	initial_count;

	index = 0;
	initial_count = *count;
	while (str[index])
	{
		while (is_whitespace(str[index]))
			index++;
		if (!str[index])
			break ;
		start = index;
		while (str[index] && !is_whitespace(str[index]))
			index++;
		if (*count == INT_MAX
			|| !parse_integer(str + start, index - start, &value))
			return (0);
		if (numbers)
			numbers[*count] = value;
		(*count)++;
	}
	return (*count > initial_count);
}

int	parse_numbers(char **arguments, int *numbers)
{
	int	count;

	count = 0;
	while (*arguments)
	{
		if (!parse_number_argument(*arguments, numbers, &count))
			return (-1);
		arguments++;
	}
	return (count);
}
