/*
 The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function may be called multiple times.
*/

// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int readBytesCount = 0;
        bool eof = false;
        while (readBytesCount < n && !eof) {
            if (readSize == 0) { // buffer is empty
                readSize = read4(buffer);
                if (readSize < 4) {
                    eof = true;
                }
            }
            // copy buffer into buf
            int bytes = min(n - readBytesCount, readSize);
            cout << "bytes = " << bytes << endl;
            //copyArray(buffer, offset, buf, readBytesCount, bytes);
            int j = readBytesCount;
            int k = offset;
            for (int i = 0; i < bytes; i++) {
                buf[j++] = buffer[k++];
            }
            readBytesCount += bytes;
            readSize -= bytes;
            offset = (offset + bytes) % 4;
        }
        return readBytesCount;
    }
private:
    char *buffer = new char[4];
    int readSize = 0;
    int offset = 0;
};
