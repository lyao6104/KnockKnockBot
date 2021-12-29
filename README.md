# KnockKnockBot
 
## How to use
    To use the program, run the executable file located in the "Executable" folder.
    When adding jokes, please use the program to do so, and don't modify any of the text files in "Resources"
    When the program asks you whether you find a joke funny, respond with one of these phrases if you found it funny:
        "yes", "y", "sure", "i guess", "definitely" (Should be case insensitive)
    Please avoid the use of semicolons in your jokes. Or else the program will probably break. I might add something to prevent that later.

## How it works
    Basically, each joke in the program's library is split into a "starter" and a "punchline", which each 
    have "funnyness" values associated with them. These values increase when the program tells you a joke that you find funny.
    Using these values, the program randomly picks a starter and a punchline, and tells you a joke, then asks you whether or not you found it funny.
    You can also tell a joke to the program. If it's an original joke, the program will store it in its library, and it might tell it to you some time.

## ...Why?
    Why not?

## Some other stuff
    This program was written in the Code::Blocks IDE, and compiled using GCC.
    If you want to compile it yourself, make sure to set the C++11 compiler flag as well.