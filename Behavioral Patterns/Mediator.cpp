/*
 * 中介者保存对组件的引用，声明对组件的通知方法
 * 每个组件都有一个指向中介者的引用，组件之间不能交互
 */


class Aircraft;

class Tower {
public:
    virtual void Notify(Aircraft* a, string event) const = 0;
};

class Aircraft {
protected:
    Tower* t;
public:
    Aircraft(Tower* _t = nullptr) : t(_t) {};
    void Link(Tower* _t) {
        t = _t;
    }
};

class Jet : public Aircraft {
public:
    void Request() {
        t->Notify(this, "J");
    }
    void Land() {
        cout << "a jet plane is landing" << endl;
    }
};

class Heli : public Aircraft {
public:
    void Request() {
        t->Notify(this, "H");
    }
    void Land() {
        cout << "a helicopter is landing" << endl;
    }
};

class LAX : public Tower {
private:
    Jet* jet;
    Heli* heli;
public:
    LAX(Jet* j, Heli* h) : jet(j), heli(h) {
        jet->Link(this);
        heli->Link(this);
    }
    void Notify(Aircraft* a, string event) const override {
        if (event == "J")
            jet->Land();
        if (event == "H")
            heli->Land();
    }
};

void Control() {
    Jet* j1 = new Jet;
    Heli* h1 = new Heli;
    LAX* lax = new LAX(j1, h1);

    j1->Request();
    h1->Request();

    lax->Notify(j1, "J");
    lax->Notify(h1, "H");

    delete j1;
    delete h1;
    delete lax;
}

int main()
{
    Control();
    return 0;
}
