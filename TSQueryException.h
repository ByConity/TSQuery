#include <exception>
#include <string>


namespace  DB
{

namespace TSQuery 
{

class TSQueryException : public std::exception 
{

public:
    TSQueryException(const std::string &arg) 
    {
        detail = "[[TSQuery ERROR]]: " + arg;
    }

  virtual const char *what() const throw() override { return detail.c_str(); }

protected:
    std::string detail;
};

} // namespace TSQuery

} // namespace DB