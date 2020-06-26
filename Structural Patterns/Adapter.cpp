class Target {
public:
    virtual ~Target() {}
    virtual string Request() const {
        return "Default.";
    }
};

class Service {
public:
    string OldRequest() const {
        return ".dellac ecivreS";
    }
};


class Adapter : public Target, public Service{
// private:
    // Service* service;
public:
    // Adapter(Service* _s) : service(_s) {}
    Adapter() {}
    string Request() const override {
        // string temp = this->service->OldRequest();
        string temp = OldRequest();
        reverse(temp.begin(), temp.end());
        return temp;
    }
};

void Client(const Target* target) {
    cout << target->Request();
}

int main()
{
    Target* target = new Target;
    Client(target);

    cout << endl;

    Service* service = new Service;
    Adapter* adapter = new Adapter;
    Client(adapter);
}
