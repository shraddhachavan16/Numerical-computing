
#ifndef GAUSSIAN_H
#define GAUSSIAN_H
#include <vector>
#include <string>
class Gaussian
{
protected:
    int n;
    std::vector<std::vector<double>> A;
    std::vector<std::vector<double>> A_original;
    std::vector<double> x;

public:
    Gaussian(int size);                
    virtual ~Gaussian() {}             
    bool readFile(const std::string& filename);
    virtual bool solve() = 0;          
    const std::vector<double>& getSolution() const;
    
};

class NoPivot : public Gaussian
{
public:
    NoPivot(int size);
    bool solve() override;
};

class WithPivot : public Gaussian
{
public:
    WithPivot(int size);
    bool solve() override;
};

#endif