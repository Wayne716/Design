/*
 *  产品基类声明具体产品要实现的统一接口
 *  工厂基类声明子工厂要实现的统一接口
 *  子工厂返回具体产品的对象
 *  这样通过指向具体产品对象的基类对象指针就可以工作
 */

class Car {
public:
    virtual ~Car() {}
    // 所有具体的产品必须遵循的同一接口
    virtual string model() const = 0;
};

class Mustang : public Car {
public:
    // 具体的产品对接口提供不同的实现方法
    string model() const override {
        return "Ford Mustang.";
    }
};
class Cayenne: public Car {
public:
    // 具体的产品对接口提供不同的实现方法
    string model() const override {
        return "Porsche Cayenne.";
    }
};

class Factory {
public:
    ~Factory() {}
    // 工厂方法创建类的一个对象，返回类型为通用的产品接口。
    // 包含一些核心的逻辑，但是子类可以直接覆盖。
    virtual Car* Produce() const = 0;
    string create() const {
        Car* car = this->Produce();
        string model = car->model();
        delete car;
        return model;
    }
};

class Ford : public Factory {
public:
    Car* Produce() const override {
        return new Mustang;
    }
};
class Porsche : public Factory {
public:
    Car* Produce() const override {
        return new Cayenne;
    }
};

// 子类通过基类接口传递，工厂用工厂方法生产产品，
// 无需了解不同子类生产的实际对象的区别。
void display(Factory* f) {
    cout << f->create() << endl;
}

int main()
{
    Factory* ford = new Ford;
    display(ford);

    Factory* porsche = new Porsche;
    display(porsche);

    delete ford;
    delete porsche;

    return 0;
}
