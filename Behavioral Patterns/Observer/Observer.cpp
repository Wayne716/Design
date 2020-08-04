/*
 * 发布者维护订阅列表，通过订阅者的接口交互。
 */

class Subscriber {
public:
    virtual ~Subscriber() {}
    virtual void Update(string& str) = 0;
};

class News {
public:
    virtual ~News() = default;
    virtual void Add(Subscriber* s) = 0;
    virtual void Remove(Subscriber* s) = 0;
    virtual void Push(string str) = 0;
};

class NYT : public News {
public:
    NYT() = default;
    void Push(string str) override {
        for (auto& s : subs)
            s->Update(str);
    }
    void Add(Subscriber* s) override {
        subs.push_back(s);
    }
    void Remove(Subscriber* s) override{
        subs.remove(s);
    }
private:
    list<Subscriber*> subs;
};

class Reader : public Subscriber {
public:
    Reader(News& news) : following(news) {
        following.Add(this);
        ID = ++ReaderID;
        cout << "Reader " + to_string(ID) +  " just subscribed." << endl;
    }
    void Unsubscribe() {
        following.Remove(this);
        cout << "Reader " + to_string(ID) + " unsubscribed." << endl;
    }
    void Update(string& h) override {
        cout << "Update " << ID << ": [" << h << ']' << endl;
    }
private:
    News& following;
    static int ReaderID;
    int ID;
};

int Reader::ReaderID = 0;

void Client() {
    NYT *world = new NYT;
    Reader* r1 = new Reader(*world);
    Reader* r2 = new Reader(*world);
    world->Push("Boris Johnson’s ‘Global Britain’: Inspired Vision or Wishful Thinking?");

    r2->Unsubscribe();
    world->Push("Coronavirus Live Updates: U.S. Cases Are Rising, Even as Death Rates Trend Down");

    delete r1;
    delete r2;
    delete world;
}

int main()
{
    Client();
    return 0;
}


/*

Reader 1 just subscribed.
Reader 2 just subscribed.
Update 1: [Boris Johnson’s ‘Global Britain’: Inspired Vision or Wishful Thinking?]
Update 2: [Boris Johnson’s ‘Global Britain’: Inspired Vision or Wishful Thinking?]
Reader 2 unsubscribed.
Update 1: [Coronavirus Live Updates: U.S. Cases Are Rising, Even as Death Rates Trend Down]
 
*/
