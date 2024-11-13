# h1:
## components:

- constant
	- sample number (30)
	- precision (5)
	- number of threas
	- dimension (30, 100)
	- setting (best, first, worst)			

- function
	- minimum
	- maximum
	- implementation

- algorithm
	- hill climbing
	- simulated anneling

- threads
- clock
- printer
- bitstring
- random numbers

## details:

- heuristic executions == 24 == 4 functions * 2 dimensions * 3 improvement types * 2 algorithm type
	- each has a SAMPLE_NUMBER == 30
		- each has N values
			- each has dimension numbers

- ceil(log2(N)) == nr of bits per dimension / number

## sa:

- value_candidate - local_optimum => how much worse is the current candidate compared to our best (worse => lower prob of getting accepted)
- temperature can only decrease
- high temperature => high probability => exploration 

- finding a cooling schedule is hard
- how to choose parameters ?
- attempt ?

- how to choose cooling schedule?
- how to choose treshold?
- how to choose stagnation number	

## model of raport:

|specifications && statistics|function|dimension|improvement|
|----------------------------|--------|---------|-----------|
|average time 		     |        |		|	    |
|best solution		     |	      |		|	    |
|average solution	     |	      |		|	    |
|worst solution		     |	      |		|	    |

## to do:

- random between 0 1
- simulated annealing
- idea of constexpr: of dimension no more pointers
- order of function
- try blocks
- change names of var

# h2:
- meta-GA
- same functions

- i won't consider a singleton a good pattern for projects. one time use => functional programming