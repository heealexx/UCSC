To use the program, type "make" into the command line. This will make and merge all the necessary object files into an executable called sequence. To run sequence, type "./sequence", followed by any flags you would like to include. 
-s prints out the primes and if it is special
-p prints out primes that are palindromes for base 2, 10, 14, and my last name + 10, which is 18
-n <input> will take the input and set it as the number of primes in the list. Default is 1000

INFER ERRORS
Memory leak: This memory leak error occurs because the compiler thinks that the memory allocated by bitvector and its vector will not be freed. However, in my sequence code, I do free it in the end, so this error can be ignored and can be taken as a reminder to free the allocated memory.
Running valgrind said it had zero memory loss.
