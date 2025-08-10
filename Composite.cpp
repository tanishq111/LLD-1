#include<iostream>
#include <vector>

class FileSystemComponent {
public: 
    virtual void displayInfo() const = 0; // Pure virtual function
};


class File : public FileSystemComponent {
public: 
    File(const std::string& name) : name(name) {}

    void displayInfo() const override {
        std::cout << "File: " << name << std::endl;
    }
private:
    std::string name;
};


class Folder : public FileSystemComponent {
public:
    Folder(const std::string& name) : name(name) {}
    void add(FileSystemComponent* component) {
        children.push_back(component);
    }
    void displayInfo() const override {
        std::cout << "Folder: " << name << std::endl;
        for (const auto& child : children) {
            child->displayInfo();
        }
    }

private:
    std::string name;
    std::vector<FileSystemComponent*> children; // children can be Files or Folders
};


int main(){
    File file1("file1.txt");
    File file2("file2.txt");
    Folder folder1("folder1");
    folder1.add(&file1);
    folder1.add(&file2);

    folder1.displayInfo();
    file1.displayInfo();
    file2.displayInfo();

    return 0;
}