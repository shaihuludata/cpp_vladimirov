#include <iostream>
#include <cassert>
#include <atomic>

using namespace std;

class Object {
    static std::atomic<int> next_id;
public:
    int id;
    double x, y;

    Object(double a, double b) : x(a), y(b) {
      id = next_id.fetch_add(1, memory_order_relaxed);
    };

    virtual ~Object() = default;

    int get_id() const { return id; };

    virtual void print(ostream& out) const {
        out << id << " at " << x << "," << y;
    }

    friend ostream& operator<< (ostream& out, const Object & o) {
        o.print(out);
        return out;
    }
};

class Stone : public Object {
public:
    double size_x, size_y;
    int material;
    Stone(double a, double b) : Object(a, b), size_x(5), size_y(5), material(0)
    {};

    void print(ostream& out) const override {
        Object::print(out);
    }

    ~Stone() = default;
};

atomic<int> Object::next_id = 0;

int main() {
    Stone o = Stone(100, 100);
    cout << o << endl;
    return 0;
}