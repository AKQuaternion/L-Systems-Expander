#ifndef RULERUNNER_H
#define RULERUNNER_H

#include "Context.h"
#include "Lsystem.h"
#include "Parser.h"
#include "Rule.h"
#include "Turtle.h"
#include <list>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>


class Lexer;
class Lsystem;

class Rulerunner {
friend class Command;
friend class PopCommand; //Turtle pops need to know about drawstrategies
friend class RuleCommand; //Rules need to call handlerule
friend class LinesDrawStrategy;
friend class DropDrawStrategy;
friend class DrawStrategy;
public:
    Rulerunner(Lsystem &l, int maxdepth, double minscale, const Consttype &c);
    const Context & getContext() const;
    void draw();
private:
    bool isDeepEnough(int depth);

    Ruletable &_therules; //Would like to be const, but calculating/caching parameters changes
    //!!! can access throu _lSystem?
    std::string _startrule;
    const Context _context;
    int _maxdepth;
    Turtle _turtle;
    bool _backwards=false; //!!!move into RuleCommand?
    double _minscale;
    Lsystem &_lSystem; //Think about this. Do we really want parent pointers?!!!
};
#endif
