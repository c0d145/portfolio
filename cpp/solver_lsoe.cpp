/*
* This program implements a solver for linear system of equations utilizing
* LU-Decomposition with pivoting.
*
* Author: c0d145
* Created: 2022-05-17
* Updated: 2022-05-19,
*          2022-05-05: Fixed mistake in solution calculation. 
* 					   Usage of pointer instead of data copies at function calls.
*                      Added third example.
*          2022-06-09: Added debug mode toggle by using 'talkative' variable.
*/
#include <sstream>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

/*
 * Function which converts comma sperated strings to a float vector.
 */
vector<float> parseFloats(string str) {
    stringstream ss(str);
    vector<float> floats;
    char ch;
    float value;
    while(ss >> value >> ch) {
        floats.push_back(value);
    }
    ss >> value;
    floats.push_back(value);
    return floats;
}

void printMatrix(vector<vector<float>> *matrix)
{
    //vector<vector<float>> matrixA = *matrix;
    for(int i = 0; i < matrix->data()[0].size(); i++)
    {
        for(int j = 0; j < matrix->data()[0].size(); j++)
        {
            std::cout << matrix->data()[i][j];
            if(j < matrix->data()[0].size()-1)
            {
                std::cout << ",";
            }
        }
        std::cout << std::endl;
    }
}

vector<float> calcy(int *m, vector<vector<float>> *matrixL, vector<float> *b)
{
    vector<float> y (*m, 0.0);
    for (int i = 0; i < *m; i++)
    {
        float sum = 0.0;
        for (int j = 0; j<i; j++)
        {
            sum += matrixL->data()[i][j] * y[j];
        }
        y[i] = (1 / matrixL->data()[i][i]) * (b->data()[i] - sum);
    }
    return y;
}

vector<float> calcx(int *m, vector<vector<float>> *matrixU, vector<float> *y)
{
    vector<float> x (*m,0.0);
    for (int i = *m-1; i >= 0; i--)
    {
        float sum = 0.0;
        if (i == *m-1)
        {
            x[i] = y->data()[i] / matrixU->data()[i][i];
        } else {
            for (int j = i+1; j < *m; j++)
            {
                sum += matrixU->data()[i][j] * x[j];
            }
            x[i] = (1 / matrixU->data()[i][i]) * (y->data()[i] - sum);
        }
    }
    return x;
}

vector<vector<float>> identityMatrix(int m)
{
    int dim = m;
    vector<vector<float>> matrixI;
    for(int i = 0; i<dim; i++)
    {
        vector<float> myvector;
        myvector.clear();
        for(int j = 0; j<dim; j++)
        {
            if (i==j)
            {
                myvector.push_back(1.0);
            } else {
                myvector.push_back(0.0);
            }
        }
        matrixI.push_back(myvector);
    }
    return matrixI;
}

// Reads dimension of matrix A from stdin.
int readMatrixDim ()
{
    string matrixdim;
    std::cout << "LU-Loeser. Bitte das Format m eingeben: ";
    cin >> matrixdim;
    stringstream ss(matrixdim);
    int m = 0;
    ss >> m;
    return m;
}

// Reads Matrix A line by line from stdin.
vector<vector<float>> readMatrixA(int m) {
    vector<vector<float>> matrixA;

    // Read matrix linewhise and save as 2D float vector.
    for (int i = 0; i<m; i++)
    {
        std::cout<<"Zeile " << std::to_string(i+1) << " von A eingeben: ";
        string line;
        cin >> line;
        matrixA.push_back(parseFloats(line));
    }
    return matrixA;
}


