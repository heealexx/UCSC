To use the program, type "make" into the command line. This will make and merge all the necessary object files into an executable called pathfinder. To run pathfinder, type "./pathfinder" into the command line with any flags you would like to include. The default will read from the keyboard. To stop reading, press CTRL+ D, and pathfinder will run with the inputted junctions. 
-i <inputfile> will read the from the file provided
-d will make the graph directed
-u will make the graph undirected (default)
-m will print the graph

INFER ERRORS:
From what I could gather from Piazza, infer sends out an error when I allocate memory that it thinks I will not free. However, I am going to free the stack, so these NULL DEREFERENCE errors can be ignored.

DEAD STORE:
From the assignment page, stackpop uses a pointer parameter to pop the value into the pointer, but in the actual function it never gets used. This gives out an error to infer, but can not be worked around because it is what Prof Long required. Does not affect outcome of the program.
