#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "string.h"
#include "stdlib.h"
int main(int argc, char *argv[]) {
    static char user_data[] = "user data";
    if (argc != 3){
        printf("error usage at least 2 arguments: device_file operation num: write 1; read 0;\n");
        return -1;
    }
    char * filename = argv[1];
    int fd;
    char read_buf[200],write_buf[200];
    // open device file
    fd = open(filename, O_RDWR);
    if (fd < 0){
        printf("open %s failed!\n", filename);
        return -1;
    }
    if (atoi(argv[2]) == 1){
        memcpy(write_buf, user_data, sizeof(user_data));
        if (write(fd, write_buf, sizeof(user_data)) < 0){
            printf("write to %s failed!\n", filename);
            return -1;
        }
        else{
            printf("write to %s success! Data: %s\n", filename, write_buf);
        }
    }
    else if (atoi(argv[2]) == 0){
        if (read(fd,read_buf, 50) < 0){
            printf("read from %s failed!\n", filename);
            return -1;
        }
        else{
            printf("read from %s success! Data: %s\n", filename, read_buf);
        }
    }
    // close device
    if (close(fd) < 0) {
        printf("close %s failed!\n", filename);
        return -1;
    }   
    return 0;
}