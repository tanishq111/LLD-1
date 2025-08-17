#include <iostream>
#include <string>
#include <memory>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>

// Error severity levels
enum class ErrorLevel {
    INFO = 0,
    WARNING = 1,
    ERROR = 2,
    CRITICAL = 3
};

// Error data structure
struct ErrorContext {
    ErrorLevel level;
    std::string message;
    std::string component;
    std::chrono::system_clock::time_point timestamp;
    int errorCode;
    
    ErrorContext(ErrorLevel lvl, const std::string& msg, const std::string& comp, int code = 0)
        : level(lvl), message(msg), component(comp), errorCode(code),
          timestamp(std::chrono::system_clock::now()) {}
};

// Abstract error handler base class
class ErrorHandler {
protected:
    std::unique_ptr<ErrorHandler> nextHandler;
    ErrorLevel handlerLevel;
    
    std::string formatTimestamp(const std::chrono::system_clock::time_point& tp) {
        auto time = std::chrono::system_clock::to_time_t(tp);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
    
    std::string levelToString(ErrorLevel level) {
        switch(level) {
            case ErrorLevel::INFO: return "INFO";
            case ErrorLevel::WARNING: return "WARNING";
            case ErrorLevel::ERROR: return "ERROR";
            case ErrorLevel::CRITICAL: return "CRITICAL";
            default: return "UNKNOWN";
        }
    }

public:
    ErrorHandler(ErrorLevel level) : handlerLevel(level) {}
    virtual ~ErrorHandler() = default;
    
    // Chain setup
    ErrorHandler* setNext(std::unique_ptr<ErrorHandler> handler) {
        nextHandler = std::move(handler);
        return nextHandler.get();
    }
    
    // Main handling method
    virtual void handle(const ErrorContext& error) {
        if (canHandle(error)) {
            processError(error);
        }
        
        // Pass to next handler in chain
        if (nextHandler) {
            nextHandler->handle(error);
        }
    }
    
    virtual bool canHandle(const ErrorContext& error) {
        return error.level >= handlerLevel;
    }
    
protected:
    virtual void processError(const ErrorContext& error) = 0;
};

// Console logger - handles all levels
class ConsoleErrorHandler : public ErrorHandler {
public:
    ConsoleErrorHandler() : ErrorHandler(ErrorLevel::INFO) {}
    
protected:
    void processError(const ErrorContext& error) override {
        std::cout << "[CONSOLE] " 
                  << formatTimestamp(error.timestamp) << " "
                  << "[" << levelToString(error.level) << "] "
                  << "[" << error.component << "] "
                  << error.message;
        
        if (error.errorCode != 0) {
            std::cout << " (Code: " << error.errorCode << ")";
        }
        std::cout << std::endl;
    }
};

// File logger - handles warnings and above
class FileErrorHandler : public ErrorHandler {
private:
    std::string filename;
    
public:
    FileErrorHandler(const std::string& file) 
        : ErrorHandler(ErrorLevel::WARNING), filename(file) {}
    
protected:
    void processError(const ErrorContext& error) override {
        std::ofstream logFile(filename, std::ios::app);
        if (logFile.is_open()) {
            logFile << formatTimestamp(error.timestamp) << " "
                   << "[" << levelToString(error.level) << "] "
                   << "[" << error.component << "] "
                   << error.message;
            
            if (error.errorCode != 0) {
                logFile << " (Code: " << error.errorCode << ")";
            }
            logFile << std::endl;
            logFile.close();
        }
    }
};

// Email notification - handles errors and critical only
class EmailNotificationHandler : public ErrorHandler {
private:
    std::string emailAddress;
    
public:
    EmailNotificationHandler(const std::string& email)
        : ErrorHandler(ErrorLevel::ERROR), emailAddress(email) {}
    
protected:
    void processError(const ErrorContext& error) override {
        // Simulate email sending
        std::cout << "[EMAIL] Sending alert to " << emailAddress << std::endl;
        std::cout << "        Subject: " << levelToString(error.level) 
                  << " in " << error.component << std::endl;
        std::cout << "        Message: " << error.message << std::endl;
    }
};

// Database logger - handles critical errors only
class DatabaseErrorHandler : public ErrorHandler {
private:
    std::string connectionString;
    
public:
    DatabaseErrorHandler(const std::string& connStr)
        : ErrorHandler(ErrorLevel::CRITICAL), connectionString(connStr) {}
    
protected:
    void processError(const ErrorContext& error) override {
        // Simulate database logging
        std::cout << "[DATABASE] Logging to " << connectionString << std::endl;
        std::cout << "           Inserting critical error: " << error.message << std::endl;
        std::cout << "           Component: " << error.component 
                  << ", Code: " << error.errorCode << std::endl;
    }
};

// Retry handler - handles specific error codes
class RetryHandler : public ErrorHandler {
private:
    int maxRetries;
    int retryableErrorCode;
    
public:
    RetryHandler(int maxRetry = 3, int errorCode = 503)
        : ErrorHandler(ErrorLevel::ERROR), maxRetries(maxRetry), retryableErrorCode(errorCode) {}
    
