#ifndef CONTEXT_H
#define CONTEXT_H

#include <map>
#include <memory>
#include <string>
#include <utility>

class Parsenode;

using Consttype = std::map<std::string, double>;
using Exprtype = std::map<std::string, std::shared_ptr<Parsenode>>;

class Context {
   public:
    Context(Consttype _c, Exprtype _e) : constants(std::move(_c)), expressions(std::move(_e)) {}
    const Consttype constants;
    const Exprtype expressions;
};

#endif
