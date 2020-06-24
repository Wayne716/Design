/*
 * 基类生成器需要声明实现的接口
 * 具体生成器实现基类的接口以及返回对象
 * 主管类负责对生成器的步骤实现
 * 最后由生成器返回结果
 */

class Pizza {
public:
    vector<string> recipe;
    void display() const {
        for (auto& s: recipe)
            cout << s << ' ';
    }
};

class Builder {
public:
    virtual ~Builder() {}

    // 具体产品必须要实现的接口，但不必须调用
    virtual void cheese() const = 0;
    virtual void sausage() const = 0;
};

class PizzaHut : public Builder {
public:
    PizzaHut() {
        this->pizza = make_shared<Pizza>();
    }

    void cheese() const override {
        pizza->recipe.emplace_back("Parmesan Cheese.");
    }
    void sausage() const override {
        pizza->recipe.emplace_back("Pepperoni.");
    }

    // 生成器提供获取结果的方法
    shared_ptr<Pizza> serve() {
        shared_ptr<Pizza> ret = this->pizza;
        this->pizza = make_shared<Pizza>();
        return ret;
    }

private:
    shared_ptr<Pizza> pizza;
};

class PapaJohn : public Builder {
public:
    PapaJohn() {
        this->pizza = make_shared<Pizza>();
    }

    void cheese() const override {
        pizza->recipe.emplace_back("Mozzarella Cheese.");
    }
    void sausage() const override {
        pizza->recipe.emplace_back("Salami.");
    }

    // 生成器提供获取结果的方法
    shared_ptr<Pizza> serve() {
        shared_ptr<Pizza> ret = this->pizza;
        this->pizza = make_shared<Pizza>();
        return ret;
    }

private:
    shared_ptr<Pizza> pizza;
};

// 主管类只执行生成步骤，不知晓生成的产品
class Cook {
public:
    void set_builder(shared_ptr<Builder> builder) {
        this->builder = builder;
    }

    void cheese_pizza() {
        this->builder->cheese();
    }
    void classic_pizza() {
        this->builder->cheese();
        this->builder->sausage();
    }

private:
    shared_ptr<Builder> builder;
};

void order(Cook& c) {

    // 由主管完成生成步骤
    shared_ptr<PizzaHut> ph = make_shared<PizzaHut>();
    c.set_builder(ph);
    c.classic_pizza();
    shared_ptr<Pizza> food1 = ph->serve();
    food1->display();

    cout << endl;

    // 直接调用生成器
    shared_ptr<PapaJohn> pj = make_shared<PapaJohn>();
    pj->cheese();
    shared_ptr<Pizza> food2 = pj->serve();
    food2->display();
}

int main()
{
    shared_ptr<Cook> c = make_shared<Cook>();
    order(*c);

    return 0;
}

/*

Parmesan Cheese. Pepperoni.
Mozzarella Cheese. 

*/
