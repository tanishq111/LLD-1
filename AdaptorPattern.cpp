#include <iostream>

// Target interface
class MediaPlayer { 
    virtual void play(const std::string& audioType, const std::string& fileName) = 0;
};


//adaptee
class Mp3Player {
public:     
    void playMp3(const std::string& fileName) {
        std::cout << "Playing MP3 file: " << fileName << std::endl;
    }
};



class Mp4Player {
public:
    void playMp4(const std::string& fileName) {
        std::cout << "Playing MP4 file: " << fileName << std::endl;
    }
};


class VlcPlayer {
public: 
    void playVlc(const std::string& fileName) {
        std::cout << "Playing VLC file: " << fileName << std::endl;
    }
};




// Adapter class
class MediaAdapter : public MediaPlayer {
    public:
    Mp3Player mp3Player;
    Mp4Player mp4Player;
    VlcPlayer vlcPlayer;
    void play(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "mp3") {
            mp3Player.playMp3(fileName);
        } else if (audioType == "mp4") {
            mp4Player.playMp4(fileName);
        } else if (audioType == "vlc") {
            vlcPlayer.playVlc(fileName);
        } else {
            std::cout << "Unsupported audio type: " << audioType << std::endl;
        }
    }
};


//mp5 -> if i want to add this
// i will make MediaAdapter as an adaptee 

class newMediaAdapter : public MediaPlayer {
    public:
    MediaAdapter* mediaAdapter; 
    void play(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "mp5") {
            std::cout << "Playing MP5 file: " << fileName << std::endl;
        } else{
            mediaAdapter = new MediaAdapter();
            mediaAdapter->play(audioType, fileName); // delegate to the existing adapter
        }
    }
};





//// legacyPrinter ->printOldFormat
//// mordernPrinter -> printNewFormat
//// printerAdapter implementer modernPrinter, but also have a legacyPrinter as a composition



class LegacyPrinter {  
public:
    void printOldFormat(const std::string& text) {
        std::cout << "Legacy Printer: " << text << std::endl;
    }
};

class ModernPrinter {   // created this interface to adapt the legacy printer
public:
  virtual void print(const std::string& text) = 0;
  virtual void printNewFormat(const std::string& text) = 0;
};


//adapter
class PrinterAdapter : public ModernPrinter { 
    LegacyPrinter legacyPrinter; // composition
public:
    void print(const std::string& text) override {
        legacyPrinter.printOldFormat(text);
    }
    void printNewFormat(const std::string& text) override {
        std::cout << "Modern Printer (via Adapter): " << text << std::endl;
    }
};