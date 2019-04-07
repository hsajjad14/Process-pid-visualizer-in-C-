# Process-pid-visualizer-in-C-

### To compile run 'make'.

#### To run on the proc directory:

change the flag in the Makefile to uncomment FLAGS = -Wall -Werror -g -std=gnu99 -DTEST

and comment FLAGS = -Wall -Werror -std=gnu99

An example of how it organizes the process, each number is the process id, with it's name next to it, and each indent represents a child.

<img width="166" alt="Capture" src="https://user-images.githubusercontent.com/40809349/55680006-47162e80-58e2-11e9-8ed9-07476cfcf362.PNG">

