/*
 * 部件类派生简单类和装饰类
 * 具体装饰类添加部件的额外行为
 */


class Component {
public:
    virtual ~Component() = default;
    virtual string display() const = 0;
};

class Basic : public Component {
public:
    string display() const override {
        return "Basic";
    }
};

class Decorator : public Component {
protected:
    Component* component;

public:
    Decorator(Component* c) : component(c) {}
    string display() const override {
        return component->display();
    }
};

// 装饰类成员包含被封装的成员变量
class Dec1 : public Decorator {
public:
    Dec1(Component* c) : Decorator(c) {}
    string display() const override {
        return "A(" + component->display() + ")";
    }
};

class Dec2 : public Decorator {
public:
    Dec2(Component* c): Decorator(c) {}
    string display() const override {
        return "B(" + Decorator::display() + ")";
    }
};

void print(Component* c) {
    cout << c->display();
}

int main()
{
    Component* simple = new Basic;
    print(simple);

    cout << endl;

    Component* dec1 = new Dec1(simple);
    Component* dec2 = new Dec2(dec1);
    print(dec2);

    delete simple;
    delete dec1;
    delete dec2;
}

/*

Basic
B(A(Basic))

*/
