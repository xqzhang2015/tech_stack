<!-- MarkdownTOC -->

- [protobuf](#protobuf)
  - [Installing protoc](#installing-protoc)
    - [Mac OS X](#mac-os-x)
    - [Linux](#linux)

<!-- /MarkdownTOC -->

# protobuf

## Installing protoc

### Mac OS X

```sh
brew install protobuf
```

Alternately, run the following commands:
```sh
PROTOC_ZIP=protoc-3.3.0-osx-x86_64.zip
curl -OL https://github.com/google/protobuf/releases/download/v3.3.0/$PROTOC_ZIP
sudo unzip -o $PROTOC_ZIP -d /usr/local bin/protoc
rm -f $PROTOC_ZIP
```


### Linux

```sh
PROTOC_ZIP=protoc-3.3.0-linux-x86_64.zip
curl -OL https://github.com/google/protobuf/releases/download/v3.3.0/$PROTOC_ZIP
sudo unzip -o $PROTOC_ZIP -d /usr/local bin/protoc
rm -f $PROTOC_ZIP
```
