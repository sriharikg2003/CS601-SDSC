#include <iostream>
#include <stdexcept>
#include <string>
#include "Eigen/Dense"

using namespace std;

// Print the correct usage of the program 
void printUsage(const char* programName) {
    std::cerr << "Usage: " << programName << " PROB N" << std::endl;
}

// Parse and validate command line arguments
bool parseArguments(int argc, char* argv[], int& prob, int& n) {
    if (argc < 3) {
        printUsage(argv[0]);
        return false;
    }

    std::string strProb = argv[1];
    std::string strN = argv[2];

    try {
        prob = std::stoi(strProb);
        n = std::stoi(strN);

        return true;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return false;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
        return false;
    }
}

// Validate the value of PROB
bool validateProb(int prob) {
    if (prob != 1 && prob != 2) {
        std::cerr << "Invalid value for PROB. Must be 1 or 2." << std::endl;
        return false;
    }
    return true;
}

// Print the solution matrix to the terminal
void printSolnTerminal(Eigen::MatrixXd solution) {
    /*
        Print the solution matrix to the terminal.

        Parameters:
            - solution (Eigen::MatrixXd): Matrix containing the solution values.

        Note:
            - The matrix represents elongation at each node.
            - The solution starts at x = 0 and ends at x = L.
            - There are n+1 entries corresponding to the number of nodes.
    */
    cout << "Solution:" << endl;
    cout << "We are starting with elongation at x = 0 and end at x = L." << endl
         << "Note that there are n+1 entries which correspond to the number of nodes." << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << solution << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

// Create and write the solution matrix to an output text file
void createOutputtxt(Eigen::MatrixXd solution) {
    /*
        Create and write the solution matrix to an output text file.

        Parameters:
            - solution (Eigen::MatrixXd): Matrix containing the solution values.

        Note:
            - The matrix represents elongation at each node.
            - The solution starts at x = 0 and ends at x = L.
            - There are n+1 entries corresponding to the number of nodes.
    */
    std::ofstream outputFile("output.txt");

    // Write to the file
    outputFile << "We are starting with elongation at x = 0 and end at x = L." << endl
               << "Note that there are n+1 entries which correspond to the number of nodes." << endl;
    outputFile << "-------------------------------------------------------------------------------------" << endl;
    outputFile << solution << std::endl;
    outputFile << "-------------------------------------------------------------------------------------" << endl;

    // Close the file
    outputFile.close();
}
