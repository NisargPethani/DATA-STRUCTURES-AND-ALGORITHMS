# HTTP based simple FTP client server functionality

- Build a simple file server using HTTP protocol having functionality similar to FTP client and FTP server where communication will be among client and server. 
- The client could be a command line interface or a web browser. 
- Only HTTP over sockets to be used, use of any other library is not allowed though you are free to use any language.

## Directory Structure of Server:
- Server will contain sub-directories corresponding to different URLs.
- Those sub-directories will contain files which are requested by the client (further sub-directories handling is not expected). One such example for reference is below. Here site1/file1.extension should return file1.extension from site1 sub-directory.

## Use Cases:
1. Request from client to server using browser/command line.
    1. Input for command line: `GET site1/filename.extension`
    2. Input for browser: `ip:port/site1/filename.extension`
2. Extract URL, map the initial part of the URL (host name and first part post that) to directory structure, get full file path using rest of URL. Load file and return response as HTTP or appropriate error message.
3. Server must be asynchronous where multiple clients can request files and same can be executed by server.
4. File upload from client is not required.
5. File formats to be supported: txt, pdf and mp4.

## Ouptput Screenshots
1. [Client as Command Line Interface](output/client_as_Terminal.pdf)
1. [Client as Browser](output/client_as_Browser.pdf)