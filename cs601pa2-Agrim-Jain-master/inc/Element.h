#ifndef ELEMENT_H
#define ELEMENT_H

// Element class represents the properties of a finite element in a rod structure.
class Element {
private:
    double area;            // Cross-sectional area of the element
    double Youngs;          // Young's modulus of the material
    double element_length;  // Length of each element

public:
    // Constructor for the Element class, initializes the properties of the element.
    Element(double area, double Youngs, double element_length);

    // Computes and returns the coefficient at each index for a specific question number (qno).
    double getCoeff(int qno, int index);
};

#endif // ELEMENT_H