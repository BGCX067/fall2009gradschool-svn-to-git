KBAI Project 3 Readme
Puyan Lotfi

Easy Instructions:

Run ./buildandrun.sh on a linux machine. It should make clean, make, then run my aicop with all the correct options.

My Project 4 report is in Project4_Report.pdf.







Involved Instructions:

Compilation:

- To compile my project, just use the makefile. Just type "make" or "gmake" in the folder of my project.

The make output should look like this:

$ make
g++ -Wall -O0 -c -g main.cpp
g++ -Wall -O0 -c -g frame.cpp
bison -dv aicop.y
aicop.y:141.2: warning: empty rule for typed nonterminal, and no action
aicop.y: conflicts: 13 shift/reduce, 5 reduce/reduce
g++ -O0 -c -g aicop.tab.c -w
flex aicop.l
g++ -O0 -c -g lex.yy.c
g++ -Wall -O0 -g -o aicop main.o frame.o aicop.tab.o lex.yy.o -lfl -ly


- I expect that this is being compiled and run on a Linux machine with Flex and Bison installed (or lex and yacc).

Execution:

Aside from this readme and expectedoutput.txt, there are the following other inputfile.
Please use my aicop.txt, because I am not sure if it is completely untouched from the original (but it should be).

All the input files you will need are:

Stores events and fact inputs, from project 1:

-rw-r----- 1 puyan 6059 Oct 12 23:50 aicop.txt

Stores Scripts From Project 2:

-rw-r----- 1 puyan 1421 Nov  9 13:31 biological-weapon-development-plan.txt
-rw-r----- 1 puyan  626 Nov  3 16:53 discontinued-investigation-plan.txt
-rw-r--r-- 1 puyan 1564 Nov  9 13:31 disease-research-subplan.txt
-rw-r----- 1 puyan  736 Nov  3 16:52 illegal-lobby-plan.txt
-rw-r--r-- 1 puyan  299 Nov  8 19:08 goto-store-subplan.txt
-rw-r----- 1 puyan 1658 Nov  3 16:54 man-from-bushes-plan.txt
-rw-r----- 1 puyan 2073 Nov  3 16:54 mayoral-race-shenanigans-plan.txt
-rw-r----- 1 puyan 1077 Nov  9 21:29 research-fraud-plan.txt
-rw-r----- 1 puyan  872 Nov  9 10:53 robbers-dog-plan.txt
-rw-r----- 1 puyan 1132 Nov  3 16:52 voting-machine-contract-plan.txt
-rw-r----- 1 puyan  259 Nov  8 20:11 rob-store-plan.txt

Stores Sub-Scripts from Project 3:

-rw-r----- 1 puyan 1208 Oct 12 23:50 acplan1.txt
-rw-r----- 1 puyan  462 Nov  8 18:25 fake-id-subplan.txt
-rw-r--r-- 1 puyan  884 Nov  9 21:27 faked-research-subplan.txt
-rw-r--r-- 1 puyan 1129 Nov  8 20:57 rob-store-fraud-subplan.txt
-rw-r--r-- 1 puyan  242 Nov  9 10:45 run-away-from-subplan.txt
-rw-r--r-- 1 puyan  566 Nov  9 14:35 runaway-subplan.txt


Stores Meta Reasons and a tag that enables queueing of output until
the end of a chain, for Project 4:

-rw-r----- 1 puyan   45 Nov 24 18:04 enablemetaqueing.txt
-rw-r----- 1 puyan 5354 Nov 24 16:24 meta.txt


Run my aicop program like so:

./aicop aicop.txt rob-store-plan.txt  robbers-dog-plan.txt man-from-bushes-plan.txt voting-machine-contract-plan.txt research-fraud-plan.txt mayoral-race-shenanigans-plan.txt biological-weapon-development-plan.txt illegal-lobby-plan.txt discontinued-investigation-plan.txt enablemetaqueing.txt meta.txt


If you have any questions or concerns please email me at puyan@gatech.edu.

The output for my aicop program should look like what is in expectedoutput.txt

Finally, my report for project 3 should be in Project4_Report.pdf.
I also included my reports from Project 2 and 3.



Thanks

-Puyan
