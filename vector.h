#pragma once
class vector_t
{
private:
    
public:
    double x, y;
    vector_t(double x, double y);
    ~vector_t();

    void normalization();
    double operator * (const vector_t& v2);
    vector_t operator * (const double& number);
    vector_t operator / (const double& number);
    vector_t operator + (const vector_t& v2);
    vector_t operator - (const vector_t& v2);
};

