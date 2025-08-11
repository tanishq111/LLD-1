#include <iostream>
#include <vector>

class Light { //receivers 
public:
    void turnOn() const {
        std::cout << "Light is turned ON." << std::endl;
    }
    
    void turnOff() const {
        std::cout << "Light is turned OFF." << std::endl;
    }
};

class stereoSystem {
public:
    void playMusic() const {
        std::cout << "Stereo system is playing music." << std::endl;
    }
    
    void stopMusic() const {
        std::cout << "Stereo system has stopped music." << std::endl;
    }
};


/// command interface
class command {
public:
    virtual void undo() const = 0; 
    virtual void execute() const = 0; 
};


//concrete command for turning on the light
class LightOnCommand : public command {
    const Light& light; // reference to the light object
public:
    LightOnCommand(const Light& l) : light(l) {}

    void execute() const override {
        light.turnOn();
    }

    void undo() const override {
        light.turnOff();
    }
};

class LightOffCommand : public command {
    const Light& light; // reference to the light object
public:
    LightOffCommand(const Light& l) : light(l) {}

    void execute() const override {
        light.turnOff();
    }

    void undo() const override {
        light.turnOn();
    }
};



class stereoOnCommand : public command {
    const stereoSystem& stereo; // reference to the stereo system object
public:
    stereoOnCommand(const stereoSystem& s) : stereo(s) {}

    void execute() const override {
        stereo.playMusic();
    }

    void undo() const override {
        stereo.stopMusic();
    }
};

class stereoOffCommand : public command {
    const stereoSystem& stereo; // reference to the stereo system object
public:
    stereoOffCommand(const stereoSystem& s) : stereo(s) {}

    void execute() const override {
        stereo.stopMusic();
    }

    void undo() const override {
        stereo.playMusic();
    }
};



// invoker class
class RemoteControl {
     public:
     std::vector<command*> oNommands; // vector to hold commands
     std::vector<command*> oFFcommands; // vector to hold commands


     void setCommand(int slot, command* onCommand, command* offCommand) {
        if (slot < oNommands.size() && slot < oFFcommands.size()) {
            oNommands[slot] = onCommand;
            oFFcommands[slot] = offCommand;
        } else {
            oNommands.push_back(onCommand);
            oFFcommands.push_back(offCommand);
        }
    }
};


void executeCommand(const RemoteControl& remote, int slot) {
    if (slot < remote.oNommands.size()) {
        remote.oNommands[slot]->execute();
    } else {
        std::cout << "No command set for this slot." << std::endl;
    }
}


void onButtonPressed(const RemoteControl& remote, int slot) {
    if (slot < remote.oNommands.size()) {
        remote.oNommands[slot]->execute();
    } else {
        std::cout << "No command set for this slot." << std::endl;
    }
}

void offButtonPressed(const RemoteControl& remote, int slot) {
    if (slot < remote.oFFcommands.size()) {
        remote.oFFcommands[slot]->execute();
    } else {
        std::cout << "No command set for this slot." << std::endl;
    }
}


void undoButtonPressed(const RemoteControl& remote, int slot) {
    if (slot < remote.oNommands.size()) {
        remote.oNommands[slot]->undo();
    } else {
        std::cout << "No command set for this slot." << std::endl;
    }
}


int main(){
    Light livingRoomLight;
    stereoSystem livingRoomStereo;

    LightOnCommand lightOnCommand(livingRoomLight);
    LightOffCommand lightOffCommand(livingRoomLight);
    stereoOnCommand stereoOnCommand(livingRoomStereo);
    stereoOffCommand stereoOffCommand(livingRoomStereo);

    RemoteControl remote;
    remote.setCommand(0, &lightOnCommand, &lightOffCommand);
    remote.setCommand(1, &stereoOnCommand, &stereoOffCommand);

    onButtonPressed(remote, 0); // Turn on the light
    offButtonPressed(remote, 0); // Turn off the light
    undoButtonPressed(remote, 0); // Undo last action (turn on the light)

    onButtonPressed(remote, 1); // Turn on the stereo
    offButtonPressed(remote, 1); // Turn off the stereo
    undoButtonPressed(remote, 1); // Undo last action (turn on the stereo)

    return 0;
}