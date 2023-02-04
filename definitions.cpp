#include <definitions.h>

vector<double> operator-(vector<double> x, vector<double> y)
{
    size_t len = x.size();
    if (len != y.size())
        return x;
    for (size_t i = 0; i < len; ++i)
        x[i] -= y[i];
    return x;
}

vector<double> operator-(vector<double> x)
{
    int len = x.size();
    for (int i = 0; i < len; ++i)
        x[i] = -x[i];
    return x;
}

vector<double> operator+(vector<double> x, vector<double> y)
{
    return x - (-y);
}

vector<double> operator*(vector<vector<double>> a, vector<double> y)
{
    size_t len = a[0].size();
    if (len != y.size())
        return y;
    vector<double> x;
    for (size_t i = 0; i < len; ++i)
    {
        double s = 0;
        for (size_t j = 0; j < len; ++j)
        {
            s += a[i][j] * y[j];
        }
        x.push_back(s);
    }
    return x;
}

vector<double> operator*(double c, vector<double> x)
{
    size_t len = x.size();
    for (size_t i = 0; i < len; ++i)
        x[i] *= c;
    return x;
}



double norm(vector<double> x)
{
    double s = 0;
    size_t len = x.size();
    for (size_t i = 0; i < len; ++i)
        s += x[i] * x[i];
    return sqrt(s);
}

double f_0(vector<double>& x)
{
    return x[1];
}



