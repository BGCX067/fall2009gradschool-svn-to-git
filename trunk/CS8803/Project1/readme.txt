Aicop Readme
CS 8803
Puyan Lotfi

I used Steal Bank Common Lisp on my Macbook Pro to implement this. 
I read the file "aicop.txt"  for my input data, which is hardcoded, in my lisp code.

To get a list of causal chains just run:

sbcl --load aicop.lisp


But if you are using CLISP:

clisp
[1]> (load "aicop.lisp")


It should just print out the causal chains in a wierd format which I made up, like this:

---------- New Causal Chain ----------
----------
ACTION: SIGNED-CONTRACT
AGENT: REX-LUTHOR
OBJECT: VOTING-MACHINES
----------
ACTION: INSTALLED
OBJECT: VOTING-MACHINES
----------
ACTION: HAD-PROBLEMS
AGENT: VOTERS
OBJECT: VOTING-MACHINES
----------
ACTION: ASKED-TO-INVESTIGATE
AGENT: REX-LUTHOR
OBJECT: VOTING-MACHINES
----------
ACTION: PLEDGED-ANSWER
AGENT: REX-LUTHOR
OBJECT: VOTING-MACHINES

---------- New Causal Chain ----------
----------
ACTION: FOUNDED
AGENT: PHILIP-BOYNTON
OBJECT: BOYNTON-LABS
----------

...