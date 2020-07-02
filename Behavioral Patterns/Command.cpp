/*
 * 命令模式可以参数化对象，并且将命令放入队列中计划执行。
 * 命令类的成员变量包括参数和接收者的引用，构造函数以参数初始化。
 */


class Command {
public:
    virtual ~Command() = default;
    virtual void Execute() const = 0;
};

class Simple : public Command {
private:
    string payload;
public:
    explicit Simple(string p) : payload(p) {};
    void Execute() const override {
        cout << payload << endl;
    }
};

// 执行命令的具体方法
class Receiver {
public:
    void Task1(const string& a) {
        cout << a << endl;
    }
    void Task2(const string& b) {
        cout << b << endl;
    }
};


// 声明命令的执行方法
class Complex : public Command {
private:
    shared_ptr<Receiver> r;
    string a;
    string b;
public:
    Complex(shared_ptr<Receiver> _r, string _a, string _b)
        : r(_r), a(_a), b(_b) {};
    void Execute() const override {
        r->Task1(a);
        r->Task2(b);
    }
};


// 触发者不创建命令，成员包含命令的引用。
class Sender {
private:
    queue<shared_ptr<Command>> Q;
public:
    void Push(shared_ptr<Command> c) {
        Q.push(c);
    }
    void Run() {
        while (!Q.empty()) {
            Q.front()->Execute();
            Q.pop();
        }
    }
};

int main()
{
    // 接收者 -> 命令 -> 发送者
    shared_ptr<Sender> s = make_shared<Sender>();
    s->Push(make_shared<Simple>("simple command"));
    shared_ptr<Receiver> r = make_shared<Receiver>();
    s->Push(make_shared<Complex>(r, "a", "b"));
    s->Run();
}
