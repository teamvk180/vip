#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
#include <iostream>
#include <errno.h>
#include <string>
using namespace std;
//this is throwed by parser
class ParseException : public std::exception
{
public:
    ParseException(const char *msg) : err_msg(msg){};

    ~ParseException() { cerr << "Unable To Throw ParseException "; };

    const char *what() const throw() { return this->err_msg.c_str(); };

private:
    std::string err_msg;
};
//this is throwed by ast
class SemanticError : public std::exception
{
public:
    SemanticError(std::string message) : err_msg_a(message){};
    ~SemanticError() { cerr << "unable to throw Semantic Exception"; };
    const char *what() const throw() { return this->err_msg_a.c_str(); };

private:
    std::string err_msg_a;
};
//this is throwed by ast
class LogicError : public std::exception
{
public:
    LogicError(std::string message) : err_msg_b(message){};
    ~LogicError() { cerr << "unable to throw Logic Exception"; };
    const char *what() const throw() { return this->err_msg_b.c_str(); };

private:
    std::string err_msg_b;
};
//this is throwed by lexer
class ReadingError : public std::exception
{
public:
    ReadingError(const char *message) : err_msg_c(message){};
    ~ReadingError() { cerr << "unable to throw Reading Exception"; };
    const char *what() const throw() { return this->err_msg_c.c_str(); };

private:
    std::string err_msg_c;
};
class InvalidDataTypeException : public std::exception
{
public:
    InvalidDataTypeException(std::string message) : err_msg_d(message){};
    ~InvalidDataTypeException() { cerr << "unable to throw datatype invalid Exception"; };
    const char *what() const throw() { return this->err_msg_d.c_str(); };

private:
    std::string err_msg_d;
};

class UnknownException : public std::exception
{
public:
    UnknownException(std::string message) : err_msg_d(message){};
    ~UnknownException() { cerr << "unable to throw Unknown Exception"; };
    const char *what() const throw() { return this->err_msg_d.c_str(); };

private:
    std::string err_msg_d;
};
class InternalException : public std::exception
{
public:
    InternalException(const char *message) : err_msg_e(message){};
    ~InternalException() { cerr << "unable to throw Internal Exception"; };
    const char *what() const throw() { return this->err_msg_e.c_str(); };

private:
    std::string err_msg_e;
};
class BuiltINMethodInvalidCallException : public std::exception
{
private:
    std::string err_msg;

public:
    BuiltINMethodInvalidCallException(std::string message) : err_msg(message) {}
    ~BuiltINMethodInvalidCallException() { throw "unable to throw invalid builtin method call Exception"; };
    const char *what() const throw() { return this->err_msg.c_str(); };
};

class InvalidArgumentCallException : public std::exception
{
private:
    std::string err_msg;

public:
    InvalidArgumentCallException(std::string message) : err_msg(message) {}
    ~InvalidArgumentCallException() { throw "unable to throw invalid builtin method call Exception"; };
    const char *what() const throw() { return this->err_msg.c_str(); };
};
class InvalidOperationTypeException : public std::exception
{
private:
    std::string err_msg;

public:
    InvalidOperationTypeException(std::string message) : err_msg(message) {}
    ~InvalidOperationTypeException() { throw "unable to throw invalid operation type Exception"; };
    const char *what() const throw() { return this->err_msg.c_str(); };
};
class MissingRequiredBasicBuiltInMethodsException : public std::exception
{
private:
    std::string err_msg;

public:
    MissingRequiredBasicBuiltInMethodsException(std::string message) : err_msg(message) {}
    ~MissingRequiredBasicBuiltInMethodsException() { throw "unable to throw basic methods missing Exception"; };
    const char *what() const throw() { return this->err_msg.c_str(); };
};
#endif