//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment 1.3
/*
    Write a new program that emulates some simple features of the PASCAL programming language solely by
    using the preprocessor. In PASCAL code groups are started and ended with begin and end rather than the
    curly-braces. The write statement allows a message to be printed without a newline following it and the
    writeln statement allows a message to be printed with a newline following it.
    The code below is what your main() function should look like.
    //Name:
    //Class:
    //Section:
    //Assignment:
    //Only #defines are allowed here in this program.
    //You should fill them in.
    main()
    begin
     write("first");
     write("line");
     writeln(" ");
     writeln("Name Here");
     writeln("'Your quote here.'");
    end
    Here is what your output should look like:
    firstline
    Name Here
    'Your quote here.'
    Note that you should actually put your name and a quote in the program in place of the “Name Here” and
    “Your quote here.” lines. Be sure to print out, demonstrate, and turn in each program. Also make sure that
    each of your programs include the proper comment block at the top
*/
#include <stdio.h>
#include <stdlib.h>

#define main() int main()
#define begin {
#define end return 0;}
#define write printf
#define writeln(x) printf(x"\n")

main()
begin
 write("first");
 write("line");
 writeln(" ");
 writeln("Kyle Johnson");
 writeln("'Whoever fights monsters should see to it that in the process he does not become a monster. And if you gaze long enough into an abyss, the abyss will gaze back into you.' ~Friedrich Nietzsche");
end

