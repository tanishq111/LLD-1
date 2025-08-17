#include <iostream>
#include <map>
#include <memory>

// --------- Prototype interface ---------
class Shape {
    public:
        virtual Shape* clone() const = 0;
        virtual void draw() const = 0;
};


// --------- Concrete Prototypes ---------
class Circle : public Shape {
    public:
    int radius;
        Circle(int r) : radius(r) {}
        Circle* clone() const override {
            return new Circle(*this);
        }
        
        void draw() const override {
            std::cout << "Drawing a Circle" << std::endl;
        }
};

class Square : public Shape {
    
    public:
    int side;
        Square(int s) : side(s) {}
        Square* clone() const override {
            return new Square(*this); // creates deep copy of the Square object
        }
        
        void draw() const override {
            std::cout << "Drawing a Square" << std::endl;
        }
};



// --------- Prototype Registry ---------
class PrototypeRegistry {
    std::map<std::string, Shape*> prototypes;
    public:
        void registerPrototypes(std::string name) {
            prototypes["Circle"] = new Circle(5);
            prototypes["Square"] = new Square(10); /// storing circle and square objects in the registry
        }

        Shape* createShape(const std::string& type) {
            auto it = prototypes.find(type);
            if (it != prototypes.end()) {
                return it->second->clone();// new Shape() -> you just clone the prototype
            }
            return nullptr;
        }
};


int main() {
    PrototypeRegistry registry;
    registry.registerPrototypes("Circle");
    registry.registerPrototypes("Square");

    Shape* circle = registry.createShape("Circle");
    if (circle) {
        static_cast<Circle*>(circle)->radius = 10; // Modify the radius if needed
        circle->draw();
        delete circle; // Clean up
    }

    Shape* square = registry.createShape("Square");
    if (square) {
        square->draw();
        delete square; // Clean up
    }

    return 0;
}