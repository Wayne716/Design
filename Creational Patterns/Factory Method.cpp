/*
 *  产品基类声明具体产品要实现的统一接口
 *  工厂基类声明子工厂要实现的统一接口
 *  子工厂返回具体产品的对象
 *  这样通过指向具体产品对象的基类对象指针就可以工作
 */

class Apple {
public:
    virtual ~Apple() {}
    // 所有具体的产品必须遵循的同一接口
    virtual string Commercial() const = 0;
};

class iPad : public Apple {
public:
    // 具体的产品对接口提供不同的实现方法
    string Commercial() const override {
        return "Your next computer is not a computer.";
    }
};
class iPhone : public Apple {
public:
    string Commercial() const override {
        return "Just the right amount of everything.";
    }
};

class Ads {
public:
    virtual ~Ads() {}
    // 创建类的一个对象，包含一些核心的逻辑，但是子类可以直接覆盖。
    // 返回类型为通用的产品接口
    virtual Apple* FactoryMethod() const = 0;
    string create() const {
        Apple* product = this->FactoryMethod();
        string commercial = product->Commercial();
        delete product;
        return commercial;
    }
};

class iPad_Ad : public Ads {
public:
    Apple* FactoryMethod() const override {
        return new iPad;
    }
};

class iPhone_Ad : public Ads {
public:
    Apple* FactoryMethod() const override {
        return new iPhone;
    }
};

// 子类通过基类接口传递
void display(const Ads& ad) {
    cout << ad.create() << endl;
}

int main()
{
    Ads* ad1 = new iPad_Ad;
    display(*ad1);

    Ads* ad2 = new iPhone_Ad;
    display(*ad2);

    delete ad1;
    delete ad2;
}
