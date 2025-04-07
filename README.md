# MacForthIntel
MacForthIntel

This is the intel X86_64 version of my MacForth, under development.

This FORTH is a non-standard compiler using ASMJIT.

The native core Forth words, have a generator function, that jits their code, and also creates the words
use by the interpreter.

Forth words are tokenized, the tokens are then optimized, allowing common FORTH word patterns to be replaced with more
efficient MACRO Words that the compiler then uses. This is limited but extensible.

This is a CMAKE project 
I use CLion IDE, with the JetBrains AI, but the original ideas have a fully human origin.

This is an excercise in LLM coding with the JetBrains AI, and cognitive therapy for me, as the human collaborator.

Selfie 
