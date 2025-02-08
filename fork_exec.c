#include <stdio.h>   
#include <unistd.h>  
int main() {
    int f = fork();  

    if (f == 0) {  
        execl("./hello", "hello", (char*)NULL);  
    } else {  
        printf("Soy el proceso padre. PID: %d\n", (int)getpid());
        execl("./hello", "hello", (char*)NULL);  
    }
    return 0;
}
