class Singleton {
private:
    // 单例的实例必须是静态类型
    static Singleton* singleton;
    static mutex m;

protected:
    // 构造函数必须是私有类型
    Singleton(const string _value) : value(std::move(_value)) {}
    ~Singleton() {}
    string value;

public:
    Singleton(Singleton& other) = delete;
    void operator=(const Singleton&) = delete;

    static Singleton* GetInstance(const string& value);

    string get_value() const {
        return value;
    }
};

Singleton* Singleton::singleton = nullptr;
mutex Singleton::m;

Singleton* Singleton::GetInstance(const string& value) {
    if (singleton == nullptr) {
        lock_guard<mutex> lock(m);
        if (singleton == nullptr)
            singleton = new Singleton(value);
    }
    return singleton;
}

void thread1() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("Orange ");
    cout << singleton->get_value();
}

void thread2() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("Juice ");
    cout << singleton->get_value();
}

int main()
{
    thread t1(thread1);
    thread t2(thread2);
    t1.join();
    t2.join();
}
