# Lab 5
This lab implements:
- `ChainingHashMap` A hash map implementation which uses chaining to resolve hash collisions.
- `HashFunction` A basic hash function implementation.
- `ProbingHashMap` A hash map implementation which uses probing to resolve hash collisions.

Note that for this lab I had to implement a number of things which were outside the scope of the original Python labs. This includes a function which transforms a buffer into an `unsigned long long` type, effectively `Numberify` in the original Python labs, and the rest of the hash function class.

I also implemented a `Hashable` class which allows the use of template methods so that I can specify exactly how specific types should be transormed into a char buffer to be hashed.