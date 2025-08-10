#include <iostream>


class Document {
public:
    virtual ~Document() = default;
    virtual void open() = 0;
    virtual void save() = 0;
    virtual void close() = 0;
    virtual std::string getType() const = 0;
};

// Concrete Products
class WordDocument : public Document {
public:
    void open() override {
        std::cout << "Opening Word document (.docx)" << std::endl;
    }
    
    void save() override {
        std::cout << "Saving Word document with formatting" << std::endl;
    }
    
    void close() override {
        std::cout << "Closing Word document" << std::endl;
    }
    
    std::string getType() const override {
        return "Word Document";
    }
};

class DocumentFactory {
public:
    enum class DocumentType {
        WORD,
        PDF,
        EXCEL
    };
    
    static Document createDocument(DocumentType type) {
        switch (type) {
            case DocumentType::WORD:
                return std::make_unique<WordDocument>();
            case DocumentType::PDF:
                return std::make_unique<PDFDocument>();
            case DocumentType::EXCEL:
                return std::make_unique<ExcelDocument>();
            default:
                throw std::invalid_argument("Unknown document type");
        }
    }
};
