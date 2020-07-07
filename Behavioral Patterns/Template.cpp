/*
 * 基类声明模版方法
 * 在模版中调用抽象方法
 * 子类必须实现抽象方法
 */


class Abstract {
public:
    void Template() const {
        this->Base();
        this->Required();
        this->Optional();
    }
protected:
    void Base() const {
        cout << "Base" << endl;
    }
    virtual void Required() const = 0;
    virtual void Optional() const {}
};

class Concrete : public Abstract {
public:
    void Required() const override {
        cout << "Required" << endl;
    }
    void Optional() const override {
        cout << "Optional" << endl;
    }
};

void Client(Abstract* a) {
    a->Template();
}

int main()
{
    Concrete* c = new Concrete();
    Client(c);
    delete c;
    return 0;
}

/*

Base
Required
Optional

 */
