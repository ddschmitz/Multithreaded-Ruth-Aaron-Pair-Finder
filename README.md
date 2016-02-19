# Multithreaded-Ruth-Aaron-Pair-Finder

### What Is A Ruth-Aaron Pair?

"a Ruth–Aaron pair consists of two consecutive integers (e.g. 714 and 715) for which the sums of the prime factors of each integer are equal" - [Wikipedia] (https://en.wikipedia.org/wiki/Ruth%E2%80%93Aaron_pair)

### Compile

`gcc Ruth-AaronV6.c - pthread`

### Modify The Program
If you want to modify how many threads it uses or how many pairs it checks, you need to edit the source code.  There are three main variables that you should modify:

`PRIMES` - How big the Sieve of Eratosthenes is.  This sieve holds the primes that the pogram needs.  
`THNUMS` - How many threads the program will use.                                                      
`PAIRS` - How many pairs the program will check.  If 100 is specified, the program will check all pairs up to 99 & 100.
	
NOTE:  Do not make the `PRIMES` variable a larger number than `PAIRS`.  If you do you will end up using the sieve to check if a number is prime and that number won't even be in the sieve!

### Test Results

I performed all of these tests on my desktop which has 16 GB of ram and uses an Intel i7-4790K.  For these results I ran the program five times and took the average of the different runs.  I checked all pairs up to 1,000,000 (1 & 2 - 999,999 & 1,000,000)

| # of threads  | Run Time (s)  | 
|:-------------:|:-------------:|
| 1             | 85.84992 |
| 2             | 56.61454      |
| 3             | 41.75345      |
| 4             | 33.55716 |
| 5             | 29.85537      |
| 6             | 27.09856      |
| 7             | 25.27791 |
| 8             | 24.11272      |
| 9             | 23.78475      |
| 10            | 24.13643      |
| 15            | 23.70623      |
| 20            | 23.01726      |
| 40            | 22.18094      |
| 100           | 21.92913      |
| 150           | 22.06507      |
