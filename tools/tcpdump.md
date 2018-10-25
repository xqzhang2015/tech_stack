<!-- MarkdownTOC -->

- [tcpdump](#tcpdump)
  - [install](#install)
  - [Usage](#usage)

<!-- /MarkdownTOC -->

# tcpdump

## install

yum install -y tcpdump

## Usage

tcpdump -i eth0 host 100.65.223.18 -w src_1.pcap

tcpdump -i eth0 host 100.96.182.4 -w dst_1.pcap