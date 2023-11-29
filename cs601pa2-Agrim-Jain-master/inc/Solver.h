#ifndef SOLVER_H
#define SOLVER_H

#include "Eigen/Dense"
#include "System.h"

// Solver class handles the solution of a linear system represented by a System object.

class Solver {
private:
    Eigen::MatrixXd global_stiffness_matrix;  // Stores the global stiffness matrix
    Eigen::MatrixXd force_vector;             // Stores the force vector

public:
    // Constructor for the Solver class, taking a System object as a parameter.
    Solver(System system);

    // Method to solve the linear system and return the solution matrix.
    Eigen::MatrixXd solve();
};

#endif // SOLVER_H
