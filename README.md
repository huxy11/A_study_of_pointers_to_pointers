# C语言细节&技巧
## 指向指针的指针
Linux大神说这样用C写链表删除的都不懂指针：
```
	if (prev)
		prev->next = entry->next;
	else
		list_head = entry->next;
```
得这么用：
```
	*pp = entry->next"
```
于是我就趟枪了，不过乍一看的确很简洁优雅,还不太容易理解，就着手试着分析一下思路了。
普通人写的链表之所以有一个的判断，是因为当删除链表头时情况特殊。于是一个简单的统一化思路就是在表头前加一个哨兵结点。但哨兵节点其他的空间就有点浪费了，又于是，我们普通人会以尽量利用这些空间存一点信息（如链表长度等）这样聊剩余无的手段改进一下。
```
	struct node *pre;
	for (pre = sentinel; pre->next;)
		if (condition)
			prev->next = pre->next->next;
		else
			pre = pre->next;
```
而Linus的方法，则是再进一步，不用一个节点当sentinel,而是用链表的head指针。
```
	struct node **cur;
	for (*cur = &head; **cur;) {
		if (condition) 
			*cur = (*cur)->next;//remove
		else
			cur = &(*cur)->next;
	}
```
分析下来，其实并不难理解，也没有高深的地方。不过倒挺有启发性的。
