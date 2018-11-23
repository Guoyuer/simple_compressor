# simple_compressor
数据结构第三次实验。只对英文ASCII文件有效  
采用CLion IDE编写  
可能是学习C++的时候没有研读经典著作，在编写这个程序时被IO操作弄的痛不欲生  
哈夫曼树在理论上支持二进制文件（即任意文件类型的文件）的压缩。但因为对IO操作不熟，这几天已经花了太多的时间了，且这与核心算法无关。故以后有空再加入。  
  
  
不足：  
1.只支持英文ASCII文件  
2.没有用优先队列建哈夫曼树，而是用了链表，效率偏低  
3.内部结构逻辑略微混乱，数据结构占内存  
4.压缩后变成了两个文件

编写程序时注意事项：  
- IO尤其要注意。因为CPU以字长为单位进行操作，所以读写文件时有八位的限制。在本程序中，借用Stack Overflow上的思想，每次集齐八位再写一个字节。  
- 解压和压缩时都需要建一次树。建树所需信息是字符及其出现频次。
