#include "../inc/System.h"

Eigen::MatrixXd System::createGlobalStiffness(int qno, int num_element) {
    /*
    Creates the Global Stiffness Matrix for the system.

    Parameters:
        - qno (int): Question number
        - num_element (int): Number of elements in the system

    Returns:
        Eigen::MatrixXd: Global Stiffness Matrix
    */

    // Initialize the global stiffness matrix with dimensions (num_element+1, num_element+1).
    Eigen::MatrixXd global_stiffness_matrix = Eigen::MatrixXd::Zero(num_element + 1, num_element + 1);

    // Fill in the values of the global stiffness matrix
    for (int i = 0; i < num_element; i++) {
        double coeff = this->element.getCoeff(qno, i); // Determine the coefficient for the specific element

        // Update the global stiffness matrix using the local stiffness matrix.
        global_stiffness_matrix(i, i) += coeff;
        global_stiffness_matrix(i + 1, i) += -1 * coeff;
        global_stiffness_matrix(i, i + 1) += -1 * coeff;
        global_stiffness_matrix(i + 1, i + 1) += coeff;
    }

    // Return a submatrix corresponding to the actual system size
    return global_stiffness_matrix.block(0, 0, num_element, num_element);
}

Eigen::MatrixXd System::createForceVector(int num_element, double force) {
    /*
    Creates a force vector for the system.

    Parameters:
        - num_element (int): Number of elements
        - force (double): Applied force

    Returns:
        Eigen::MatrixXd: Force vector
    */

    // Initialize the force vector with dimensions
    force_vector = Eigen::MatrixXd::Zero(num_element, 1);

    // Set the first entry of the vector as the applied force, leaving the rest as 0.
    force_vector(0, 0) = force;

    return force_vector;
}

System::System(int qno, int num_element, double force, double Length, double area, double Youngs) :
    num_element(num_element), qno(qno), force(force), Length(Length), element(area, Youngs, Length / num_element) {
    /*
    Constructor for System.

    Parameters:
        - num_element (int): Number of elements
        - force (double): Force
        - qno (int): Question number
        - Length (double): Length of the rod
        - area (T): Area of the rod
        - Youngs (double): Young's modulus of the rod
    */

    // Set the Global Stiffness Matrix and the Force vector of the system.
    global_stiffness_matrix = createGlobalStiffness(qno, num_element);
    force_vector = createForceVector(num_element, force);
}

Eigen::MatrixXd System::getGlobalStiffnessMatrix() {
    /*
    Returns the Global Stiffness Matrix.
    */
    return global_stiffness_matrix;
}

Eigen::MatrixXd System::getForceVector() {
    /*
    Returns the Force Vector.
    */
    return force_vector;
}
