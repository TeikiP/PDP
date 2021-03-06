-- Inshi No Heya and Hashiwokakero game solver --

INSTALL :

To compile both solvers, just run "make" at the root of this directory.
If you want to compile only one of those solvers, simply go in the solver directory then run "make".


UNINSTALL :

You can use "make cleanall" to remove any binary files you've made. As for the installation, you can
do it for both solvers at once or only one.


------ How to use Hashiwokakero ------

CREATING A GRID :

The encoding used for Hashiwokakero is fairly simple : just create a plain text file and create your grid using
thoses characters (each line in the file being a line on the graph):

- _ for an empty slot
- A number between 1 and 8 to indicate the value of the island.

Any other character will result in a "invalid character" error.

USING THE BINARY :

You can resolve a grid by calling the Hashiwokakero binary file and using the path of the grid file as an argument to the -f option.
Example : "./hashiwokakero -f ../test/test1.txt"

Some test grids are bundled with the sovler. See the test directory to find them. You can also launch "make testsolve" to automate them.

A grid can be generated using the -g argument to enable the generator mode. Three arguments are needed :

-s X where X is the size of the grid.
-i X where X is the number of islands.
-d X where X is the path to the file to be generated.

Example : "./hashiwokakero -g -s 10 -i 25 -d here.txt"

Three more non essentials options are available to use :

-o to specify the path where a file will be generated at the end of the solving of a grid, showing where the bridges were drawn.
-v for verbose mode. Gives a lot of info for each state.
-t as a timeout to end the program properly if the solver doesn't manage to find a solution.


------ How to use Inshi no Heya ------

HELP :

Usage recommendations et launch options can be found by using the help command with "./inshiNoHeya -h".


GRID FILE FORMAT :

In order to create a grid, you will need to add the following data into a new empty file :
- the size of the grid on the first line ("5x5" or just "5"),
- for each room, read from left to right and top to bottom in the grid, a line that tells its
  product value, 'b' if it goes downwards or 'r' if it goes rightwards, and its length (such as "6b2").

Each room has to be listed only once and on a line on its own.


USING THE SOLVER :

Similarly to Hashiwokakero, the solver can be called by giving it the path to the file containing the grid to solve.
Example : "./inshiNoHeya ../test/3x3_Generated".

Tests grids are provided within the test folder. Their names indicate their size and what makes them particular compared to the other grids, such as "Singles" for a grid that only has rooms of one cell or "Invalid" for a grid that is either not readable or not solvable. More information concerning the test grids can be found in the readme that is located within the test folder.


USING THE GENERATOR :

The generator can be called using the "-g [size]" option. Furthermore, if you intend to use the generated grid with the solver, you will want to save it to the input format within a file with "-i [input]".

Example : "./inshiNoHeya -g 5 -i grid.txt".

