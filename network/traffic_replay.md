<!-- MarkdownTOC -->

- [Goreplay](#goreplay)
  - [Forwarding to multiple addresses](#forwarding-to-multiple-addresses)
  - [Splitting traffic](#splitting-traffic)
  - [Tracking responses](#tracking-responses)
  - [Traffic interception engine](#traffic-interception-engine)
- [TCPDump](#tcpdump)
- [TCPCopy](#tcpcopy)
- [References](#references)

<!-- /MarkdownTOC -->



# [Goreplay](https://github.com/buger/goreplay/wiki/Capturing-and-replaying-traffic)
__--output-xxx__
```
sudo ./gor --input-raw :8000 --output-stdout

sudo ./gor --input-raw :8000 --output-http http://staging.env

sudo ./gor --input-raw :8000 --output-file=requests.gor
```

__--input-file__
```
./gor --input-file requests.gor --output-http="http://localhost:8001"
```

### Forwarding to multiple addresses
You can forward traffic to multiple endpoints.

```
gor --input-tcp :28020 --output-http "http://staging.com"  --output-http "http://dev.com"
```

### Splitting traffic
By default, it will send same traffic to all outputs, but you have options to equally split it (round-robin) using __--split-output__ option.

```
gor --input-raw :80 --output-http "http://staging.com"  --output-http "http://dev.com" --split-output true
```
### Tracking responses
By default __input-raw__ does not intercept responses, only requests. You can turn response tracking using __--input-raw-track-response__ option. When enable you will be able to access response information in middleware and __output-file__.

### Traffic interception engine
By default, Gor will use __libpcap__ for intercepting traffic, it should work in most cases. If you have any troubles with it, you may try alternative engine: __raw_socket__.

```
sudo gor --input-raw :80 --input-raw-engine "raw_socket" --output-http "http://staging.com"
```


# TCPDump
# TCPCopy


# References
[github.com: goreplay](https://github.com/buger/goreplay)<br/>

[]()<br/>

[]()<br/>

[]()<br/>

[]()<br/>

[]()<br/>

[]()<br/>

[]()<br/>
