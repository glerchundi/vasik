#include "TLog.h"

int TLog::nargs(const char *fmt) {
    int i, len, ret = 0;
    
    for(i = 0; fmt[i] != '\0'; ++i)
        if(validatechar(fmt, i)) 
            ret++;

    return ret;
}

// %[flags][width][.precision][length]specifier
int TLog::validatechar(const char *fmt, int i) {
    int n;
    char c;

    if(fmt[i] != '%')
        return 0;
    else {
        c = fmt[i+1];
        switch(c) {
            case 'c':
            case 'd': case 'i':
            case 'e': case 'E':
            case 'f':
            case 'g': case 'G':
            case 'o':
            case 's':
            case 'u':
            case 'x': case 'X':
            case 'p':
            case 'n':
                break;
            default:
                return 0;
        }

        if(i != 0) {
            int num_mods = 0;
            for(n = i; n >= 0 && fmt[n] == '%' ; n--)
                num_mods++;
            if(!(num_mods % 2))
               return 0;
        }
    }

    return 1;
}
/*
   void my_printf( char *format, ... ) {
     va_list argptr;
 
     va_start( argptr, format );
 
     while( *format != '\0' ) {
       // string
       if( *format == 's' ) {
         char* s = va_arg( argptr, char * );
         printf( "Printing a string: %s\n", s );
       }
       // character
       else if( *format == 'c' ) {
         char c = (char) va_arg( argptr, int );
         printf( "Printing a character: %c\n", c );
         break;
       }
       // integer
       else if( *format == 'd' ) {
         int d = va_arg( argptr, int );
         printf( "Printing an integer: %d\n", d );
       }
 
       *format++;
     }
 
     va_end( argptr );
   }
 
   int main( void ) {
 
     my_printf( "sdc", "This is a string", 29, 'X' );
 
     return( 0 );
   }
*/

void TLog::log(const char *file, const int line, const char *fmt, ...)
{
	FILE *fp;
	fp = fopen("debug.log","a+");
	
	int numargs;
	char text[1024], *trash;
	va_list ap;
	
	if(fmt == NULL)
		return;

    if(nargs(fmt)) {
	    va_start(ap, fmt);
	    vsnprintf(text, sizeof(text), fmt, ap);
	    va_end(ap);
	    fprintf(fp,"## %25s ## [%10i]: %s\n",file,line,text);
	    fclose(fp);
    }
    else {
        fprintf(fp,"## %25s ## [%10i]: %s\n",file,line,fmt);
    }
}
