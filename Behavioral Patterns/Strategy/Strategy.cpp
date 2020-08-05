class Strategy {
public:
    virtual ~Strategy() = default;
    virtual string Sort(const vector<string>& data) const = 0;
};

// 上下文维护具体策略的引用，仅通过策略的接口交互
class Context {
private:
    Strategy* strategy;
    vector<string> data;
public:
    Context(Strategy* s) : strategy(s) {};
    ~Context() {
        delete strategy;
    }
    void Set(const vector<string>& d){
        data = d;
    }
    void Run() {
        cout << strategy->Sort(data) << endl;
    }
    void Change(Strategy* s) {
        delete strategy;
        strategy = s;
    }
};

class Normal : public Strategy {
public:
    string Sort(const vector<string>& data) const override {
        string res;
        for (auto& s : data)
            res += s;
        sort(res.begin(), res.end());
        return res;
    }
};

class Reverse : public Strategy {
public:
    string Sort(const vector<string>& data) const override {
        string res;
        for (auto& s : data)
            res += s;
        sort(res.begin(), res.end(), greater<char>());
        return res;
    }
};

// 将特定策略传递给上下文
void Client() {
    Context* context = new Context(new Normal);
    context->Set(vector<string>{"c", "b", "d", "a", "e"});
    context->Run();
    context->Change(new Reverse);
    context->Run();
    delete context;
}

int main()
{
    Client();
    return 0;
}

/*

abcde
edcba
 
*/
