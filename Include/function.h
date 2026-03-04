#ifndef FUNCTION_H
#define FUNCTION_H


class RootMethod
{
protected:
    double tol;

public:
    RootMethod();
    virtual void solve() = 0;
    virtual ~RootMethod(){}
};



class Bisection : public RootMethod
{
public:
    Bisection();
    void solve();
};



class Newton : public RootMethod
{
public:
    Newton();
    void solve();
};



class FixedPoint : public RootMethod
{
public:
    FixedPoint();
    void solve();
};

#endif
