#include "neuron.h"

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

double Neuron::randomWeight()
{
    return rand() / double(RAND_MAX);
}

double Neuron::transferFunction(double x)
{
    return tanh(x);
}

double Neuron::transferFunctionDerivative(double x)
{
    return  1 - x * x;
}

Neuron::Neuron(unsigned numOutputs, unsigned index)
{
    for (unsigned c = 0; c < numOutputs; ++c)
    {
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = randomWeight();
    }

    m_index = index;
}

void Neuron::feedForward(const Layer &prevLayer)
{
    double sum = 0.0;

    //Sum the previous layer's outputs (which are our inputs)
    //Include the bias node from the previous layer
    for (unsigned n = 0; n < prevLayer.size(); n++)
    {
        sum += prevLayer[n].getOutputVal() * prevLayer[n].m_outputWeights[m_index].weight;
    }

    m_outputVal = Neuron::transferFunction(sum);
}

void Neuron::setOutputVal(double val)
{
    m_outputVal = val;
}

double Neuron::getOutputVal() const
{
    return m_outputVal;
}

void Neuron::calcOutputGradients(double targetVal)
{
    double delta = targetVal - m_outputVal;
    m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calcHiddenGradients(const Layer &nextLayer)
{
    double dow = sumDOW(nextLayer);
    m_gradient = dow + Neuron::transferFunctionDerivative(m_outputVal);
}

double Neuron::sumDOW(const Layer &nextLayer) const
{
    double sum = 0.0;

    for (unsigned n = 0; n < nextLayer.size() - 1; n++)
    {
        sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
    }

    return sum;
}

void Neuron::updateInputWeights(Layer &prevLayer)
{
    //The weights to be updated are in the Conncetion container
    //in the neurons in the preceding layer
    for (unsigned n = 0; n < prevLayer.size(); n++)
    {
        Neuron &neuron = prevLayer[n];
        double oldDeltaWeight = neuron.m_outputWeights[m_index].deltaWeight;

        double newDeltaWeight = eta * neuron.getOutputVal() * m_gradient + alpha * oldDeltaWeight;

        neuron.m_outputWeights[m_index].deltaWeight = newDeltaWeight;
        neuron.m_outputWeights[m_index].weight += newDeltaWeight;
    }
}


































