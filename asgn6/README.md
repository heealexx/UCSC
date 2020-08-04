To use the newspeak program, type "make" into the command line. This will make and merge all necessary object files into an executable called newspeak. To run newspeak, type "./newspeak" into the command lind, followed by any of the following flags and input values you would like to include.

-s prints out statistics of the program
-h <input> sets hashtable size to input, default is 10000
-f <input> sets bloomfilter size to input, default is 2^20
-m will use the move-to-front rule
-b will not use the move-to-front rule, default is not use

INFER ERRORS:
All of the infer errors are produced by infer's thinking that the user will not be freeing up memory allocated by the program. However, this is untrue in the fact that I know that the memory allocated is freed.
