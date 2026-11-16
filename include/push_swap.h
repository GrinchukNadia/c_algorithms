/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzouhar <dominik.zouhar@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 21:21:41 by dzouhar           #+#    #+#             */
/*   Updated: 2026/11/11 21:21:41 by dzouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef enum e_operation
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR
}	t_operation;

typedef enum e_strategy
{
	STRATEGY_INVALID = -1,
	STRATEGY_SIMPLE,
	STRATEGY_MEDIUM,
	STRATEGY_COMPLEX,
	STRATEGY_ADAPTIVE
}	t_strategy;

typedef struct s_options
{
	t_strategy	strategy;
	int			benchmark;
}	t_options;

typedef struct s_benchmark
{
	unsigned long long	counts[11];
	unsigned long long	total;
	double				disorder;
	t_strategy			strategy;
}	t_benchmark;

/**
 * @brief Array-backed stack; values[0] is the top.
 * @details Initialize benchmark to NULL before standalone operation calls,
 * or use init_benchmark to attach shared counters to both stacks.
 */
typedef struct s_stack
{
	int			*values;
	int			size;
	double		disorder;
	t_benchmark	*benchmark;
}	t_stack;

/**
 * @brief Checks if values are in order.
 * @param a Valid stack to inspect; not modified.
 * @return 1 if sorted or fewer than two elements exist, otherwise 0.
 */
int			is_sorted(t_stack *a);

/**
 * @brief Sorts A using small sorting or the selected strategy.
 * @param a Stack of validated integers.
 * @param b Empty stack; array must hold all initial A values.
 * @param strategy Requested strategy; sizes up to five use small sorting.
 * @details Sorted inputs print nothing. Sorting instructions go to stdout.
 * @return 1 on success, 0 for an invalid strategy or allocation failure.
 * @details The caller reports errors; failed sorts produce no benchmark.
 */
int			sort_stack(t_stack *a, t_stack *b, t_strategy strategy);

/**
 * @brief Sorts up to five values using minimum extraction and a
 * three-value sort.
 * @param a Stack containing zero to five distinct integers.
 * @param b Empty stack; array must hold all initial A values.
 * @details Leaves A ascending and B empty; prints instructions to stdout.
 */
void		sort_small(t_stack *a, t_stack *b);

/**
 * @brief Sorts A by repeatedly extracting its minimum to B, then pushing back.
 * @param a Stack of integers to sort.
 * @param b Empty stack; array must hold all initial A values.
 * @details Leaves A ascending and B empty; prints instructions to stdout.
 * Worst-case stack-operation count is O(n squared).
 */
void		sort_simple(t_stack *a, t_stack *b);

/**
 * @brief Sorts A in roughly square-root-sized chunks, highest chunk first.
 * @param a Stack of integers to sort.
 * @param b Empty stack; array must hold all initial A values.
 * @details Leaves A ascending and B empty; prints instructions to stdout.
 * Uses O(n sqrt(n)) stack operations and O(n) extra memory. Preparing the
 * sorted copy takes O(n squared) comparisons, not counted as stack operations.
 * @return 1 on success, 0 on allocation failure without changing the stacks.
 * The caller reports errors.
 */
int			sort_medium(t_stack *a, t_stack *b);

/**
 * @brief Sorts A by processing rank bits from least to most significant.
 * @param a Stack of integers;
 * @param b Empty stack; array must hold all initial A values.
 * @details Leaves A ascending and B empty; prints pb, ra and pa to stdout.
 * Uses O(n log n) stack operations and O(n) extra memory. Preparing the
 * sorted copy takes O(n squared) comparisons, not counted as stack operations.
 * @return 1 on success, 0 on allocation failure without changing the stacks.
 * The caller reports errors.
 */
int			sort_complex(t_stack *a, t_stack *b);

/**
 * @brief Allocates an ascending copy of the active stack values.
 * @param a stack to copy;
 * @return New array owned by the caller, or NULL if allocation fails.
 * @details Caller must free the array and report allocation failure.
 * Uses insertion sort with O(n squared) comparisons; emits no instructions.
 */
int			*sorted_values(t_stack *a);

/**
 * @brief Selects a sorting strategy from the initial disorder.
 * @param a Stack of distinct integers to sort.
 * @param b Empty stack; array must hold all initial A values.
 * @details Recalculates and caches initial disorder before any operations.
 * Below 0.2 uses simple; below 0.5 uses medium; otherwise uses complex.
 * Leaves A ascending and B empty on success; prints instructions to stdout.
 * Sorted inputs emit nothing. The caller reports allocation failures.
 * The cached disorder describes the input, not the final sorted stack.
 * @return 1 on success, 0 on allocation failure.
 */
int			sort_adaptive(t_stack *a, t_stack *b);

/**
 * @brief Resolves the adaptive regime using the shared 0.2/0.5 thresholds.
 */
t_strategy	adaptive_strategy(double disorder);

/**
 * @brief Resets counters and attaches them to both stacks only with --bench.
 * @details The benchmark object must outlive all operations on these stacks.
 * Otherwise each stack's benchmark pointer must be NULL.
 */
void		init_benchmark(t_benchmark *benchmark, t_stack *a, t_stack *b,
				const t_options *options);

/**
 * @brief Prints one instruction to stdout and counts it once if enabled.
 * @param stack Stack whose benchmark pointer is NULL or shared valid counters.
 * @param operation One of OP_SA through OP_RRR; not OP_COUNT.
 */
