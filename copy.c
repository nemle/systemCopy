#include <stdio.h>
#include <stdlib.h>
#include "k.h"

K copy_file(K source_path,K dest_path,K buffer_size) {

    // If type of param is not correct throw a type error
    if (source_path->t != -KS || dest_path->t != -KS || buffer_size->t != -KI) {
        return krr("type");
    }

    printf("Opening file object in read mode for source file\n");
    FILE *source = fopen(source_path->s, "rb");
    if (source == NULL) {
        return krr("Failed to open source file");
    }

    printf("Opening file object in write mode for destination file\n");
    FILE *dest = fopen(dest_path->s, "wb");
    if (dest == NULL) {
        fclose(source);
        return krr("Failed to open destination file");
    }

    int bufferSize = buffer_size->i;
    printf("Creating buffer of type char with size : %d\n",bufferSize);
    char buffer[bufferSize];
    int bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        printf("Bytes read from source : %d\n",bytes);
        if (fwrite(buffer, 1, bytes, dest) != bytes) {
            fclose(source);
            fclose(dest);
            return krr("Failed to write to destination file");
        }
    }

    printf("File copied successfully!");

    fclose(source);
    fclose(dest);

    // return boolean
    return ktj(-KB, 1);

}
