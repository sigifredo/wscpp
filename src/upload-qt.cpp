

#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
    FILE *fd;
    char *rawdata;
    char *data = nullptr;
    long lengthrd;
    long imglength; // use for the length of the write

    std::printf("Content-type: text/plain\r\n\r\n");

    fd = fopen("/tmp/file.dat","wb+"); // open the output file

    imglength = lengthrd = std::atol(getenv("CONTENT_LENGTH"));

    std::printf("Content Length: %ld\n", lengthrd);

    rawdata = new char[lengthrd+1];

    fread(rawdata, lengthrd, 1, stdin);

    // now comes the loop, there are better ways but not that I can find quickly enough
    for (char * it = rawdata; it < (rawdata+lengthrd-4); it++)
    {
        imglength--;
        printf("%c", it[0]);

        if ( (it[0]==13) && (it[1]==10) && (it[2]==13) && (it[3]==10) && ( (it[4]<32)||(it[4]>127) ) )
        {
            data = it+4;
            imglength -= 3;
            break;
        }
    }

    if (data)
    {
        printf("Writelength: %ld\n", imglength); // yet another debug

        // write the data to the file
        fwrite(data, 1, imglength, fd);
    }

    // close the file
    fclose(fd);

    delete [] rawdata; // free memory

    std::printf("Upload Complete"); // debug - comment out for live

    return 0; // exit
}
