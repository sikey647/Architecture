
/* redis 数据类型
    string（简单动态字符串）
    list（双向链表、压缩列表）
    hash（哈希表、压缩列表）
    sorted set（跳表、压缩列表）
    set（哈希表、整数数组）
*/

/* redis 底层数据结构
    整数数组 O(N)
    双向链表 O(N)
    哈希表  O(1)
    压缩列表 O(N)
    跳表    O(logN)
*/

/* redis 键值组织结构
    全局哈希表保存键值对
    链表法解决hash冲突
    hash表的rehash
        两个hash表
        渐进式rehash: 将一次性大量的拷贝，分摊到多次处理请求的过程中，避免耗时操作，保证数据快速访问。
*/

/* list 操作
    lpush key string:  在key对应list的头部添加字符串元素，返回1表示成功，0表示key存在且不是list类型
    rpush key string:  同上，在尾部添加
    llen key: 返回key对应list的长度，key不存在返回0,如果key对应类型不是list返回错误
    lrange key start end: 返回指定区间内的元素，下标从0开始，负值表示从后面计算，-1表示倒数第一个元素 ，key不存在返回空列表
*/

/* set 操作
    sadd key member: 向名称为key的set中添加元素member
    srem key member: 删除名称为key的set中的元素member
    spop key: 随机返回并删除名称为key的set中一个元素
    srandmember key: 随机返回名称为key的set的一个元素，但是不删除元素
*/

/* hash操作
    
*/