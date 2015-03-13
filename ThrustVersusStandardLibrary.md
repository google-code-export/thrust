While Thrust's functionality is similar in many respects to familiar algorithms and containers from C++'s standard library, there are subtle and important differences. We document a non-exhaustive list of these here.

# Algorithm Semantics #

Unlike Thrust, C++'s standard algorithms library assumes an environment where serial processing is the norm, and parallel processing the exception. The semantics of many of standard C++'s algorithms reflect those considerations. In a parallel setting, some of these semantics are too restrictive or otherwise impossible to satisfy.

**`std::for_each` versus `thrust::for_each` and `thrust::for_each_n`**

> `std::for_each` assumes the function object contains state which will be mutated inside a serial loop. It returns a copy of this state as a result.

> `thrust::for_each` and `thrust::for_each_n` instantiate many copies of the function object in parallel. In parallel, shared mutable state within the object is a performance hazard at best, and impossible at worst. Instead, `thrust::for_each` and `thrust::for_each_n` return a copy of its `last` iterator parameter for consistency with other algorithms.

**`std::accumulate` versus `thrust::reduce`**

> `std::accumulate` operates by initializing an accumulator variable `acc` and repeatedly executing the read-modify-write: `acc = binary_op(acc, *iter)`. These semantics are implicitly serial and allow the user-specified `binary_op` to be non-associative and non-commutative.

> `thrust::reduce` requires associativity and commutativity of its user-specified `binary_op`. Stricter requirements enable parallelization.

> `thrust::reduce` also adds an overloaded variant which omits the `init` parameter, which implicitly assumes the result type is constructible from `0`.

**`std::inner_product` versus `thrust::inner_product`**

> Like `thrust::reduce`, `thrust::inner_product` requires associativity and commutativity of its user-specified `binary_op` and also adds an overload which assumes an implicit `0` {{{init}} parameter.

**`std::partial_sum` versus `thrust::exclusive_scan` and `thrust::inclusive_scan`**

> Like `std::accumulate`, `std::partial_sum` is defined in terms of serial summation on an accumulator variable, which allows freedom from associativity and commutatitivity. By contrast, Thrust's prefix sums `thrust::exclusive_scan` and `thrust::inclusive_scan` require associativity and commutativity of their user-defined `binary_op`s and introduce overloads to capture common use cases.

**key-value algorithms**

> Thrust's `_by_key` algorithm variants such as `thrust::sort_by_key` have no analogue in the C++ Standard Library but are important for capturing, exploiting, and accelerating common use cases.

# Data Structures #

C++'s memory model assumes that any function may dereference any pointer and receive a well-defined result. This is too restrictive for heterogeneous system architectures which present a partitioned view of memory resources (e.g., CUDA).

**raw memory versus tagged memory**

> "Tagged" primitives such as `thrust::device_ptr` and `thrust::device_reference` allow programmers the use of terse, familiar expressions for manipulating objects which may physically exist in a remote memory. These primitives embed the object's heterogeneous system association in the C++ type system and allow dispatching onto system-specific algorithm implementations.

**`std::vector` versus vectors with an associated system**

> Thrust's system-specific vector containers (e.g., `thrust::cuda::vector`) provide a standard interface to a managed, tagged range of objects. Unlike these containers, `std::vector` has no notion of system association.

**`std::map`, `std::list`, etc. currently have no Thrust analogues.**

> C++'s assumption of a mostly serial execution environment is also reflected in the variety of data structures offered in its standard library. Few of these are appropriate in a massive data parallel environment.

> Instead, Thrust provides variants of a single random access, resizable container because this data structure is most amenable to data parallel algorithms. Many standard containers have implicitly serial semantics (e.g., `std::list`). Algorithms which manipulate them cannot be mapped onto data parallel implementations. Others (e.g., std::map) may be accessed in parallel, but assume either a single or small set of mutators. Thrust algorithm implementations assume the presence of very wide data parallelism. Shared mutable state becomes a performance hazard at such scales.