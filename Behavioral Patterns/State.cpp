class Context;

// 状态的方法可以由其他状态调用
class State {
protected:
    Context* context;
public:
    virtual ~State() = default;
    void set_context(Context* c) {
        context = c;
    };
    virtual void Handle1() = 0;
    virtual void Handle2() = 0;
};

// 上下文保存当前状态的引用
// 每次转移释放掉之前的状态
// 每个新状态设置上下文
class Context {
private:
    State* state;
public:
    ~Context() {
        delete state;
    }
    Context(State* s) : state(nullptr) {
        this->transfer(s);
    }
    void transfer(State* s) {
        if (state) delete state;
        state = s;
        state->set_context(this);
    }
    void ToB() {
        state->Handle2();
    }
    void ToA() {
        state->Handle1();
    }
};

class StateA : public State {
public:
    void Handle1() override {
        cout << "HOLD" << endl;
    }
    void Handle2() override;
};

class StateB : public State {
public:
    void Handle1() override {
        context->transfer(new StateA);
        cout << "B -> A" << endl;
    }
    void Handle2() override {
        cout << "HOLD" << endl;
    }
};

void StateA::Handle2() {
    context->transfer(new StateB);
    cout << "A -> B" << endl;
}

void Client() {
    Context* c = new Context(new StateA);
    c->ToB();
    c->ToA();
    
    delete c;
}

int main()
{
    Client();
    return 0;
}

/*

A -> B
B -> A

 */
