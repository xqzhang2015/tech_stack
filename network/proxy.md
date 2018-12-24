<!-- MarkdownTOC -->

- [Normal proxy: forward proxy](#normal-proxy-forward-proxy)
  - [nginx conf for forward proxy](#nginx-conf-for-forward-proxy)
  - [test: curl --proxy](#test-curl---proxy)
- [Reverse proxy](#reverse-proxy)

<!-- /MarkdownTOC -->
# Normal proxy: forward proxy
With client, to form a LAN.

## nginx conf for forward proxy

```sh
worker_processes  3;

events {
    worker_connections  1024;
}

http {
    server {
        listen       8888;
        server_name  localhost;

        location / {
            resolver 8.8.8.8;
            proxy_pass http://$http_host$uri;
        }
    }
}
```

## test: curl --proxy

Connecting to proxy first and then proxy server parsing the host and forward out.

```sh
curl -v --proxy 127.0.0.1:8888 http://github.com/xqzhang2015/tech_stack/blob/master/network/proxy.md
*   Trying 127.0.0.1...
* TCP_NODELAY set
* Connected to 127.0.0.1 (127.0.0.1) port 8888 (#0)
> GET http://github.com/xqzhang2015/tech_stack/blob/master/network/proxy.md HTTP/1.1
> Host: github.com
> User-Agent: curl/7.54.0
> Accept: */*
> Proxy-Connection: Keep-Alive
```

* tcpdump proxy server result

`sudo tcpdump -i lo0 -w test.pcap "port 8888"`

![proxy](../images/2018/proxy_tcpdump.png)

# Reverse proxy
With server, to form a LAN.
* Load balance
* Hide the existence and characteristics of an origin server or servers
* Application fire wall
* Caching: Reduce load on its origin servers by caching static content,
