#include <iostream>
#include <fstream>

#include "Eigen/Dense"
#include "Element.cpp"
#include "Solver.cpp"
#include "System.cpp"
#include "Helper.cpp"
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    // Initialize variables for the problem and number of elements
    int prob, n;

    // Check for the validity of inputs
    if (!parseArguments(argc, argv, prob, n) || !validateProb(prob)) {
        return 1;
    }

    // Domain parameters
    double area = 0.00125;
    double Youngs = 70000000000;
    double Length = 0.5;
    int num_element = n;
    double force = 5000;
    int qno = prob;

    // Start the solution process
    auto start = std::chrono::high_resolution_clock::now();
    System system(qno, num_element, force, Length, area, Youngs);
    Solver solver(system);
    Eigen::MatrixXd solution = solver.solve();
    // The solution is a vector containing the elongation at each node.
    auto stop = std::chrono::high_resolution_clock::now();

    // Print the solution to the terminal
    printSolnTerminal(solution);
    // Output the solution into a text file
    createOutputtxt(solution);

    // Calculate and print the execution time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
