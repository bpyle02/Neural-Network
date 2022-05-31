#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.h"

#include <vector>

class Network
{
    std::vector<Layer> m_layers;
    double m_error;
    double m_recentAverageError;
    double m_recentAverageSmoothingFactor;

public:
    Network(const std::vector<unsigned> &topology);

    void feedForward(const std::vector<double> &inputVals);
    void backProp(const std::vector<double> &targetVals);
    void getResults(std::vector <double> &resultVals) const;
    double getRecentAverageError() const;
};

#endif // NETWORK_H
