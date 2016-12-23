

// Qt
#include <QTemporaryFile>

// std
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
    QTemporaryFile file;
    file.setAutoRemove(false);

    std::printf("Content-type: text/plain\r\n\r\n");

    if (file.open())
    {
        char * rawdata;
        char * imgPtr = nullptr;
        long lengthrd, imglength;

        imglength = lengthrd = std::atol(getenv("CONTENT_LENGTH"));
        rawdata = new char[lengthrd+1];

        std::printf("Content Length: %ld\n", lengthrd);

        fread(rawdata, lengthrd, 1, stdin);

        // now comes the loop, there are better ways but not that I can find quickly enough
        for (char * it = rawdata; it < (rawdata+lengthrd-4); it++)
        {
            imglength--;
            std::printf("%c", it[0]);

            if (it[0] == 13 && it[1] == 10 && it[2] == 13 && it[3] == 10 && (it[4] < 32 || it[4] > 127))
            {
                imgPtr = it+4;
                imglength -= 3;
                break;
            }
        }

        if (imgPtr)
        {
            std::printf("Writelength: %ld\n", imglength);
            file.write(imgPtr, imglength);
        }

        delete [] rawdata;

        std::printf("Upload Complete at %s\n", qPrintable(file.fileName())); // debug - comment out for live
        file.close();
    }
    else
        std::printf("The file couldn't be uploaded.\n");

    return 0; // exit
}
