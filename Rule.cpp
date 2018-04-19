// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Rule.h"
#include "Cmd.h"
#include <exception>

void Rule::setdrawmethod(Method m) {
    switch (m) {
        case NORM:
            break;
        case DROP:
            if (!_dropAngleExpression)
                _dropAngleExpression = Parser("0").parse();
            if (!_dropDistanceExpression)
                _dropDistanceExpression = Parser("1").parse();
            break;
        case RECT:
            if (!_rectWidthExpression)
                _rectWidthExpression = Parser("0.1").parse();
            break;
        case INVIS:
        case MIDPT:
        case WRITE:
            break;
    }
    drawmethod = m;
}

void Rule::readruleoptions(Lexer &lex) {
    Token t = lex.nexttoken();
    
    while (t.isdata()) {
        if (t.getdata() == "drawmethod") {
            t = lex.nexttoken();
            assertdatatoken(t);
            if (t.getdata() == "drop")
                setdrawmethod(Rule::DROP);
            else if (t.getdata() == "normal")
                setdrawmethod(Rule::NORM);
            else if (t.getdata() == "rectangle")
                setdrawmethod(Rule::RECT);
            else if (t.getdata() == "invisible")
                setdrawmethod(Rule::INVIS);
            else if (t.getdata() == "midpoint")
                setdrawmethod(Rule::MIDPT);
            else if (t.getdata() == "write")
                setdrawmethod(Rule::WRITE);
            else
                throw std::runtime_error("Unexpected draw method " + t.getdata());
        } else if (t.getdata() == "dropangle") {
            t = lex.nexttoken();
            assertdatatoken(t);
            _dropAngleExpression = Parser(t.getdata()).parse();  //!!! Rule member function? (then can take away friendship)
        } else if (t.getdata() == "dropdistance") {
            t = lex.nexttoken();
            assertdatatoken(t);
            _dropDistanceExpression = Parser(t.getdata()).parse();  //!!! Rule member function? (then can take away friendship)
        } else if (t.getdata() == "rectwidth") {
            t = lex.nexttoken();
            assertdatatoken(t);
            _rectWidthExpression = Parser(t.getdata()).parse();  //!!! Rule member function? (then can take away friendship)
        }                                               //!!!fix similarity of last three elseifs
        else if (t.getdata() == "info") {
            t = lex.nexttoken();
            assertdatatoken(t);
            _info = t.getdata();
        }  //!!!even this is pretty similar,
        else if (t.getdata() == "localscale") {
            t = lex.nexttoken();
            assertdatatoken(t);
            _localScaleExpression = Parser(t.getdata()).parse();  //!!! Rule member function? (then can take away friendship)
        } else
            throw std::runtime_error("Unexpected option " + t.getdata());
        t = lex.nexttoken();
    }
}

void Rule::calculateParameters(const Context& cc) {
    for (auto & cmd : cmds)
        cmd->evaluateExpressions(cc);
    switch (drawmethod) {
        case DROP:
            _dropAngle = _dropAngleExpression->eval(cc) * M_PI / 180.0;  //!!! cache sin and cos instead?
            _dropDistance = _dropDistanceExpression->eval(cc);
            break;
        case RECT:
            _rectWidth = _rectWidthExpression->eval(cc);
            break;
        case NORM:
        case INVIS:
        case MIDPT:
        case WRITE:
            break;
    }
    _localScale = _localScaleExpression ? _localScaleExpression->eval(cc) : 1;
}
