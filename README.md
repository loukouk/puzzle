# puzzle

This is an implentation of the 15 puzzle (https://en.wikipedia.org/wiki/15_puzzle),
as well as an implemtation of an AI that can solve the puzzle.

You can make the AI solve the puzzle, or solve it yourself using a command line interface.
For more info: "./[program_name] -h"

The performance of the AI was then measured (in number of moves) for different puzzle
sizes so that we could see its "big O" behavior.
(As expected, linearly if you only increase one dimension of the puzzle grid,
and quadratically if both dimensions are increased simultaneously).
