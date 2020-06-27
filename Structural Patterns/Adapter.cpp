/*
 * 适配器类继承服务类
 * 封装对象后由客户端调用
 *
 * 可以在成员中包含对象的指针
 * 或是多重继承服务类和客户端类
 */


class RoundPeg {
private:
    double radius;
public:
    RoundPeg() {}
    RoundPeg(double _r) : radius(_r) {}

    // 服务类的接口要设置为虚函数
    virtual double Radius() const {
        return radius;
    }
    virtual ~RoundPeg() = default;
};

class SquarePeg {
private:
    double edge;
public:
    SquarePeg(double _e) : edge(_e) {}
    double Edge() const {
        return edge;
    }
};

class Adapter : public RoundPeg {
private:
    SquarePeg* sp;
public:
    Adapter(SquarePeg* _sp) : sp(_sp) {}

    double Radius() const override {
        int r2 = 2 * pow(sp->Edge()/2, 2);
        return sqrt(r2);
    }
};

class RoundHole {
private:
    double radius;
public:
    RoundHole(double _r) : radius(_r) {}

    bool fits(RoundPeg* peg) const {
        return radius >= peg->Radius();
    }
};

int main()
{
    SquarePeg* peg = new SquarePeg(10);
    Adapter* a = new Adapter(peg);
    RoundHole* hole = new RoundHole(8);
    if (hole->fits(a)) cout << "YES";
    else cout << "NO";

    delete peg;
    delete a;
    delete hole;
    return 0;
}
