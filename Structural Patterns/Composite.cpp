/*
 * 组合类声明简单类和复合类的接口
 * 简单类实现主要的工作
 */

class Tree {
protected:
    shared_ptr<Tree> parent;

public:
    virtual ~Tree() = default;
    void SetParent(shared_ptr<Tree> p) {
        this->parent = std::move(p);
    }
    shared_ptr<Tree> GetParent() const {
        return parent;
    }
    virtual void Add(shared_ptr<Tree> t) {}
    virtual void Remove(shared_ptr<Tree> t) {}
    virtual bool isComposite() const {
        return false;
    }
    virtual string display() const = 0;
};

class Leaf : public Tree {
public:
    string display() const override {
        return "Leaf";
    }
};

// 复合类将任务委托给简单类
class Branch : public Tree, public enable_shared_from_this<Tree> {
protected:
    list<shared_ptr<Tree>> children;

public:
    void Add(shared_ptr<Tree> t) override {
        children.push_back(t);
        t->SetParent(shared_from_this());
    }
    void Remove(shared_ptr<Tree> t) override {
        children.remove(t);
        t->SetParent(nullptr);
    }
    bool isComposite() const override {
        return true;
    }
    string display() const override {
        string res;
        for (const auto& t : children) {
            if (t == children.back())
                res += t->display();
            else res += t->display() + '+';
        }
        return '[' + res + ']';
    }
};

void print(const shared_ptr<Tree>& t) {
    cout << t->display();
}


int main()
{
    shared_ptr<Tree> leaf = make_shared<Leaf>();
    print(leaf);

    cout << endl;

    shared_ptr<Tree> branch1 = make_shared<Branch>();
    shared_ptr<Tree> branch2 = make_shared<Branch>();
    shared_ptr<Tree> leaf1 = make_shared<Leaf>();
    shared_ptr<Tree> leaf2 = make_shared<Leaf>();
    shared_ptr<Tree> leaf3 = make_shared<Leaf>();
    branch1->Add(leaf1);
    branch1->Add(branch2);
    branch2->Add(leaf2);
    branch2->Add(leaf3);
    print(branch1);

    cout << endl;

    branch1->Remove(leaf1);
    branch2->Remove(leaf2);
    print(branch1);
}

/*

Leaf
[Leaf+[Leaf+Leaf]]
[[Leaf]]

*/
