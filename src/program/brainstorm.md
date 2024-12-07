# h1:
## components:

- constant
	- sample number (30)
	- precision (5)
	- number of threas
	- dimension (5, 10, 30, 100)
	- strategy (best, first, worst, sa)			

- function
	- minimum
	- maximum
	- implementation

- clock
- printer
- threads
- random numbers
- bitstring

## details:

- heuristic executions == 64 == 4 functions * 4 strategy_types * 4 dimensions
	- each has a SAMPLE_NUMBER == 30
		- each has 10.000 iterations
			- each has dimension numbers
	- this number is not representative for the amount of time used by the algorithm
	- the different dimensions will have a major impact on time complexity

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

# h2:

- operators:
	- select
	- cross-over
	- mutate
	- switch
	- inverse 

## details:

- fitness function:

if(maximum_point)
	if(positive)
		fitness() = objective_function();
	if(negativa)
		fitness(x) = objective_function(x) + constant
else if(minimum_point)
	if(positive)
		fitness() = 1 / objective_function();
	else if(negativa)
		fitness() = -1 * objective_function();

- the function order is established by their computational dificulty (de jong 1's is the easiest => the first to be evaluated)
- meta-GA / gray code
- same functions => executions = 4 functions * 2 dimensions (8 VS 64)

- i won't consider a singleton a good pattern for projects. one time use => functional programming

## to do:

- converge cu adaptive mutation targeted pe biti nesemnificativi in faza de exploatare
- cross-over optimization
- cross-over with n cutting points
- mutation second variant easier faster
- if the algorithm stagnates => change parameters, don't stop
- parameter::fitness_function

- structure for bits
- constexpr for dimension => no more pointers
- 17 minutes on threads VS 6 minutes on one thread (am i braindead?)

- pgplot gnuplot
- stochastic error in sampling - chapter 4
- try blocks
- simulated annealing
- names of variables