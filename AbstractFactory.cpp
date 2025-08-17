#include <iostream>
// provides interface that will be help creating families of related or dependent objects without specifying their concrete classes.
//AbstractProducts

//abstract classes
class Button {
public:
    virtual void render() const = 0;
};

class Checkbox {
public:
    virtual void render() const = 0;
};


class WindowsButton : public Button {
public: 
    void render() const override {
        std::cout << "Rendering Windows Button" << std::endl;
    }
};

class WindowsCheckbox : public Checkbox {
public: 
    void render() const override {
        std::cout << "Rendering Windows Checkbox" << std::endl;
    }
};


class MacOSButton : public Button {
public:
    void render() const override {
        std::cout << "Rendering MacOS Button" << std::endl;
    }
};


class MacOSCheckbox : public Checkbox {
public:
    void render() const override {
        std::cout << "Rendering MacOS Checkbox" << std::endl;
    }
};


class linuxButton : public Button {
public: 
    void render() const override {
        std::cout << "Rendering Linux Button" << std::endl;
    }
};      


class linuxCheckbox : public Checkbox {
public:
    void render() const override {
        std::cout << "Rendering Linux Checkbox" << std::endl;
    }
};



//CREATE GUI

class GUIFactory {
public: 
    virtual Button* createButton() const = 0;
    virtual Checkbox* createCheckbox() const = 0;
};

class WindowsFactory : public GUIFactory {
public:
    Button*  createButton() const override {
        return new WindowsButton();
    }
    
    Checkbox* createCheckbox() const override {
        return new WindowsCheckbox();
    }
};


class MacOSFactory : public GUIFactory {
public:
    Button* createButton() const override {
        return new MacOSButton();
    }
    
    Checkbox* createCheckbox() const override {
        return new MacOSCheckbox();
    }
};


class LinuxFactory : public GUIFactory {
public:     
    Button* createButton() const override {
        return new linuxButton();
    }
    
    Checkbox* createCheckbox() const override {
        return new linuxCheckbox();
    }
};