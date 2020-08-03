/*
 * 原型类声明克隆的接口
 * 调用对象的克隆接口实现克隆
 */


class Prototype {
protected:
    string name;
    string value;

public:
    Prototype() {}
    Prototype(string _name) : name(_name) {};
    virtual ~Prototype() {}

    virtual unique_ptr<Prototype> Clone() const = 0;

    virtual void Modify(string _value) {
        value = _value;
        cout << name << " is " << value << '.';
    }
};

class Model1 : public Prototype {
private:
    string cval;

public:
    Model1(string _name, string _cval) : Prototype(_name), cval(_cval) {};
    unique_ptr<Prototype> Clone() const override {
        return make_unique<Model1>(*this);
    }
};

class Model2 : public Prototype {
private:
    string cval;

public:
    Model2(string _name, string _cval) : Prototype(_name), cval(_cval) {};
    unique_ptr<Prototype> Clone() const override {
        return make_unique<Model2>(*this);
    }
};

// 原型工厂管理原型的注册表，生成的是原型的克隆。
class PrototypeFactory {
private:
    unordered_map<int, unique_ptr<Prototype>> reg;

public:
    PrototypeFactory() {
        reg[1] = make_unique<Model1>("M1", "basic");
        reg[2] = make_unique<Model2>("M2", "basic");
    }

    unique_ptr<Prototype> Create(int i) {
        return reg[i]->Clone();
    }
};

void Client(PrototypeFactory& f) {
    unique_ptr<Prototype> p = f.Create(1);
    p->Modify("advanced");

    cout << endl;

    p = f.Create(2);
    p->Modify("ultimate");
}

int main()
{
    unique_ptr<PrototypeFactory> f = make_unique<PrototypeFactory>();
    Client(*f);
    return 0;
}

/*

M1 is advanced.
M2 is ultimate.

*/
