# Multithreaded-Ruth-Aaron-Pair-Finder

### Compile

`gcc Ruth-AaronV6.c - pthread`

### Modify The Program
If you want to modify how many threads it uses or how many pairs it checks, you need to edit the source code.  There are three main variables that you should modify:

`PRIMES` - How big the Sieve of Eratosthenes is.  This sieve holds the primes that the pogram needs.  
`THNUMS` - How many threads the program will use.                                                      
`PAIRS` - How many pairs the program will check.  If 100 is specified, the program will check all pairs up to 99 & 100.
	
NOTE:  Do not make the `PRIMES` variable a larger number than `PAIRS`.  If you do you will end up using the sieve to check if a number is prime and that number won't even be in the sieve!

### Test Results


| # of threads  | Run Time      | 
| ------------- |:-------------:|
| 1      | right-aligned |
| 2      | centered      |
| 3    | are neat      |
| 4      | right-aligned |
| 5      | centered      |
| 6    | are neat      |
| 7      | right-aligned |
| 8      | centered      |
| 9    | are neat      |
| 0    | are neat      |
| 3    | are neat      |
# of threads	Run Time (s)
1	85.84992
2	56.61454
3	41.75345
4	33.55716
5	29.85537
6	27.09856
7	25.27791
8	24.11272
9	23.78475
10	24.13643
15	23.70623
20	23.01726
40	22.18094
100	21.92913
150	22.06507
