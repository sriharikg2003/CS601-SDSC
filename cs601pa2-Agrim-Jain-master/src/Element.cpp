#include "../inc/Element.h"
#include<iostream>
using namespace std;

// Constructor for the Element class, initializes the properties of the element
Element::Element(double area, double Youngs, double element_length)
    : area(area), Youngs(Youngs), element_length(element_length) {}

double Element::getCoeff(int qno, int index) {

    /*
    Method to calculate the coefficient based on specified parameters.

    Parameters:
        - qno (int): Question number
        - index (int): Index of the node element

    Returns:
        The coefficient value based on the question number and index.
    */

    if (qno == 2) {
        // Computes coefficient for the variable cross-section problem
        double area_left = area * (1 + (element_length * index));
        return ((Youngs * area_left) / element_length);
    }

    // Computes coefficient for the uniform cross-section problem
    return ((Youngs * area) / element_length);
}