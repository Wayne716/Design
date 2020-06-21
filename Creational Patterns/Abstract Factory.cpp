/*
 * 每种产品由相应工厂实现，返回抽象产品。
 * 客户调用抽象工厂接口，生产的产品互相对应。
 */

class Table {
public:
    virtual ~Table() {}
    virtual string function() const = 0;
};

class Cafe_Table : public Table {
public:
    string function() const override {
        return "Cafe Table";
    }
};
class Bar_Table : public Table {
    string function() const override {
        return "Bar Table";
    }
};

class Chair {
public:
    virtual ~Chair() {}
    virtual string function() const = 0;
    virtual string match(const Table& table) const = 0;
};

class Cafe_Chair : public Chair {
public:
    string function() const override {
        return "Cafe Chair";
    }
    string match(const Table& table) const override {
        return "& Cafe Chair.";
    }
};
class Bar_Stool : public Chair {
public:
    string function() const override {
        return "Bar Stool";
    }
    string match(const Table& table) const override {
        return "& Bar Stool.";
    }
};

class Factory {
public:
    virtual Table* CreateTable() const = 0;
    virtual Chair* CreateChair() const = 0;
};

// 为每种产品实现一个工厂类
class Cafe_Factory : public Factory {
public:
    Table* CreateTable() const override {
        return new Cafe_Table;
    }
    Chair* CreateChair() const override {
        return new Cafe_Chair;
    }
};
// 为每种产品实现一个工厂类
class Bar_Factory : public Factory {
public:
    Table* CreateTable() const override {
        return new Bar_Table;
    }
    Chair* CreateChair() const override {
        return new Bar_Stool;
    }
};

void order(const Factory& f) {
    const Table* table = f.CreateTable();
    const Chair* chair = f.CreateChair();

    cout << table->function() << endl;
    cout << chair->match(*table) << endl;

    delete table;
    delete chair;
}

int main()
{
    // 必须初始化工厂类别
    Cafe_Factory* cafe = new Cafe_Factory();
    order(*cafe);
    delete cafe;

    // 必须初始化工厂类别
    Bar_Factory* bar = new Bar_Factory();
    order(*bar);
    delete bar;

    return 0;
}

/*

Cafe Table
& Cafe Chair.
Bar Table
& Bar Stool.

*/
