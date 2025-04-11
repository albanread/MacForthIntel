## Novel Safety features of this MacForth language

This is a FORTH inspired language, and FORTH is not memory safe at all.

A goal of this FORTH is increased safety, please do not crash while I am writing my program.

FORTH is full of words that poke bytes into memory, or read bytes directly from memory addresses.

A mistake in one of the parameters of these words will cause a crash.

These crashes are caught by the signal handler, and FORTH memory state is reset.

But this does not mean you are ok to continue, with some possible memory corruption.

The words most prone to crash are in the UNSAFE dictionary, and highlighted in red when you 
show words, FORTH allows you to do anything, this is just a warning to be cautious and consider alternatives.


### Safe memory allotment

Some FORTH words expect to be able to poke bytes into the dictionary following the latest word.

These words can be used to create look up tables, and layout structures of any kind in memory.

This is a nice feature, in this implementation there is no global data space in a dictionary.

```FORTH

VARIABLE UPC 32 ALLOT  
26 C, 65 C, 66 C, 67 C, 68 C,
69 C, 70 C, 71 C, 72 C, 73 C,
74 C, 75 C, 76 C, 77 C, 78 C,
79 C, 80 C, 81 C, 82 C, 83 C,
84 C, 85 C, 86 C, 87 C, 88 C,
89 C, 90 C, 
```

That was a not very efficient way to create the string A..Z.

Tip: 

```FORTH
 S" ABCDEFGHIJKLMNOPQRSTUVWXYZ" UPC PLACE 
```
also works

Either way this is a counted string, so you can use
```FORTH
 UPC COUNT TYPE
 ``` 
to display it.

Lets discuss the implementation of ALLOT and C, 

ALLOT allocates a block of dynamic memory to the last word created.

You can 
```FORTH 
SHOW ALLOT
```
to see all the alloted memory.

You can 
```FORTH
SEE UPC
``` 
to look at the word, and you will notice the word has a data pointer
as well as a capacity and an offset field.


C, will set bytes in order, in the words alloted memory, by checking the remaining capacity, and using the offset.

So the code appears to work as it does in a standard FORTH global dictionary.

The reason this is safe, is that we are checking that there is room in the memory block, and we will raise an exception if there is not.

This implementation will also allow you to resize the memory, by using the allot command again, which is not standard.







