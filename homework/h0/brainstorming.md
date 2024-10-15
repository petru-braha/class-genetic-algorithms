## components:

- constant
	- dimension (2 or 10)
	- sample number (30)
	- number of threas

- setting
	- best improvement
	- first improvement
	- worst improvement		

- function
	- minimum
	- maximum
	- implementation

- execution
	- deterministic - not now
	- heuristic
		- hill climbing
		- simulated anneling - not now

- threads
- clock
- printer
	- results
	- error statements
	- default

- bitstring
- random numbers

## theory:

- long double is not portable for every compiler
- <ranges> lib is C++2O

- mersenne prime number = prime number == 2^x - 1, x belongs to Z
- mersenne twister = random number generator, floting points number = mersenne prime number
- mt19937
	- 2^19937 - 1
	- 32-bit word length

- implementation
	- std::mt19937
	- std::bernoulli (1/2)
	- std::thread::hardware_concurrency

- heuristic executions == 24 == 4 functions * 2 dimensions * 3 improvement types
- each execution
	- has 30 values ==  30 numbers * dimension
	- one thread
	- one result file

- N == to be tested values' number 
- SAMPLE_NUMBER == 30
	- each has N values
		- each has dimension numbers
	- actual number of values = SAMPLE_NUMBER * N * dimension
		- worst case == 10.000 * 30 * 10

## what can be improved:

- random number function improvement
- thread manipulation
- to print

|specifications && statistics|function|dimension|improvement|
|----------------------------|--------|---------|-----------|
|average time 		     |        |		|	    |
|best solution		     |	      |		|	    |
|average solution	     |	      |		|	    |
|worst solution		     |	      |		|	    |

## what could be done differently:

- no conversion betwen double and bitstring, generating bitstrings

## questions:

- deterministic approach?
