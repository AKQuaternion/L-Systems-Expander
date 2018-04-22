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
friend class RotateCommand;  //!!!need friends, or make a public turtle accessor?
friend class FlipCommand;
friend class PopCommand;
friend class PushCommand;
friend class RuleCommand;
friend class LinesDrawStrategy;
friend class DropDrawStrategy;
public:
    Rulerunner(Lsystem &l, int maxdepth, double minscale, const Consttype &c);
    void draw();
private:
    struct RuleInvocation {
        const Rule &rule;
        bool rulerev;
        bool ruleflip;
        double atScale;
        int depth;
    };
    
    bool isDeepEnough(int depth);
    void handlerule(const RuleInvocation &ri);
    void doCommand(Command &c, const RuleInvocation &ri);

    Ruletable &_therules; //Would like to be const, but calculating/caching parameters changes
    std::string _startrule;
    const Context _context;
    int _maxdepth;
    Turtle _turtle;
    bool _backwards=false;
    double _minscale;
    Lsystem &_lSystem; //Think about this. Do we really want parent pointers?!!!
};
#endif
