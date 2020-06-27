// 基类声明简单类和复合类的接口
class Component {
protected:
    Component* parent;

public:
    virtual ~Component() {}
    void SetParent(Component* _parent) {
        parent = _parent;
    }
    Component* GetParent() const {
        return this->parent;
    }
    virtual void Add(Component* component) {}
    virtual void Remove(Component* component) {}

    virtual bool isComposite() const {
        return false;
    }

    virtual string Operation() const = 0;
};

class Leaf : public Component {
public:
    string Operation() const override {
        return "Leaf";
    }
};

class Composite: public Component {
protected:
    list<Component*> children;

public:
    void Add(Component* component) override {
        this->children.push_back(component);
        component->SetParent(this);
    }

    void Remove(Component* component) override {
        children.remove(component);
        component->SetParent(nullptr);
    }

    bool isComposite() const override {
        return true;
    }

    string Operation() const override {
        string result;
        for (const Component* c : children) {
            if (c == children.back())
                result += c->Operation();
            else
                result += c->Operation() + '+';
        }
        return '[' + result + ']';
    }
};

void Client1(Component* component) {
    cout << component->Operation();
}

void Client2(Component* c1, Component* c2) {
    if (c1->isComposite())
        c1->Add(c2);
    cout << c1->Operation();
}

int main()
{
    Component* simple = new Leaf;
    Client1(simple);

    cout << endl;

    Component* tree = new Composite;
    Component* branch1 = new Composite;
    Component* leaf1 = new Leaf;
    Component* leaf2 = new Leaf;
    branch1->Add(leaf1);
    branch1->Add(leaf2);
    tree->Add(branch1);
    Client1(tree);

    cout << endl;

    Client2(tree, simple);
}
