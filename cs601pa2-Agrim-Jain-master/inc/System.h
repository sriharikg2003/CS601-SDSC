#ifndef SYSTEM_H
#define SYSTEM_H

#include "Eigen/Dense"
#include "Element.h"

// The System class represents a physical system with finite elements.
class System {
private:
    int num_element;                    // Number of elements in the system
    int qno;                            // Question number
    double force;                       // Applied force
    double Length;                      // Length of the rod
    Element element;                    // Element object representing properties of the rod
    Eigen::MatrixXd global_stiffness_matrix;   // Global Stiffness Matrix
    Eigen::MatrixXd force_vector;               // Force Vector

public:
    // Creates and returns the Global Stiffness Matrix
    Eigen::MatrixXd createGlobalStiffness(int qno, int num_element);

    // Creates and returns the Force Vector
    Eigen::MatrixXd createForceVector(int num_element, double force);

    // Constructor for the System class
    System(int qno, int num_element, double force, double Length, double area, double Youngs);

    // Returns the Global Stiffness Matrix
    Eigen::MatrixXd getGlobalStiffnessMatrix();

    // Returns the Force Vector
    Eigen::MatrixXd getForceVector();
};

#endif // SYSTEM_H
