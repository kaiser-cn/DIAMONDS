// Derived class for sampling from an ellipsoid build
// from a sample of points according to the
// nesting algortihm. The class is based on the
// sampling technique of the MultiNest code presented 
// by Feroz F. et al. (2008, 2009).
// Created by Enrico Corsaro @ IvS - 28 March 2013
// e-mail: enrico.corsaro@ster.kuleuven.be
// Header file "MultiEllipsoidSampler.h"
// Implementation contained in "MultiEllipsoidSampler.cpp"

#ifndef MULTIELLIPSOIDSAMPLER_H
#define MULTIELLIPSOIDSAMPLER_H

#include <random>
#include <Eigen/Dense>
#include "NestedSampler.h"
#include "Ellipsoid.h"
#include "Prior.h"

using namespace std;

class MultiEllipsoidSampler : public NestedSampler
{

    public:
       
        MultiEllipsoidSampler(const bool printOnTheScreen, vector<Prior*> ptrPriors, 
                              Likelihood &likelihood, Metric &metric, Clusterer &clusterer, 
                              const int Nobjects, const double initialEnlargementFactor, const double shrinkingRate);
        ~MultiEllipsoidSampler();
        
        virtual void drawWithConstraint(const RefArrayXXd totalSampleOfParameters, const int Nclusters, const vector<int> &clusterIndices,
                                        const double logTotalWidthInPriorMass, RefArrayXXd drawnSampleOfParameters, const int NloopMaximum); 

        void computeEllipsoids(const RefArrayXXd totalSampleOfParameters, const int Nclusters, const vector<int> &clusterIndices, 
                               const double logRemainingWidthInPriorMass);
        
        vector<int> getNonOverlappingEllipsoidsIndices();
        vector<int> getOverlappingEllipsoidsIndices();
        vector<Ellipsoid> getEllipsoidsVector();
   

    protected:
      
        void findOverlappingEllipsoids();


    private:

        vector<Ellipsoid> ellipsoids;
        vector<int> NobjectsPerCluster;
        vector<int> nonOverlappingEllipsoidsIndices;
        vector<int> overlappingEllipsoidsIndices;
        int Nellipsoids;                        // Total number of ellipsoids computed
        double initialEnlargementFactor;        // Initial factor for enlargement of ellipsoids
        double shrinkingRate;                   // Prior volume shrinkage rate (between 0 and 1)
        double logRemainingWidthInPriorMass;    // log value of the total remaining prior mass at the actual nested iteration

};

#endif
