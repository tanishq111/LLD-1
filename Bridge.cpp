#include <iostream>

class DrawingAPI {
public:
    virtual void drawCircle(int x, int y, int radius) = 0;
    virtual void drawSquare(int x, int y, int side) = 0;
};

class OpenGLAPI : public DrawingAPI {
public:
    void drawCircle(int x, int y, int radius) override {
        std::cout << "OpenGL: Drawing Circle at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }

    void drawSquare(int x, int y, int side) override {
        std::cout << "OpenGL: Drawing Square at (" << x << ", " << y << ") with side " << side << std::endl;
    }
};


class DirectXAPI : public DrawingAPI {
public:
    void drawCircle(int x, int y, int radius) override {
        std::cout << "DirectX: Drawing Circle at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }

    void drawSquare(int x, int y, int side) override {
        std::cout << "DirectX: Drawing Square at (" << x << ", " << y << ") with side " << side << std::endl;
    }
};


class Shape {
    public:
    DrawingAPI* drawingAPI;
    virtual void draw() = 0;
};



class Circle : public Shape {
    int x, y, radius;
public:
    Circle(int x, int y, int radius, DrawingAPI* api) : x(x), y(y), radius(radius) {
        drawingAPI = api;
    }

    void draw() override {
        drawingAPI->drawCircle(x, y, radius);
    }
};


int main(){
    DrawingAPI* openGL = new OpenGLAPI();
    DrawingAPI* directX = new DirectXAPI();

    Shape* circle1 = new Circle(10, 20, 30, openGL);
    Shape* circle2 = new Circle(15, 25, 35, directX);

    circle1->draw();
    circle2->draw();
    return 0;
}



///////////// if this was not available

/// drawCircleX
/// drawCircleO













////////////TV remote
class TVCompany{
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void changeChannel(int channel) = 0;
};


class  RemoteControl {
    public:
    TVCompany* tv;
    virtual void pressXButton() = 0;
    virtual void pressYButton() = 0;
    virtual void pressZButton() = 0;
};



class LG: public TVCompany {
public: 
  RemoteControl* remoteControl;
    void turnOn() override {
        remoteControl->pressXButton();
    }
    
    void turnOff() override {
        remoteControl->pressYButton();
    }
    
    void changeChannel(int channel) override {
        remoteControl->pressZButton()   ;
    }
};