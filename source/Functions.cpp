#include "Functions.h"


// Functions::lorentzProfile()
//
// PURPOSE: 
//      Computes a simple Lorentzian profile given the centroid and the width.
//      Saves the dependent variable values into a vector y accessible as
//      public data member.
//
// INPUT:
//      predictions : vector containing the result
//      covariates : vector containing independent variable values
//      centroid : centroid of the Lorentzian profile (default = 0)
//      amplitude : maximum height of the Lorentzian profile (default = 1)
//      gamma : width of the Lorentzian profile (mode linewidth) (default = 1)
//
// OUTPUT:
//      void
//

void Functions::lorentzProfile(RefArrayXd predictions, const RefArrayXd covariates, double centroid, double amplitude, double gamma)
{
        predictions = (amplitude*amplitude)/((covariates-centroid)*(covariates-centroid) + (gamma/2.)*(gamma/2.));

} // END Functions::lorentzProfile()










// Functions::logGaussProfile()
//
// PURPOSE: 
//      Computes the logarithm of a Gaussian profile given the centroid, 
//      the standard deviation and the amplitude, for one given x-value
//
// INPUT:
//      covariate : independent variable
//      mu : mean value of the Gaussian profile (default = 0)
//      sigma : standard deviation of the Gaussian profile (default = 1)
//      amplitude : maximum amplitude of the Gaussian profile (default = 1)
//
// OUTPUT:
//      The natural logarithm of the Gaussian profile value of the independent variable.
//

double Functions::logGaussProfile(const double covariate, const double mu, const double sigma, const double amplitude)
{
    const double prefactor = log(amplitude) - 0.5 * log(2*Functions::PI) - log(sigma);

    return prefactor - 0.5 * (covariate - mu) * (covariate - mu) / (sigma * sigma);

} // END Functions::logGaussProfile() 








// Functions::logGaussProfile()
//
// PURPOSE: 
//      Computes the logarithm of a Gaussian profile given the centroid, 
//      the standard deviation and the amplitude for a set of values (overloaded)
//
// INPUT:
//      predictions : Eigen array containing the result
//      covariates : Eigen array containing independent variable values
//      mu : mean value of the Gaussian profile (default = 0)
//      sigma : standard deviation of the Gaussian profile (default = 1)
//      amplitude : maximum amplitude of the Gaussian profile (default = 1)
//
// OUTPUT:
//      void
//

void Functions::logGaussProfile(RefArrayXd predictions, const RefArrayXd covariates, const double mu, const double sigma, const double amplitude)
{
    const double prefactor = log(amplitude) - 0.5 * log(2*Functions::PI) - log(sigma);
    predictions = prefactor - 0.5 * (covariates - mu) * (covariates - mu) / (sigma * sigma);
    
} // END MathExra::logGaussProfile()









// Functions::logGaussLikelihood() 
//
// PURPOSE: 
//      Computes the log-Gaussian likelihood from a set of observations,
//      uncertainties, and theoretical predictions.
//
// INPUT:
//      observations : array containing the oberved values
//      predictions : array containing the corresponding predicted values of x
//      uncertainties : array containing the uncertanties on the observed values
//
// OUTPUT:
//      The resulting value of the log-Gaussian likelihood.
//

double Functions::logGaussLikelihood(const RefArrayXd observations, const RefArrayXd predictions, const RefArrayXd uncertainties)
{
    if ((observations.size() != predictions.size()) || (observations.size() != uncertainties.size()))
    {
        cerr << "Array dimensions do not match. Quitting program." << endl;
        exit(EXIT_FAILURE);
    }
    
    ArrayXd delta;
    ArrayXd lambda0;
    ArrayXd lambda;
    
    delta = ((observations - predictions)*(observations - predictions)) / (uncertainties*uncertainties);
    lambda0 = -1.*log(sqrt(2.*PI) * uncertainties);
    lambda = lambda0 -0.5*delta;
    
    return lambda.sum();

} // END Functions::logGaussLikelihood()










// Functions::clusterCovariance()
//
// PURPOSE:
//      Compute the covariance matrix of a set of points belonging to a cluster.
//
// INPUT:
//      clusterSample: an Eigen Array matrix of size (Ndimensions, Npoints)
//      containing coordinates of all the points belonging to the cluster.
//      covarianceMatrix: an Eigen Array matrix of size (Ndimensions, Ndimensions) where the
//      covariance matrix is stored.
//      centerCoordinates: an Eigen Array of size Ndimensions where the coordinates of the
//      center (mean values) of the cluster of points are stored.
//
// OUTPUT:
//      void
//

void Functions::clusterCovariance(const RefArrayXXd clusterSample, RefArrayXXd covarianceMatrix, RefArrayXd centerCoordinates)
{    
    int Ndimensions = clusterSample.rows();
    int Npoints = clusterSample.cols();
    covarianceMatrix.resize(Ndimensions, Ndimensions);
    centerCoordinates.resize(Ndimensions);

    for (int i=0; i < Ndimensions; i++)
    {
        centerCoordinates(i) = (clusterSample.row(i).sum())/Npoints;
    }

    double biasFactor = 1./(Npoints-1);

    for (int i=0; i < Ndimensions; i++)
    {
        for (int j=0; j < Ndimensions; j++)
        {
            covarianceMatrix(i,j) = biasFactor * ((clusterSample.row(i) - centerCoordinates(i))*(clusterSample.row(j) - centerCoordinates(j))).sum();
        }
    }

}











