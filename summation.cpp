#include <algorithm>
#include <iostream>
#include <map>
#include <random>
using namespace std;
int main()
{
    std::map<float,unsigned int> imprecision;
    const int N = 1e6;

    std::random_device Maxwell;
    std::default_random_engine prng;
    prng.seed(Maxwell());

    std::vector<float> x;
    #ifdef DECIMAL
    for (unsigned int i = 0; i < 9; i++) {
        x.push_back(   0.001);
        x.push_back(   0.01);
        x.push_back(   0.1);
        x.push_back(   1.);
        x.push_back(  10.);
        x.push_back( 100.);
        x.push_back(1000.);
    }
    x.push_back(0.001); // there's an extra one of these guys

    #else
    for (unsigned int i = 0; i < 8; i++) {
        x.push_back(0.0625);
        x.push_back(0.1250);
        x.push_back(0.2500);
        x.push_back(0.5000);
        x.push_back(1.0000);
        x.push_back(2.0000);
        x.push_back(4.0000);
        x.push_back(8.0000);
    }
    x.push_back(0.5000); // there's an extra one of these guys

    #endif

    for (unsigned int i = 0; i < N; i++) {
        random_shuffle(x.begin(), x.end());
        float z = 0;
        for (unsigned int i = 0; i < x.size(); i++)
            z += x[i];

        imprecision[z]++;
    }

    for (map<float,unsigned int>::const_iterator it = imprecision.begin(); it != imprecision.end(); it++) {
        printf("%32.26f: %12.9f %%\n", it->first, double(100*it->second)/N);
    }

    return 0;
}
