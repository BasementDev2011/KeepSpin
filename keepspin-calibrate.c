#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/select.h>
#include <stdlib.h>
#include <inttypes.h>

#define KEEP_SPIN_CALIBRATE_VERSION "V1.0"

unsigned int wait_time_calibrate() {
    //whhyyyy
    unsigned int seconds = 0;
    for (seconds = 1; ; seconds++) {
        if (seconds > 4294967) {
            printf("Wait time is too long");
            exit(1);
        }

        fd_set input;
        FD_ZERO(&input);
        FD_SET(STDIN_FILENO, &input);

        struct timeval timeout = {
            .tv_sec = 1,
            .tv_usec = 0
        };

        int result = select(STDIN_FILENO + 1, &input, NULL, NULL, &timeout);

        if (result > 0) {
            getchar();
            break;
        }

        if (result == 0) {
            printf("%u seconds\n", seconds);
            fflush(stdout);
        }
    }
    if (seconds < 9) {
        printf("Invalid waiting time\n");
        exit(1);
    }
    return seconds;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Must specify block device (e.g : '/dev/sr0')\n");
        return 1;
    }
    unsigned char byte;
    printf("KeepSpin-Calibrate %s",KEEP_SPIN_CALIBRATE_VERSION);
    printf("Performing time out calibration\n");
    int fd = open(argv[1],O_RDONLY);
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

    printf("Total size %jd\n",(intmax_t)size);

    lseek(fd,size / 2,SEEK_SET);
    if (size == (off_t)-1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    if (read(fd,&byte,1) < 0) {
        perror("read");
        return 1;
    }

    printf("When the disc stops spinning, press ENTER\n");
    unsigned int timeout = wait_time_calibrate();
    timeout -= 8;
    printf("Use this timeout : %u\n",timeout);

    if (close(fd) < 0) {
        perror("close");
        return 1;
    }
    return 0;
}