// Functions::selfAdjointMatrixDecomposition()
//
// PURPOSE:
//      Compute the decomposition of a covariance matrix into eigenvectors and eigenvalues.
//
// INPUT:
//      covarianceMatrix: an Eigen Array matrix to be decomposed
//      eigenvalues: an Eigen Array to contain the eigenvalues 
//      of the covariance matrix
//      eigenvectorsMatrix: an Eigen Array matrix to contain the matrix of
//      the eigenvectors of the covariance matrix
//
// OUTPUT:
//      void
//

void Functions::selfAdjointMatrixDecomposition(const RefArrayXXd covarianceMatrix, RefArrayXd eigenvalues, RefArrayXXd eigenvectorsMatrix)
{
    assert(covarianceMatrix.cols() == covarianceMatrix.rows());
    assert(eigenvalues.size() == covarianceMatrix.cols());
    assert(eigenvectorsMatrix.cols() == eigenvectorsMatrix.rows());
    assert(eigenvectorsMatrix.cols() == eigenvalues.size());

    SelfAdjointEigenSolver<MatrixXd> eigenSolver(covarianceMatrix.matrix());

    if (eigenSolver.info() != Success) abort();

    eigenvalues = eigenSolver.eigenvalues();
    eigenvectorsMatrix = eigenSolver.eigenvectors();
}










// Functions::product()
//
// PURPOSE: 
//      Computes the product of the elements contained in a vector of doubles of class vector.
//
// INPUT:
//      vec : vector of values to be multiplied
//
// OUTPUT:
//      The productoria of the vector elements.
//

inline double Functions::product(const vector<double> &vec)
{
    return accumulate(vec.begin(), vec.end(), 1.0, multiplies<double>());
} // END Functions::product()









// Functions::sum()
//
// PURPOSE: 
//      Computes the sum of the elements contained in a vector of doubles of vector class.
//
// INPUT:
//      vec : vector of values to be added.
//
// OUTPUT:
//      The summation of the vector elements.
//

inline double Functions::sum(const vector<double> &vec)
{
    return accumulate(vec.begin(), vec.end(), 0.0);
} // END Functions::sum()










// Functions::logExpSum()
//
// PURPOSE: 
//      Computes a logaritmic summation of exponentials in order to avoid overflow errors.
//
// INPUT: 
//      x : a first variable to be added
//      y : a second variable to be added
//
// OUTPUT: 
//      The logarithmic summation of the exponentials log(exp(x)+exp(y)).
//

double Functions::logExpSum(double x, double y)
{
    return (x >= y ? x + log(1.+exp(y-x)) : y + log(1.+exp(x-y)));
} // END Functions::logExpSum()










// Functions::sortElementsDouble()
//
// PURPOSE: 
//      Sorts the element of the first input array in increasing order 
//      and the elements of the second input array according to the 
//      sorting of the first array.
//
// INPUT: 
//      array1: a first Eigen Array of double numbers to be sorted in increasing order 
//      array2: a second Eigen Array to be sorted according to array1
//
// OUTPUT: 
//      void
//

void Functions::sortElementsDouble(RefArrayXd array1, RefArrayXd array2)
{
    for (int i = 0; i < array1.size(); i++)
    {
        for (int j = 1; j < (array1.size()-i); j++)
        {
            if (array1(j-1) > array1(j))
            {
                SWAPDOUBLE(array1(j-1),array1(j));        // SWAP array1 elements in increasing order
                SWAPDOUBLE(array2(j-1),array2(j));        // SWAP array2 elements accordingly
            }
            else
                if (array1(j-1) == array1(j))
                    continue;
        }
    }
    
} // END Functions::sortElementsDouble()













// Functions::sortElementsInt()
//
// PURPOSE: 
//      Sorts the element of the first input array in increasing order 
//      and the elements of the second input array according to the 
//      sorting of the first array.
//
// INPUT: 
//      array1: a first Eigen Array of integer values to be sorted in increasing order 
//      array2: a second Eigen Array to be sorted according to array1
//
// OUTPUT: 
//      void
//

void Functions::sortElementsInt(RefArrayXi array1, RefArrayXd array2)
{
    for (int i = 0; i < array1.size(); i++)
    {
        for (int j = 1; j < (array1.size()-i); j++)
        {
            if (array1(j-1) > array1(j))
            {
                SWAPINT(array1(j-1),array1(j));         // SWAP array1 elements in increasing order
                SWAPDOUBLE(array2(j-1),array2(j));      // SWAP array2 elements accordingly
            }
            else
                if (array1(j-1) == array1(j))
                    continue;
        }
    }
    
} // END Functions::sortElementsInt()















// Functions::BoxMullerDistribution()
//
// PURPOSE: 
//      Generates a 2D normal distribution from a uniform distribution by
//      means of the Box-Muller algorithm.
//
// INPUT:
//      Npoints: number of samples in the distribution.
//      sampleDistribution: an Eigen Array of size (2, Npoints) to contain the
//      points normally distributed.
//
// OUTPUT:
//      void
//
// REMARKS:
//      THe two normal distributions generated have both zero mean and unit standard deviation.
//

void Functions::BoxMullerDistribution(RefArrayXXd sampleDistribution, const int Npoints)
{
    mt19937 engine(time(0));
    uniform_real_distribution<double> uniform_dist(0.0,1.0);
    auto uniform = bind(uniform_dist, engine);
    ArrayXd u;
    ArrayXd v;

    sampleDistribution.resize(2, Npoints);

    for (int i = 0; i < Npoints; i++)
    {
        u(i) = uniform();
        v(i) = uniform();
        sampleDistribution(0,i) = sqrt(-2*log(u(i))) * cos(2*PI*v(i));
        sampleDistribution(1,i) = sqrt(-2*log(u(i))) * sin(2*PI*v(i));
    }

}

