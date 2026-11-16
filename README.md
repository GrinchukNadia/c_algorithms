*This activity has been created as part of the 42 curriculum by dzouhar and ngrinchu*

# push_swap

## Description

`push_swap` is a 42 school sorting project written in C. It receives distinct
integers and prints a sequence of stack instructions that sorts them in
ascending order, with the smallest value at the top of stack A and stack B
empty. The first integer supplied is initially the top of A.

Both stacks use arrays. Sorting is performed through these instructions:

| Instructions | Effect |
|---|---|
| `sa`, `sb`, `ss` | Swap the top two values of A, B, or both |
| `pa`, `pb` | Move the top value from B to A, or from A to B |
| `ra`, `rb`, `rr` | Move the top value to the bottom of A, B, or both |
| `rra`, `rrb`, `rrr` | Move the bottom value to the top of A, B, or both |

The goal is to reduce the number of emitted instructions, not just execution
time. The program provides simple, medium, complex, and adaptive strategies,
plus an optional benchmark report. Inputs of up to five values use dedicated
small sorting. Already sorted inputs emit no instructions.

## Instructions

### Requirements and compilation

Use a POSIX environment such as Linux, macOS, or an installed WSL distribution
on Windows, with Make and a C compiler available as `cc`. The implementation
uses `unistd.h` and POSIX file descriptors;

From the project directory:

```sh
make
```

This builds `push_swap` using `-Wall -Wextra -Werror`.

| Command | Effect |
|---|---|
| `make` or `make all` | Build the executable; rebuild changed dependencies |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and the executable |
| `make re` | Clean and rebuild |

### Running the program

```sh
./push_swap [--simple | --medium | --complex | --adaptive] [--bench] integers...
```

All options must appear **before the first numeric argument**. The strategy and
benchmark options can appear in either order. If no strategy is supplied,
adaptive is used. At most one strategy selector is accepted, even when repeated
selectors are identical.

| Strategy | Method |
|---|---|
| `--simple` | Minimum extraction |
| `--medium` | Chunk-based sorting |
| `--complex` | Binary LSD radix sorting on ranks |
| `--adaptive` | Select a method from the initial disorder |

Examples:

```sh
./push_swap 3 2 1
./push_swap --simple 6 2 5 1 4 3
./push_swap --medium "6 2 5" "1 4 3"
./push_swap --complex -8 +3 0 42 -1 7
./push_swap --adaptive --bench 6 2 5 1 4 3
```

Numeric arguments can contain multiple whitespace-separated integers, including
mixed quoted and unquoted arguments. Optional leading `+` and `-` signs are
accepted. Values must fit in an `int` (`INT_MIN` through `INT_MAX`).

The program rejects:

- Duplicate integer values, including equivalent forms such as `1` and `+1`.
- Out-of-range values, nonnumeric tokens, and signs without digits.
- Empty or whitespace-only arguments.
- Unknown options, multiple strategy selectors, or options after numbers.
- Options supplied without any integers.

No arguments exits silently with status zero. Successful sorting also returns
zero. Invalid input or an allocation failure prints `Error` followed by a
newline to stderr and returns a nonzero status.

### Output and checking

Stdout contains only sorting instructions, one per line, not the sorted values.
Stderr contains errors or, with `--bench`, the benchmark report.

```sh
./push_swap --bench 3 2 1 > operations.txt 2> benchmark.txt
```

If you have the checker supplied for your evaluation environment, it can read
the instructions directly:

```sh
./push_swap --bench 3 2 1 | ./checker 3 2 1
```

Pass the same initial integers to the checker, without the strategy or benchmark
options. The checker is not built by this project's Makefile.

## Adaptive sorting

[sort_adaptive](src/sorting/adaptive.c) computes and caches the input disorder:
the number of inverted pairs divided by the total number of index pairs.
Empty and single-element inputs have disorder zero.

The thresholds are prescribed by the subject, not experimentally tuned:

| Initial disorder | Selected method | Stack-operation upper bound |
|---|---|---|
| Less than 0.2 | Minimum extraction, then push back | O(n squared) |
| At least 0.2 and less than 0.5 | One chunk at a time, highest first | O(n sqrt(n)) |
| At least 0.5 | Binary LSD radix on ranks | O(n log n) |

