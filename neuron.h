#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cstdlib>
#include <cmath>

class Neuron;

using Layer = std::vector<Neuron>;

struct Connection
{
    double weight;
    double deltaWeight;
};

class Neuron
{
    double m_outputVal;
    std::vector<Connection> m_outputWeights;
    unsigned m_index;
    double m_gradient;
    static double eta;
    static double alpha;

    static double randomWeight();
    static double transferFunction(double x);
    static double transferFunctionDerivative(double x);

public:
    Neuron(unsigned numOutputs, unsigned index);

    void feedForward(const Layer &prevLayer);
    void setOutputVal(double val);
    double getOutputVal() const;
    void calcOutputGradients(double targetVal);
    void calcHiddenGradients(const Layer &nextLayer);
    double sumDOW(const Layer &nextLayer) const;
    void updateInputWeights(Layer &prevLayer);
};

#endif // NEURON_H
