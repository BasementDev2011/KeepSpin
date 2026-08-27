#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/select.h>
#include <stdlib.h>
#include <signal.h>

#define KEEP_SPIN_VERSION "V1.0"
#define STATE_SEED 873212
int fd;

unsigned int hex_shift(unsigned int state) {
    state ^= state << 13;
    state ^= state >> 6;
    state ^= state << 11;
    state ^= state >> 17;
    return state;
}

void signal_handle(int sig) {
    printf("\nReceived signal %d\n",sig);
    if (sig == SIGINT) {
        printf("Closing program\n");
        close(fd);
        exit(0);
    }
}

int KeepAliveOperation(const char *device, unsigned int time) {
    unsigned long int state = hex_shift(STATE_SEED); //Random enough to not be cached by firmware.
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
    state = state * size;
    unsigned int mod_state = state % size;
    printf("Total size %jd\n",size);

    signal(SIGINT,signal_handle);
    while (1) {
        state = hex_shift(state);
        mod_state = state % size;

        if (lseek(fd, mod_state, SEEK_SET) == (off_t)-1) {
            perror("lseek");
            return 1;
        }
        if (read(fd,&byte,1) < 0) {
            perror("read");
            close(fd);
            return 1;
        }
        printf("Reading at %jd Byte %02X PRNG (Raw) State: %lu\n",(intmax_t)mod_state,byte,state);
        sleep(time);
    }

}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Too little arguments\n");
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
    printf("KeepSpin %s",KEEP_SPIN_VERSION);
    printf("Device: %s\n",argv[1]);
    printf("Wait time %s\n",argv[2]);
    KeepAliveOperation(argv[1],wait_time);
    return 0;
}