    bool canHandle(const ErrorContext& error) override {
        return error.level >= handlerLevel && error.errorCode == retryableErrorCode;
    }
    
protected:
    void processError(const ErrorContext& error) override {
        std::cout << "[RETRY] Error code " << error.errorCode 
                  << " is retryable. Max retries: " << maxRetries << std::endl;
        std::cout << "        Scheduling retry for: " << error.message << std::endl;
    }
};

// Error middleware manager
class ErrorMiddleware {
private:
    std::unique_ptr<ErrorHandler> handlerChain;
    
public:
    void setupChain() {
        // Create handler chain: Console -> File -> Email -> Retry -> Database
        auto console = std::make_unique<ConsoleErrorHandler>();
        auto file = std::make_unique<FileErrorHandler>("application.log");
        auto email = std::make_unique<EmailNotificationHandler>("admin@company.com");
        auto retry = std::make_unique<RetryHandler>(3, 503);
        auto database = std::make_unique<DatabaseErrorHandler>("mongodb://localhost:27017/logs");
        
        // Chain them together
        console->setNext(std::move(file))
               ->setNext(std::move(email))
               ->setNext(std::move(retry))
               ->setNext(std::move(database));
        
        handlerChain = std::move(console);
    }
    
    void handleError(const ErrorContext& error) {
        if (handlerChain) {
            handlerChain->handle(error);
        }
    }
    
    // Convenience methods for different error types
    void logInfo(const std::string& component, const std::string& message) {
        handleError(ErrorContext(ErrorLevel::INFO, message, component));
    }
    
    void logWarning(const std::string& component, const std::string& message, int code = 0) {
        handleError(ErrorContext(ErrorLevel::WARNING, message, component, code));
    }
    
    void logError(const std::string& component, const std::string& message, int code = 0) {
        handleError(ErrorContext(ErrorLevel::ERROR, message, component, code));
    }
    
    void logCritical(const std::string& component, const std::string& message, int code = 0) {
        handleError(ErrorContext(ErrorLevel::CRITICAL, message, component, code));
    }
};

// Example application components
class DatabaseService {
private:
    ErrorMiddleware& errorHandler;
    
public:
    DatabaseService(ErrorMiddleware& handler) : errorHandler(handler) {}
    
    void connect() {
        errorHandler.logInfo("DatabaseService", "Attempting to connect to database");
        // Simulate connection failure
        errorHandler.logError("DatabaseService", "Connection timeout", 503);
    }
    
    void performCriticalOperation() {
        errorHandler.logCritical("DatabaseService", "Data corruption detected!", 500);
    }
};

class WebService {
private:
    ErrorMiddleware& errorHandler;
    
public:
    WebService(ErrorMiddleware& handler) : errorHandler(handler) {}
    
    void handleRequest() {
        errorHandler.logInfo("WebService", "Processing HTTP request");
        errorHandler.logWarning("WebService", "High memory usage detected", 101);
        errorHandler.logError("WebService", "Service temporarily unavailable", 503);
    }
};

// Demo application
int main() {
    std::cout << "=== Error Handling Middleware Demo ===" << std::endl << std::endl;
    
    // Setup error handling middleware
    ErrorMiddleware errorMiddleware;
    errorMiddleware.setupChain();
    
    // Create application services
    DatabaseService dbService(errorMiddleware);
    WebService webService(errorMiddleware);
    
    std::cout << "--- Database Service Operations ---" << std::endl;
    dbService.connect();
    std::cout << std::endl;
    
    std::cout << "--- Web Service Operations ---" << std::endl;
    webService.handleRequest();
    std::cout << std::endl;
    
    std::cout << "--- Critical Database Error ---" << std::endl;
    dbService.performCriticalOperation();
    std::cout << std::endl;
    
    std::cout << "--- Manual Error Logging ---" << std::endl;
    errorMiddleware.logInfo("Application", "Application started successfully");
    errorMiddleware.logWarning("Security", "Multiple failed login attempts", 401);
    errorMiddleware.logError("PaymentService", "Payment gateway timeout", 503);
    errorMiddleware.logCritical("System", "Disk space critically low", 507);
    
    return 0;
}