#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>

struct termios orig_termios;

void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode(){
    
    tcgetattr(STDIN_FILENO, &orig_termios);

    struct termios raw;
    raw.c_iflag &= ~(IXON);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    atexit(disableRawMode);
}

int main(){
    enableRawMode();

    char c;
    while(read(STDIN_FILENO, &c,1)==1 && c != 'q'){
        if iscntrl(c){
            printf("%d \n",c);
            
        }else{
            printf("%d ('%c)\n",c,c);
        }
    }
    ;
    
    return 0;
}