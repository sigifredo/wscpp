

#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
    FILE *fd;
    char *rawdata; // pointer for rawdata
    char *data; // will be an offset of rawdata after the two newlines
    long length; // length of data to be read used for malloc
    long writelength; // use for the length of the write
    char *pos; // used in the loop

    std::printf("Content-type: text/plain\r\n\r\n"); // for debug output
    // Various bits of debug output are included - comment out for live
    // and replace with whatever output you'd like to send to the client

    fd = fopen("/tmp/file.dat","wb+"); // open the output file

    length = std::atol(getenv("CONTENT_LENGTH"));
    writelength = length;

    printf("Content Length: %l\n", length);

    rawdata = new char[length+1]; // malloc required buffer

    fread(rawdata, length, 1, stdin); // read into buffer

    // now comes the loop, there are better ways but not that I can find quickly enough
    for (pos = rawdata; pos < (rawdata+length-4); pos++)
    {
        writelength--; // decrement the write length
        printf("%c", pos[0]); // used for debug output (comment out for live)

        if ( (pos[0]==13) && (pos[1]==10) && (pos[2]==13) && (pos[3]==10) && ( (pos[4]<32)||(pos[4]>127) ) ) // pattern to find two double-newlines
        {
            data = pos+4; // move data pointer forward 4 to start of actual data
            printf("Found\n"); // another debug line - comment out for live
            writelength-=3; // decrement writelength by three (done one already above for this loop)
            break;
        }
    }

    printf("Writelength: %u\n",writelength); // yet another debug

    // write the data to the file
    fwrite(data, 1, writelength, fd);

    // close the file
    fclose(fd);

    delete [] rawdata; // free memory

    std::printf("Upload Complete"); // debug - comment out for live

    return 0; // exit
}
