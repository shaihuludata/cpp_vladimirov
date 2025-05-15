#include <iostream>
#include <cassert>
#include <atomic>
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include <execution>
#include <array>
// #include <ranges>
// #include <iterator>
// #include <algorithm>
#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>

using namespace std;
using namespace spdlog;

//////////////// RANDOM
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(-10, 10);

inline const double size_x = 1024;
inline const double size_y = 768;

std::array<const sf::Color, 5> colors[] = {
    sf::Color::Green,
    sf::Color::Magenta,
    sf::Color::Red,
    sf::Color::Cyan,
    sf::Color::Blue,
};

class Object {
    static atomic<int> next_id;
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

    void log() const {
        stringstream ss;
        ss << id << " at " << x << "," << y;
        info(ss.str());
    }
};

class Moveable: public Object {
    void predraw() {
        shape->setPosition(x, y);
    }
public:
    unique_ptr<sf::Shape> shape;
    Moveable(double a, double b) : Object(a, b) {
        auto circle = make_unique<sf::CircleShape>(20);
        // colors->at(random()%colors->size())
        circle->setFillColor(sf::Color(random()%255, random()%255, random()%255, random()%255));
        circle->setPosition(x, y);
        shape = move(circle);
    };

    virtual ~Moveable() = default;

    void walk() {
        x += dist(gen);
        y += dist(gen);
        if (x < 0) x += size_x;
        if (y < 0) y += size_y;
        if (x > size_x) x -= size_x;
        if (y > size_y) y -= size_y;
        predraw();
    }
};

class Stone : public Moveable {
public:
    double size_x, size_y;
    int material;

    Stone(double a, double b) : Moveable(a, b), size_x(5), size_y(5), material(0)
    {};

    void print(ostream& out) const override {
        Object::print(out);
    }

    ~Stone() = default;
};

std::atomic<int> Object::next_id{0};

// g++ ./main.cpp -lsfml-system -lsfml-window -lsfml-graphics -lspdlog -lfmt -ltbb && ./a.out 3
int main(int argc, char ** argv) {
    cout << argc << " " << argv[1] << endl;
    auto n = 1;
    if (argc >= 2) {
        n = std::stoi(argv[1]);
    };
    info("Welcome! N={}", n);

    vector<unique_ptr<Moveable>> objects;
    objects.reserve(n);

    for (int i = 0; i<n; i++) {
        objects.push_back(make_unique<Stone>(size_x/2, size_y/2));
    }
    // ranges::for_each(views::iota(0, n), [&objects]() {
    //     objects.push_back(make_unique<Stone>(100, 100));
    // });
    sf::RenderWindow window(sf::VideoMode(size_x, size_y), "Box");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear();
        for_each(execution::par, objects.begin(), objects.end(), [](auto & o) {
            o->walk(); o->log();
        });
        // for_each(execution::par, objects.begin(), objects.end(), [window](auto & o) {
            // window.draw(*o->shape);
        // });
        for (auto & o : objects) {
            window.draw(*o->shape);
        }
        window.display();
    }

    return 0;
}