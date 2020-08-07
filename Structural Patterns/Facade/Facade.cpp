/*
 * 外观模式提供简化的接口
 * 实现子系统的部分功能
 */


class System1 {
public:
    string init() const {
        return "System1 is initialized.\n";
    }
    string close() const {
        return "System1 is closed.\n";
    }
};

class System2 {
public:
    string init() const {
        return "System2 is initialized.\n";
    }
    string close() const {
        return "System2 is closed.\n";
    }
};

class Facade {
protected:
    System1* sys1;
    System2* sys2;
public:
    Facade(System1* s1 = nullptr, System2* s2 = nullptr) {
        this->sys1 = s1? : new System1;
        this->sys2 = s2? : new System2;
    }
    ~Facade() {
        delete sys1;
        delete sys2;
    }
    string boot() {
        return this->sys1->init() + this->sys2->init();
    }
    string shut() {
        return this->sys1->close() + this->sys2->close();
    }
};

void Client(Facade* f) {
    cout << f->boot();
    cout << f->shut();
}

int main()
{
    System1* s1 = new System1;
    System2* s2 = new System2;
    Facade* f = new Facade(s1, s2);
    Client(f);

    delete f;
    return 0;
}


/*

System1 is initialized.
System2 is initialized.
System1 is closed.
System2 is closed.

 */
