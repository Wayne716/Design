![](Mediator.png)
<br>

从对象之间的交互变成与对象与中介的交互

*From:*
```cpp
struct Node {
    ...
private:
    Node* next;	
};
```

*To:*
```cpp
struct Node {
    ...
private:
    Mediator* mediator;
};
```
