#include<iostream>

class CharacterFlyweight {
public:
    virtual void display() const = 0; 
    virtual char getSymbol() const = 0; 
};


class ConcreteCharacter : public CharacterFlyweight {
    char symbol; // intrinsic state same for all instances for a given character
public:
    ConcreteCharacter(char sym) : symbol(sym) {}

    void display() const override {
        std::cout << "Character: " << symbol << std::endl;
    }

    char getSymbol() const override {
        return symbol;
    }
};


class CharacterFactory {
    std::map<char, CharacterFlyweight*> characters; // map to hold created characters
public:

    CharacterFlyweight* getCharacter(char symbol) {
        if (characters.find(symbol) == characters.end()) {
            characters[symbol] = new ConcreteCharacter(symbol);
        }
        return characters[symbol];
    }
};



int main() {
    CharacterFactory factory;

    // Create characters
    CharacterFlyweight* a = factory.getCharacter('A');
    CharacterFlyweight* b = factory.getCharacter('B');
    CharacterFlyweight* c = factory.getCharacter('C');

    // Display characters
    a->display();
    b->display();
    c->display();

    // Reuse existing character
    CharacterFlyweight* anotherA = factory.getCharacter('A');
    anotherA->display(); // Should display the same character as 'a'

    return 0;
}


// you get the character then you can implment styles on top of it, instead of storing all the objects with every styple possible.
