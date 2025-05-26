# C Copy API for kdb+ 
Copy function written in C for kdb+ using KX C API.

A problem faced when running system commands with peach is that you get a sys error thrown. 
This can be avoided by replacing the system"cp" with a C function that has been loaded into kdb+.
Using the C API we can also specify some extra low level parameters such as buffer size for the copy function.

PRE-REQUISITES 
Ensure k.h and c.o are in $QHOME/c
(You can find them via the following links -> 
https://github.com/KxSystems/kdb/blob/master/c/c/k.h 
https://github.com/KxSystems/kdb/blob/master/m64/c.o)

TO COMPILE (on macos)
Download copy.c from this repo and run the below with it in the current directory.
gcc -bundle -undefined dynamic_lookup -DKXVER=4 -I $QHOME/c copy.c -o libcopy.so

Before starting q you will then want to copy libcopy.so into $QHOME/m64

TO TEST FROM Q
Start q with 2 slaves and a file call source.txt in the current directory.

///// HIGHLIGHTING THE PROBLEM /////
q) func:{[destName] system"cp source.txt ",destName}
q) func peach ("dest1.txt";"dest2.txt")
-> Throws a "sys" error

///// SOLUTION WITH C API FUNCTION /////
q) systemCp:`libcopy 2: (`copy_file;3)
q) func:{[destName] systemCp[`source.txt;destName;1000i]}
q) func peach `dest1.txt`dest2.txt
-> no error thrown
-> buffer of 1000 bytes specified and can be adjusted as seen fit
-> type error thrown if source/dest params are not symbols and buffer is not integer



