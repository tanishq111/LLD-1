#include<iostream>

class Observer {
public:
    virtual void update() = 0; // Pure virtual function to be implemented by concrete observers
}

class Subject{ // subject -> cricket
    virtual void attach(Observer* observer) = 0; // whenever i attach a subject -> observer will be notified;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
}

class NewsAgency : public Subject {
private:
    std::vector<Observer*> observers; // List of observers
    std::string news; // News content

public:
    void attach(Observer* observer) override {
        observers.push_back(observer);
    }
    void detach(Observer* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notify() override {
        for (Observer* observer : observers) {
            observer->update();
        }
    }
    void setNews(const std::string& newsContent) { // new news came here
        news = newsContent;
        notify(); // Notify all observers when news is updated
    }
};


//concrete observer
// NewsChannel
class NewsChannel : public Observer {
public:
    std::string channelName;
    void update() override {
        std::cout << "NewsChannel " << channelName << " received news update." << std::endl;
    }
};


class NewsApp : public Observer {
public:
    std::string appName;
    void update() override {
        std::cout << "NewsApp " << appName << " received news update." << std::endl;
    }
};


class NewsWebsite : public Observer {
public: 
    std::string websiteName;
    void update() override {
        std::cout << "NewsWebsite " << websiteName << " received news update." << std::endl;
    }
};

class youTubeChannel : public Observer {
public: 
    std::string channelName;
    void update() override {
        std::cout << "YouTube Channel " << channelName << " received news update." << std::endl;
    }
};


// observable for iphone stock
class iponeStock : public Subject {
private:
    std::vector<Observer*> observers; // List of observers
    int stockCount; // Current stock count  
public:
    void attach(Observer* observer) override {  
        observers.push_back(observer);
    }    
    void detach(Observer* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notify() override {
        for (Observer* observer : observers) {
            observer->update();
        }
    }   
    void setStockCount(int count) { // Update stock count
        stockCount = count;
        notify(); // Notify all observers when stock count changes
    }                       
};

int main(){
    // observable
    // uber app
    NewsAgency agency = new NewsAgency();
    
    //observers //drivers
    NewsChannel channel1;//////subscribing to notifications
    channel1.channelName = "CNN";
    agency.attach(&channel1);
    
    NewsApp app1;
    app1.appName = "BigShots";
    agency.attach(&app1);
    
    NewsWebsite website1;
    website1.websiteName = "Social News";
    agency.attach(&website1);
    
    youTubeChannel ytChannel1;
    ytChannel1.channelName = "JRE Clips";
    agency.attach(&ytChannel1);
    
    // Set news and notify observers
    agency.setNews("Breaking News: Observer Pattern in Action!");

    agency.detach(&app1); // Detach app1 from notifications
    
    return 0;
}