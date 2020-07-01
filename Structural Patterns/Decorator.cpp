/*
 * 部件类派生简单类和装饰类
 * 具体装饰类添加部件的额外行为
 * 以递归的方式添加底层的装饰
 */


class Coffee {
public:
    virtual ~Coffee() = default;
    virtual string display() const = 0;
};

class Espresso : public Coffee {
public:
    string display() const override {
        return "espresso";
    }
};

// 装饰类成员包含被封装的成员变量
class Decorator : public Coffee {
protected:
    shared_ptr<Coffee> coffee;
public:
    Decorator(shared_ptr<Coffee> c) : coffee(c) {}
    string display() const override {
        return coffee->display() + " +";
    }
};

class Cream : public Decorator {
public:
    Cream(shared_ptr<Coffee> c) : Decorator(c) {}
    string display() const override {
        return Decorator::display() + "cream";
    }
};

class Sugar : public Decorator {
public:
    Sugar(shared_ptr<Coffee> c) : Decorator(c) {}
    string display() const override {
        return Decorator::display() + "sugar";
    }
};

void print(shared_ptr<Coffee> c) {
    cout << c->display() << endl;
}

int main()
{
    shared_ptr<Coffee> esp = make_shared<Espresso>();
    print(esp);

    shared_ptr<Cream> c = make_shared<Cream>(esp);
    shared_ptr<Sugar> m = make_shared<Sugar>(c);
    print(m);
}

/*

espresso
espresso +cream +sugar

 */
