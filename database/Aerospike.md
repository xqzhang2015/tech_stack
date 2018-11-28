<!-- MarkdownTOC -->

- [Architecture](#architecture)
  - [Distribution: Data Distribution](#distribution-data-distribution)
    - [Partitions](#partitions)
    - [Data Replication and Synchronization](#data-replication-and-synchronization)
      - [Aerospike Cluster with No Replication](#aerospike-cluster-with-no-replication)
      - [Aerospike Cluster with Replication](#aerospike-cluster-with-replication)
  - [Distribution: Consistency](#distribution-consistency)
    - [Available mode](#available-mode)
    - [Strong Consistency mode](#strong-consistency-mode)
  - [Client API](#client-api)
- [Knowledge](#knowledge)
  - [CAP theorem](#cap-theorem)
- [References](#references)

<!-- /MarkdownTOC -->

Technology

# Architecture

Aerospike maintains shared-nothing simplicity.

## Distribution: Data Distribution

### Partitions

In the Aerospike Database, a namespace is a collection of data stored in the same way. Each namespace is divided into 4096 partitions, which are divided equally between cluster nodes. 

Aerospike uses a __random hashing__ method to ensure that partitions distribute evenly. There is no need for manual __sharding__.

Data records stay in the same partition their entire life. Partitions can move between servers, but should not be split.

### Data Replication and Synchronization

#### Aerospike Cluster with No Replication

In the Aerospike Database, having NO replicated data is replication factor = 1.

The Aerospike Smart Client is __location-aware__. It knows where each partition is located so that the data retrieval is achieved in __a single hop__.

#### Aerospike Cluster with Replication

Again, the Smart Client
* reads records and sends a request to the correct data master node for that record.
* write requests are also sent to the correct node.

* A write transaction includes both writing to master and writing to replica node.

When a node receives a write request, it saves the data and forwards the write request to the replica node. Once the replica node confirms a successful write and the node writes the data itself, a confirmation returns to the client.

## [Distribution: Consistency](https://www.aerospike.com/docs/architecture/consistency.html)

As per Eric Brewer's CAP theorem, Aerospike is, as of version 3.0, an __AP database__ - that is, one that provides avalability instead of consistency in various network partition situations. 

As of Aerospike 4.0, Aerospike supports both AP ( Available and Partition Tolerant ) as well as CP ( Consistent and Partition Tolerent ) mode. These modes can be configured on a namespace-by-namespace basis.

### Available mode

### Strong Consistency mode



## Client API
Aerospike C Client

Introduction


The Aerospike C client allows you to build C/C++ applications to store and retrieve data from the Aerospike cluster. The C client is a smart client that periodically pings nodes for cluster status and manages interactions with the cluster. The following functionality is supported.

* Database commands

** Key/Value

** Map/List collections

** Batch read

** Scan

** Secondary index query

** User defined Lua functions

* Both synchronous and asynchronous command models

Asynchronous model supports the following event frameworks.

** libev

** libevent

** libuv

* Thread safe API

* Shared memory cluster tend state for multi-process applications

* TLS secure sockets

# Knowledge

## CAP theorem

In theoretical computer science, the CAP theorem, also named Brewer's theorem after computer scientist Eric Brewer, states that it is impossible for a distributed data store to simultaneously provide more than two out of the following three guarantees:[1][2][3]

* Consistency: Every read receives the most recent write or an error
* Availability: Every request receives a (non-error) response – without the guarantee that it contains the most recent write
* Partition tolerance: The system continues to operate despite an arbitrary number of messages being dropped (or delayed) by the network between nodes



# References
[apidocs_c](https://www.aerospike.com/apidocs/c/)<br/>

[]()<br/>

[]()<br/>

[]()<br/>

[]()<br/>

[]()<br/>

[]()<br/>