- **Simple:** extracting each minimum uses at most O(n) rotations and one push.
  Repeating for n values, then pushing back, takes O(n squared) instructions.
- **Medium:** chunks contain roughly sqrt(n) values. Each chunk scans A once,
  so roughly sqrt(n) chunks require O(n sqrt(n)) instructions. B contains only
  one chunk; extracting its maximum costs O(sqrt(n)) per value, preserving
  the same bound.
- **Complex:** ranks range from zero to n - 1 and need O(log n) bits. Each
  stable bit pass uses at most n pushes/rotations plus n pushes back, giving
  O(n log n) instructions.

These bounds count allowed stack instructions, not internal C work. Computing
disorder takes O(n squared) comparisons; preparing the medium/radix sorted
copy uses insertion sort with O(n squared) comparisons. Array shifts and rank
lookups also add runtime work but do not emit extra stack instructions.

The two stack buffers use O(n) space. Simple uses O(1) additional workspace;
medium and complex allocate an O(n) sorted copy. Adaptive adds O(1) space beyond
the chosen method, so total space is O(n) in every regime.

[sort_stack](src/stack/stack_utils.c) emits nothing for already sorted inputs
and uses the existing small sorter for up to five values before dispatching
larger inputs. This fixed-size shortcut does not change the asymptotic bounds.
Direct calls to adaptive apply the disorder thresholds regardless of input size.
The cached disorder remains the initial measurement after sorting.

## Benchmark mode

Put `--bench` before the numeric arguments, optionally alongside a strategy:

```sh
./push_swap --bench --adaptive 3 2 1
```

Sorting instructions still go exclusively to stdout. After a successful sort,
stderr receives five lines in this format:

```text
disorder: 100.00%
strategy: Adaptive / O(nlogn)
total_ops: 2
sa: 1 sb: 0 ss: 0 pa: 0 pb: 0
ra: 1 rb: 0 rr: 0 rra: 0 rrb: 0 rrr: 0
```

The disorder is measured before sorting. The label is the requested strategy (Adaptive by default); its complexity
is the selected regime's bound. The existing small-sort shortcut remains
in place for up to five values and satisfies these bounds for its fixed size.
Sorted inputs report zero operations. Without `--bench`, no report is printed.
Invalid input or allocation failure prints only `Error` to stderr and exits
with failure; it does not produce a benchmark report.

Each emitted instruction is counted exactly once: `ss`, `rr`, and `rrr` do
not also increment their component operations. No-op calls that emit nothing
are not counted. Both stacks share the same counters; there is no global
benchmark state. Callers constructing stacks outside `main` must initialize
their `benchmark` pointers to NULL, or attach the same valid benchmark to both
using `init_benchmark`. The benchmark object must remain alive during sorting.

## Resources

- [Radix sort](https://en.wikipedia.org/wiki/Radix_sort):
  LSD sorting, digit passes, and why stable partitioning preserves earlier work.
- [Selection sort](https://en.wikipedia.org/wiki/Selection_sort):
  the minimum-extraction idea used by the simple strategy.
- [Inversion (discrete mathematics)](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)):
  the out-of-order pairs used to measure input disorder.
- [GNU Make manual](https://www.gnu.org/software/make/manual/make.html):
  build rules, dependencies, automatic variables, and cleanup targets.
- [POSIX write](https://pubs.opengroup.org/onlinepubs/9799919799/functions/write.html):
  writing instructions and diagnostics to file descriptors.
- [Doxygen documentation](https://www.doxygen.nl/manual/docblocks.html):
  documentation comments used in [push_swap.h](include/push_swap.h).

## Contribution
- Input parsing: ngrinchu (dzouhar)
- Operations: ngrinchu, dzouhar
- small sort: ngrinchu
- simple sort: ngrinchu
- medium sort: dzouhar (ngrinchu)
- complex sort: dzouhar (ngrinchu)
- adaptive: dzouhar
- disorder: ngrinchu
- benchmark: dzouhar (ngrinchu)
- main: dzouhar, ngrinchu

### AI assistance

AI assistance was used to explain C concepts and sorting algorithms, implement
and refactor parts of the program,eview parsing, add documentationmplementation agaclean up README.mdsubject;eplace that evaluation.

