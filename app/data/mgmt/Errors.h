#ifndef ERRORS_H
#define ERRORS_H

#include <string>
#include <format>

// Base error class for database operations
class DatabaseError {
public:
    explicit DatabaseError(std::string message) : message_(std::move(message)) {}
    
    [[nodiscard]] 
    const std::string& what() const noexcept { return message_; }
    
private:
    std::string message_;
};

// Specific error types
class QueryError : public DatabaseError {
public:
    explicit QueryError(const std::string& query, const std::string& error)
        : DatabaseError(std::format("Query error: {} ({})", query, error)) {}
};

class NotFoundError : public DatabaseError {
public:
    explicit NotFoundError(const std::string& entity, int id)
        : DatabaseError(std::format("{} with ID {} not found", entity, id)) {}
};

#endif // ERRORS_H
