#ifndef LAB1TEMPLATE_PAGERANK_HPP
#define LAB1TEMPLATE_PAGERANK_HPP

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <fstream>
#include "matrix.hpp"

void runPageRank();

std::vector<double> getConnectivityValuesAsVector(std::ifstream &);

Matrix generateImportanceMatrix(double *, int);

Matrix generateProbabilityTeleportMatrix(int);

Matrix generateTransitionMatrix(Matrix, Matrix);

Matrix doMarkovProcessToGetFinalMatrix(Matrix);

Matrix rankMatrixStopChanging(Matrix, Matrix);

Matrix newRankMatrix(Matrix, Matrix);

void printResult(Matrix);

#endif //LAB1TEMPLATE_PAGERANK_HPP
