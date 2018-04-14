#ifndef CMD_H
#define CMD_H

#include <string>
#include <list>

#include "Context.h"
#include "Parser.h"
#include "Rulerunner.h"

class Cmd {
   public:
    virtual void execute(Rulerunner *master) = 0;
    virtual ~Cmd()=default;
    virtual void cachevalue(const Context &) {}

   private:
    static bool lastconstruct;
};

typedef std::list<std::shared_ptr<Cmd> > Cmdcont;

class Rotatecmd : public Cmd {
   public:
    explicit Rotatecmd(std::shared_ptr<Parsenode> _a) : angle(_a) {}
    void execute(Rulerunner *master) override { master->turtles.top().rotate(cachedangle); }
    void cachevalue(const Context &cc) override { cachedangle = angle->eval(cc); }

   private:
    std::shared_ptr<Parsenode> angle;
    double cachedangle;
};

class Flipcmd : public Cmd {
   public:
    void execute(Rulerunner *master) override { master->turtles.top().flip(); }
};

class Pushcmd : public Cmd {
   public:
    void execute(Rulerunner *master) override { master->pushturtle(); }
};

class Popcmd : public Cmd {
   public:
    void execute(Rulerunner *master) override {
        master->popturtle();
        Dropgraphic::haveapt = false;
    }
};

class Rulecmd : public Cmd {
   public:
    explicit Rulecmd(const std::string &_m, bool _r = false, bool _f = false,
            std::shared_ptr<Parsenode> _s = Parser("1").parse())
        : myrule(_m), rev(_r), flip(_f), scale(_s) {}
    void execute(Rulerunner *master) override { master->handlerule(myrule, rev, flip, cachedscale); }
    void cachevalue(const Context &cc) override { cachedscale = scale->eval(cc); }

   private:
    const std::string myrule;
    bool rev;
    bool flip;
    std::shared_ptr<Parsenode> scale;
    double cachedscale;
};
#endif
