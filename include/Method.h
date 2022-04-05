#include "libraries.h"
#include "Graph.h"
#pragma once

#ifndef _METHOD_H
#define _METHOD_H

class Method {
    public:
    Method();
    Method(std::string);
    ~Method();
    virtual Pair SolveMethod() = 0;
    protected:
    Graph* graph_;
    
};

Method::Method() {}

Method::Method(std::string name) {
    graph_ = new Graph(name);
}

Method::~Method() {}

#endif //_METHOD_H
