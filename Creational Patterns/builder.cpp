class House {
public:
    vector<string> furnitures;

    void display() const {
        int size = furnitures.size();
        for (int i=0; i<size; ++i)
            cout << furnitures[i] << ' ';
    }
};

class Builder {
public:
    virtual void Bed() const = 0;
    virtual void Table() const = 0;
};

class IKEA : public Builder {
public:
    IKEA() { this->reset(); }

    void Bed() const override {
        this->house->furnitures.emplace_back("Queen Bed");
    }

    void Table() const override {
        this->house->furnitures.emplace_back("Work Desk");
    }

    shared_ptr<House> get() {
        shared_ptr<House> item = this->house;
        this->reset();
        return item;
    }

    void reset() {
        this->house = make_shared<House>();
    }

private:
    shared_ptr<House> house;
};

class Director {
public:
    void set_builder(shared_ptr<Builder> _builder) {
        this->builder = std::move(_builder);
    }

    void build_lite() {
        this->builder->Bed();
    }

    void build_full() {
        this->builder->Bed();
        this->builder->Table();
    };


private:
    shared_ptr<Builder> builder;
};

void order(Director& director) {
    shared_ptr<IKEA> builder = make_shared<IKEA>();
    director.set_builder(builder);

    director.build_lite();
    shared_ptr<House> lite_house = builder->get();
    lite_house->display();

    cout << endl;

    director.build_full();
    shared_ptr<House> full_house = builder->get();
    full_house->display();
}

int main()
{
    shared_ptr<Director> director = make_shared<Director>();
    order(*director);

    return 0;
}
