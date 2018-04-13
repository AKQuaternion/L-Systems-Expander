#ifndef RULE_H
#define RULE_H

#include <memory>
using std::make_shared;
using std::shared_ptr;
#include <stdexcept>
using std::logic_error;
#include <list>
using std::list;

#include "Lexer.h"
class Cmd;
#include "Parser.h"

typedef list<shared_ptr<Cmd> > Cmdcont;

class Rule {
    friend class Rulestate;
    friend class Rulerunner;  //!!!be careful with friends?
    friend void readruleoptions(Lexer &, Rule &);
    typedef enum { NORM,
                   DROP,
                   RECT,
                   INVIS,
                   MIDPT } Method;

   public:
    void setcmds(const Cmdcont &newcmds) { cmds = newcmds; }  //!!!need smart ptr here, delete old cmds
    Rule() : drawmethod(NORM) {}                              //!!! initialize scalefac, or fix it later when syntax checking?
    void setdrawmethod(Method m);
    void cachevalues(const Context &cc);

   private:
    Cmdcont cmds;
    Method drawmethod;
    shared_ptr<Parsenode> dropangle;
    shared_ptr<Parsenode> dropdistance;
    shared_ptr<Parsenode> rectwidth;
    shared_ptr<Parsenode> scalefac;
    double cacheddropangle;
    double cacheddropdistance;
    double cachedrectwidth;
    double cachedscalefac;
    string info;
    //Color
};

typedef map<string, Rule> Ruletable;

#endif