void pivotize(int m,vector<vector<float>> *matrixU,vector<vector<float>> *matrixL,vector<vector<float>> *matrixP, vector<float> *b, bool talkative)
{
    for (int k = 0; k<m-1; k++)
    {
        float pivot = matrixU->data()[k][k]; // = *max_element(matrixU[0].begin(), matrixU[0].end(), compare);
        int pivoti = k;

        // Iterate over all lines i to find pivot element.
        for (int i = k; i < matrixU->data()[0].size(); i++)
        {
            if(abs(matrixU->data()[i][k]) > abs(pivot))
            {
                    pivot = matrixU->data()[i][k];
                    pivoti = i;
            }
        }

        //std::cout << "Pivot element is: " << pivot << " Line is: " << pivoti << std::endl;

        // Stwich lines
        // vector<float> tmp(m,0);
        float tmp = 0.0;

        for (int j=k;j<m;j++)
        {
            // Save entry.
            tmp = matrixU->data()[k][j];
            // Swap / overwrite entry.
            matrixU->data()[k][j] = matrixU->data()[pivoti][j];
            // Finish swap.
            matrixU->data()[pivoti][j] = tmp;
        }
        tmp = 0.0;

        for (int j=0;j<k;j++)
        {
            // Save entry.
            tmp = matrixL->data()[k][j];
            // Swap / overwrite entry.
            matrixL->data()[k][j] = matrixL->data()[pivoti][j];
            // Finish swap.
            matrixL->data()[pivoti][j] = tmp;
        }
        tmp = 0.0;
        
        for (int j=0;j<m;j++)
        {
            // Save entry.
            tmp = matrixP->data()[k][j];
            // Swap / overwrite entry.
            matrixP->data()[k][j] = matrixP->data()[pivoti][j];
            // Finish swap.
            matrixP->data()[pivoti][j] = tmp;
        }
        // Swap position of b.
        tmp = b->data()[k];
        b->data()[k] = b->data()[pivoti];
        b->data()[pivoti] = tmp;

//		std::cout << "After swap: b = ";
//		for (float entry : b)
//			std::cout << entry << ",";
//		std::cout << "" << std::endl;

//        std::cout << "Matrix U after swap: " << std::endl;
//        printMatrix(matrixU);

        // Subtract line k from line k+1, ..., m
        for (int i = k+1; i<m;i++)
        {
            matrixL->data()[i][k] = matrixU->data()[i][k] / matrixU->data()[k][k];

            //b[i] = b[i] - matrixL[i][k] * b[k];
            for(int column=0; k+column<m; column++)
            {
                matrixU->data()[i][k+column] = matrixU->data()[i][k+column] - matrixL->data()[i][k] * matrixU->data()[k][k+column];
//                std::cout << "i: " <<  i << " k: " << k+column << " entry value old: " << matrixU->data()[i][k+column] << std::endl;
//                std::cout << "i: " <<  i << " k: " << k+column << " entry value new: " << matrixU->data()[i][k+column] - matrixL->data()[i][k] * matrixU->data()[k][k+column] << std::endl;
            }
        }
//        std::cout << "Matrix L after elimination: " << std::endl;
//        printMatrix(matrixL);
    }

    if(talkative)
    {
        std::cout << "Pivoting matrix P: " << std::endl;
        printMatrix(matrixP);
        std::cout << "Pivoting matrix L: " << std::endl;
        printMatrix(matrixL);
        std::cout << "Pivoting matrix U: " << std::endl;
        printMatrix(matrixU);

//        std::cout << "b = ";
//        for (float entry : b->data())
//           std::cout << entry << ",";
//        std::cout << "" << std::endl;
    }

    vector<float> nullvector(m,0.0);
    vector<float> y = calcy(&m,matrixL,b);
//	std::cout << "y = ";
//	for (float entry : y)
//       std::cout << entry << ",";
//	std::cout << "" << std::endl;

    vector<float> x = calcx(&m,matrixU,&y);

    bool solvable = true;
    for (vector<float> row : *matrixU)
    {
        if (row == nullvector)
        {
            std::cout << "This lsoe has no solution." << std::endl;
            solvable = false;
            break;
        }
    }

    if (solvable)
    {
        std::cout << "Solution is x = (";
        for(int i = 0; i<x.size(); i++)
        {
            std::cout<<x[i];
            if(i<x.size()-1)
            {
                std::cout << ",";
            }
        }
        std::cout << ")^T." << std::endl;
    }
}

vector<float> readVectorB()
{
    cout<<"b eingeben: ";
    string line;
    cin >> line;
    vector<float> solution = parseFloats(line);
    return solution;
}

// Helper function for max_element to find highest absolute value.
bool compare(int a , int b){
    return abs(a) < abs(b);
}

int main() {
    // If true read data from console otherweise use examples:
    // example1, example2, example3, example4
    bool talkative = false;
    bool interactive = true;
    string whichExample = "example4";
    int m;
    vector<vector<float>> matrixA;
    vector<float> b;

    if (interactive)
    {
        m = readMatrixDim();
        matrixA = readMatrixA(m);
        b = readVectorB();
    } else {
        if(whichExample == "example1")
        {
            // Instanciate test Matrix.
            vector<float> row1{ 2, 1, 1, 0 };
            vector<float> row2{ 4, 3, 3, 1 };
            vector<float> row3{ 8, 7, 9, 5 };
            vector<float> row4{ 6, 7, 9, 8 };
            // Beware: b is made up. ;-)
            vector<float> solution { 0.5 , 1 , 2, 4 };
            b = solution;
            m = row1.size();
            matrixA.push_back(row1);
            matrixA.push_back(row2);
            matrixA.push_back(row3);
            matrixA.push_back(row4);
        } else if (whichExample == "example2") {
            vector<float> row1{ 1, 2, 1.5 };
            vector<float> row2{ 0.5 ,-0.5, 0 };
            vector<float> row3{ 2, 0 , 1.5 };
            vector<float> solution { 0.5 ,1 , 2 };
            b = solution;
            m = row1.size();
            matrixA.push_back(row1);
            matrixA.push_back(row2);
            matrixA.push_back(row3);
        } else if (whichExample == "example3") {
            vector<float> row1{ 1, 2, 1.5 };
            vector<float> row2{ 0.5, -0.5, 0 };
            vector<float> row3{ 2, 0, 1 };
            vector<float> solution { 0.5, 1, 2 };
            b = solution;
            m = row1.size();
            matrixA.push_back(row1);
            matrixA.push_back(row2);
            matrixA.push_back(row3);
        } else if (whichExample == "example4") {
            vector<float> row1{ 0, 1, 1 };
            vector<float> row2{ 1, 1, 1 };
            vector<float> row3{ 2, 1, 0 };
            vector<float> solution { 1, 2, 3 };
            b = solution;
            m = row1.size();
            matrixA.push_back(row1);
            matrixA.push_back(row2);
            matrixA.push_back(row3);
        }
    }

    if(talkative)
    {
        std::cout << "Matrix A: " << std::endl;
        printMatrix(&matrixA);
    }
    // null vector to test if U is solvable.

    // Algorithmn for Gauss elimination without pivoting.
    vector<vector<float>> matrixU = matrixA;
    vector<vector<float>> matrixL = identityMatrix(m);
    vector<vector<float>> matrixP = identityMatrix(m);

    pivotize(m, &matrixU, &matrixL, &matrixP, &b, talkative);

    return 0;
}

// Ax = b <=> LUx = b, as A = LU
// Ly = b

// No solution for b exists if one line consists only of zeros.
