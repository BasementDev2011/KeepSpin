#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/select.h>
#include <stdlib.h>
#include <signal.h>

#define KEEP_SPIN_VERSION "V1.2"
int fd;

void signal_handle(int sig) {
    printf("\nReceived signal %d\n",sig);
    if (sig == SIGINT) {
        printf("Closing program\n");
        close(fd);
        exit(0);
    }
}

int KeepAliveOperation(const char *device, unsigned int time) {
    unsigned char byte; //Tiny enough for fast reads

    fd = open(device,O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    off_t size = lseek(fd,0,SEEK_END);
    if (size == (off_t)-1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    FILE *random_src = fopen("/dev/urandom","rb");
    if (random_src == NULL) {
        perror("fopen");
        return 1;
    }
    unsigned long int random_value;

    printf("Total size %jd\n",size);

    signal(SIGINT,signal_handle);
    while (1) {

        if (fread(&random_value,sizeof(random_value),1,random_src) == 0) {
            perror("fread");
        }
        if (lseek(fd, random_value % size, SEEK_SET) == (off_t)-1) {
            perror("lseek");
            return 1;
        }
        if (read(fd,&byte,1) < 0) {
            perror("read");
            close(fd);
            return 1;
        }
        printf("Reading at %lu Byte %02X RNG (Raw) State: %lu\n",random_value % size,byte,random_value);
        sleep(time);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Too little arguments\n");
        return 1;
    }
    if (argc > 3) {
        printf("Too many arguments\n");
        return 1;
    }
    char *endptr;
    unsigned long int wait_time = strtol(argv[2],&endptr,10);
    if (*endptr != '\0') {
        printf("Invalid wait time value\n");
        return 1;
    }
    if (wait_time < 1) {
        printf("WARNING: Wait time is too low, stopping program\n");
        return 1;
    }
    printf("KeepSpin %s\n",KEEP_SPIN_VERSION);
    printf("Device: %s\n",argv[1]);
    printf("Wait time %s\n",argv[2]);
    KeepAliveOperation(argv[1],wait_time);
    return 0;
}