void		print_operation(t_stack *stack, t_operation operation);
const char	*operation_name(t_operation operation);

/**
 * @brief Prints the five-line benchmark report exclusively to stderr.
 * @details Call only after a successful sort when --bench is enabled.
 * Disorder is the initial measurement, rounded to two percentage decimals.
 */
void		print_benchmark(const t_benchmark *benchmark);
void		putstr_fd(const char *text, int fd);
void		print_unsigned_fd(unsigned long long number, int fd);

/**
 * @brief Calculates the fraction of index pairs whose values are out of order.
 * @param a Valid stack to inspect;
 * @return Value from 0.0 to 1.0; 0.0 for fewer than two elements.
 * @details Uses O(n squared) comparisons and emits no sorting instructions.
 */
double		compute_disorder(const t_stack *a);

/**
 * @brief Prints active values from top to bottom to stderr for debugging.
 * @param stack Valid stack to inspect;
 * @details Values are space-separated and followed by a newline.
 * An empty stack prints only a newline. No output is written to stdout.
 */
void		print_stack(t_stack *stack);

/**
 * @brief Moves B's top value to A and prints pa followed by a newline to stdout.
 * @param a Destination stack; must have room for one more element.
 * @param b Source stack; if empty, nothing changes or prints.
 * @details Updates both sizes;
 */
void		push_a(t_stack *a, t_stack *b);

/**
 * @brief Moves A's top value to B and prints pb followed by a newline to stdout.
 * @param a Source stack; if empty, nothing changes or prints.
 * @param b Destination stack; must have room for one more element.
 * @details Updates both sizes;
 */
void		push_b(t_stack *a, t_stack *b);

/**
 * @brief Moves A's minimum to the top of B using the shorter rotation direction.
 * @param a Source stack;
 * @param b Destination stack; must have room for one more element.
 * @details Prints the rotations followed by pb to standard output.
 */
void		push_minimum(t_stack *a, t_stack *b);

/**
 * @brief Moves B's maximum to the top of A using the shorter rotation direction.
 * @param a Destination stack; must have room for one more element.
 * @param b Source stack;
 * @details Prints the rotations followed by pa to standard output.
 */
void		push_maximum(t_stack *a, t_stack *b);

/**
 * @brief Swaps A's top two values and prints sa followed by a newline to stdout.
 * @details Fewer than two elements: nothing changes or prints.
 */
void		swap_a(t_stack *a);

/**
 * @brief Swaps B's top two values and prints sb followed by a newline to stdout.
 * @details Fewer than two elements: nothing changes or prints.
 */
void		swap_b(t_stack *b);

/**
 * @brief Swaps each stack's top two values independently.
 * @details Stacks with fewer than two elements remain unchanged.
 * Prints only ss followed by a newline to stdout if either stack can swap.
 */
void		swap_both(t_stack *a, t_stack *b);

/**
 * @brief Moves A's top value to the bottom; prints ra and a newline to stdout.
 * @details Fewer than two elements: nothing changes or prints.
 */
void		rotate_a(t_stack *a);

/**
 * @brief Moves B's top value to the bottom; prints rb and a newline to stdout.
 * @details Fewer than two elements: nothing changes or prints.
 */
void		rotate_b(t_stack *b);

/**
 * @brief Moves each stack's top value to its bottom independently.
 * @details Stacks with fewer than two elements remain unchanged.
 * Prints only rr followed by a newline to stdout if either stack can rotate.
 */
void		rotate_both(t_stack *a, t_stack *b);

/**
 * @brief Moves A's bottom value to the top; prints rra and a newline to stdout.
 * @details Fewer than two elements: nothing changes or prints.
 */
void		reverse_a(t_stack *a);

/**
 * @brief Moves B's bottom value to the top; prints rrb and a newline to stdout.
 * @details Fewer than two elements: nothing changes or prints.
 */
void		reverse_b(t_stack *b);

/**
 * @brief Moves each stack's bottom value to its top independently.
 * @details Stacks with fewer than two elements remain unchanged.
 * Prints only rrr followed by a newline to stdout if either stack can rotate.
 */
void		reverse_both(t_stack *a, t_stack *b);

/**
 * @brief Reads prefix-only options; defaults to adaptive with benchmark off.
 * @param argv Original command-line arguments, including the program name.
 * @param options Receives strategy and benchmark mode; use only on success.
 * @return Index of the first numeric argument, or -1 for invalid options.
 * @details Rejects unknown options and multiple strategy selectors.
 */
int			parse_options(char **argv, t_options *options);

/**
 * @brief Validates and counts integers, optionally writing them to an array.
 * @param arguments Null-terminated list starting at the first numeric argument.
 * @param numbers parsed integer values.
 * @return Number of integers, or -1 for malformed or empty arguments.
 */
int			parse_numbers(char **arguments, int *numbers);

/**
 * @brief Parses exactly length characters as a signed decimal int.
 * @return 1 on success, 0 on invalid syntax or overflow.
 */
int			parse_integer(const char *str, int length, int *result);

/**
 * @brief Returns 1 if any two integer values are equal, otherwise 0.
 * @details Uses O(n squared) comparisons; does not modify the array.
 */
int			has_duplicates(const int *numbers, int count);

int			str_equal(const char *s1, const char *s2);
int			is_whitespace(char character);

#endif