//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment 1.2
/*
Rewrite the program so that no #include directives are used in the program and so that the compiler doesn't
generate any warnings or errors. Hint: to do this, you will have to find the correct prototype for the printf
function in the stdio.h file and paste it in your program at the top.
*/

int printf (const char *__format, ...)
{
  register int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vprintf( __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}

int main()
{
    printf("Kyle Johnson\n");
    printf("\"");
    printf("Whoever fights monsters should see to it that in the process he does not become a monster. And if you gaze long enough into an abyss, the abyss will gaze back into you.");
    printf("\"");
    printf("\n~Friedrich Nietzsche");
    return 0;
}
