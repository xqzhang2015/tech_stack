### how to check if a port is opened(or ocuppied)? And then kill?
* lsof - list open files
* An open file may be a regular file, a directory, a block special file, a character special file, an executing text reference, a library, a stream or  a  network  file (Internet socket, NFS file or UNIX domain socket.)
* -i [i]   selects the listing of files any of whose Internet address matches the address specified in i.  If no address is specified, this option selects  the  listing of all Internet and x.25 (HP-UX) network files.
```
An Internet address is specified in the form (Items in square brackets are optional.):

                [46][protocol][@hostname|hostaddr][:service|port]
```
Example
```
➜  ~ lsof -i :7777
COMMAND     PID    USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
AdServerR 43027 xqzhang    3u  IPv6 0xfc83dc0e547207f7      0t0  TCP *:cbt (LISTEN)
➜  ~ lsof -i :6321
COMMAND     PID    USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
AdServerR 43041 xqzhang    3u  IPv6 0xfc83dc0e4858a7f7      0t0  TCP *:emp-server1 (LISTEN)
```

<br/>
### traceroute
In computing, traceroute is a computer network diagnostic tool for 
* displaying the route (path) and
* measuring transit delays of packets across an Internet Protocol (IP) network.
