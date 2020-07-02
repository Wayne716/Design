class Command {
public:
    virtual ~Command() = default;
    virtual void Execute() const = 0;
};

// 通过命令接口不与任何具体命令类相耦合
class SimpleCommand : public Command {
private:
    string payload;
public:
    SimpleCommand(string _p) : payload(_p) {}
    void Execute () const override {
        cout << this->payload << endl;
    }
};

class Receiver {
public:
    void Task1(const string &a) {
        cout << a << endl;
    }
    void Task2(const string &a) {
        cout << a << endl;
    }
};

class ComplexCommand : public Command {
private:
    Receiver* receiver;
    string a;
    string b;
public:
    ComplexCommand(Receiver* _r, string _a, string _b)
        : receiver(_r), a(_a), b(_b) {};
    void Execute() const override {
        receiver->Task1(a);
        receiver->Task2(b);
    }
};

class Invoker {
private:
    Command* start;
    Command* end;
public:
    ~Invoker() {
        delete start;
        delete end;
    }
    void SetStart(Command* _c) {
        start = _c;
    }
    void SetEnd(Command* _c) {
        end = _c;
    }
    void Task() {
        if (start)
            start->Execute();
        if (end)
            end->Execute();
    }
};

int main()
{
    Invoker* i = new Invoker;
    i->SetStart(new SimpleCommand("Simple"));
    Receiver* r = new Receiver;
    i->SetEnd(new ComplexCommand(r, "1", "2"));
    i->Task();

    delete i;
    delete r;

    return 0;
}
