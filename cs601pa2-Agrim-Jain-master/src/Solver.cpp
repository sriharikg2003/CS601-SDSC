#include "../inc/Solver.h"
#include <iostream>

// Constructor for Solver class, takes a System object as a parameter
Solver::Solver(System system) {
    // Initialize private member global_stiffness_matrix with the Eigen matrix from the System object
    global_stiffness_matrix = system.getGlobalStiffnessMatrix();
    // Initialize private member force_matrix with the Eigen force matrix from the System object
    force_vector = system.getForceVector();
}

// Solve method for Solver class, returns the solution matrix
Eigen::MatrixXd Solver::solve() {

    /*
    Function to compute the vector containing elongations.
    
    Returns:
        - Eigen::MatrixXd: Vector containing elongations of each node.
    
    Procedure:
        1. Calculate the pseudo-inverse of the global_stiffness_matrix using complete orthogonal decomposition.
        2. Calculate the solution by multiplying the pseudo-inverse with the force_vector.
        3. Resize the solution matrix to add a row and set the values in the added row to zero (elongation at the point where it is hinged).
        4. Return the final solution matrix.
    */

    // Calculate the pseudo-inverse of the global_stiffness_matrix using complete orthogonal decomposition
    Eigen::MatrixXd pseudoinverse = this->global_stiffness_matrix.completeOrthogonalDecomposition().pseudoInverse();

    // Calculate the solution by multiplying the pseudo-inverse with the force_vector
    Eigen::MatrixXd solution = pseudoinverse * this->force_vector;

    // Resize the solution matrix to add a row and set the values in the added row to zero (elongation at the point where it is hinged)
    solution.conservativeResize(solution.rows() + 1, Eigen::NoChange);
    solution.row(solution.rows() - 1).setZero();

    // Return the final solution matrix
    return solution;
}
