#include <fcntl.h> 
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

void overwriteFile(const char* filepath) {
    struct stat statbuf;

    if (stat(filepath, &statbuf) != 0) {
        perror("Error");
        return;
    }
    
    if (!S_ISREG(statbuf.st_mode)) {
        std::cerr << "Error" << std::endl;
        return;
    }

    int fd = open(filepath, O_WRONLY);
    if (fd == -1) {
        perror("Error");
        return;
    }

    size_t size = statbuf.st_size;
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error");
        close(fd);
        return;
    }

    std::vector<char> buffer(size, '\0');
    if (write(fd, buffer.data(), size) != size) {
        perror("Error");
    }

    close(fd);
}

void deleteFile(const char* filepath) {
    if (unlink(filepath) != 0) {
        perror("Error");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << argv[0] << std::endl;
        return 1;
    }

    const char* filepath = argv[1];

    overwriteFile(filepath);
    deleteFile(filepath);

    std::cout << filepath << std::endl;

    return 0;
}
