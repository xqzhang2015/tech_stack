### References
[The Secret Lives of Data: Raft](http://thesecretlivesofdata.com/raft/)<br/>

[Raft Paper](https://raft.github.io/raft.pdf)<br/>

### Concepts
1. This process is called *Leader Election*.
2. This process is called *Log Replication*.

### More
In Raft there are two timeout settings which control elections.
1. First is the *election timeout*.<br/>
The election timeout is the amount of time a follower waits until becoming a candidate. <br/>
The election timeout is randomized to be between 150ms and 300ms. <br/>
After the election timeout the follower becomes a candidate and starts a new election term...<br/>
* votes for itself...
* and sends out *Request Vote* messages to other nodes.
* If the receiving node hasn't voted yet in this term then it votes for the candidate...
* ...and the node resets its election timeout.
* Once a candidate has a majority of votes it becomes leader.

2 The leader begins sending out *Append Entries* messages to its followers.
<br/>
These messages are sent in intervals specified by the *heartbeat timeout*.<br/>
Followers then respond to each *Append Entries* message.<br/>
This election term will continue until a follower stops receiving heartbeats and becomes a candidate.<br/>

x. Requiring a majority of votes guarantees that <br/>
only one leader can be elected per term.<br/>
-- 不会脑裂<br/>
-- Let's take a look at a split vote example...: two nodes become candidates at the same time<br/>
x1. For nodes: A / B / C / D<br/>
<br/>-- Two nodes(A&B) both start an election for the same term...
<br/>-- Now each candidate has 2 votes and can receive no more for this term.
<br/>-- The nodes will wait for a new election and try again.
<br/>-- Node D received a majority of votes in term 5 so it becomes leader.
<br/>

### References
[The Raft Consensus Algorithm](https://raft.github.io)<br/>

[分布式一致性算法：Raft 算法（论文翻译）](http://www.cnblogs.com/linbingdong/p/6442673.html)<br/>

[Raft Paper](https://raft.github.io/raft.pdf)<br/>

[知乎：raft算法与paxos算法相比有什么优势](https://www.zhihu.com/question/36648084)<br/>

[PingCAP首席架构师唐刘：基于Raft构建分布式系统TiKV](http://www.sohu.com/a/114408897_465979)<br/>

[从etcd看Raft协议](http://qa.blog.163.com/blog/static/19014700220153155498735)<br/>

[raft.github.io: where can I get RAFT?](https://raft.github.io/)<br/>


[github: braft](https://github.com/brpc/braft)<br/>

[github: 360raft](https://github.com/Qihoo360/floyd)<br/>

[Consensus2 course: Replicated State Machines, RAFT](https://www.cs.princeton.edu/courses/archive/fall16/cos418/docs/L8-consensus-2.pdf)<br/>

[]()<br/>

[]()<br/>
