// Main code for peak bagging by means of nested sampling analysis
// Created by Enrico Corsaro @ IvS - 24 January 2013
// e-mail: enrico.corsaro@ster.kuleuven.be
// Source code file "peakbagging.cpp"

#include <iostream>
#include <iomanip>
#include "MathExtra.h"
#include "FileProcess.h"
#include "NestedSampler.h"
#include "NormalVariate.h"

int main()
{
    int Ndata = 100;      // Number of objects per nested iteration (usually 100)
    int Niter = 1000;     // Number of nested iterations (usually 1000)
    
    NormalVariate normalVariate(10.0, 3.0);
    normalVariate.setBoundaries(0.0, 20.0);
    NestedSampler nestedSampler(normalVariate);
    nestedSampler.run(Ndata, Niter);
    
    cout << right << setw(10) << "Parameter value" << right << setw(20) << "logLikelihood" << endl;
    for (int i = 0; i < Niter; i++)
    {
       cout << right << setw(10) << nestedSampler.posteriorSample[i]
            << right << setw(20) << nestedSampler.logLikelihoodOfPosteriorSample[i] 
            << endl;
    }
    
    cout << endl;
    cout << " ------------------------------------------------" << endl;
    cout << " Evidence: logZ = " << nestedSampler.getLogEvidence() << " +/- " << nestedSampler.getLogEvidenceError() << endl;
    cout << " Information: H = " << nestedSampler.getInformationH() << endl;
    cout << " ------------------------------------------------" << endl;
}
