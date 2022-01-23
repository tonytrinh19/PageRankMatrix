#include "PageRank.hpp"
#include <exception>
#include <iostream>
#include <vector>

#define FOLLOW_PROBABILITY 0.85
#define NOT_FOLLOW_PROBABILITY 0.15
#define RANK_MATRIX_DEFAULT_VALUE 1.0
#define NUMBER_OF_COLUMN_FOR_DEFAULT_RANK_MATRIX 1

using namespace std;

/**
 * The core of the program, runs all the required calculations to finally print out the result of the page rank.
 */
void runPageRank() {
    try {
        string path("../connectivity.txt");
        ifstream input_file(path);
        if (!input_file.is_open()) {
            throw exception();
        }

        vector<double> values_vector = getConnectivityValuesAsVector(input_file);

        Matrix importance_matrix           = generateImportanceMatrix(values_vector.data(), (int) values_vector.size());
        Matrix probability_teleport_matrix = generateProbabilityTeleportMatrix(importance_matrix.getNumOfColumns());
        Matrix transition_matrix           = generateTransitionMatrix(importance_matrix, probability_teleport_matrix);
        Matrix final_matrix                = doMarkovProcessToGetFinalMatrix(transition_matrix);
        printResult(final_matrix);
        input_file.close();
    }
    catch (exception &e) {
        e.what();
    }
}

/**
 * Reads connectivity.txt file and retrieves the data in the file
 * and put the data in a double vector.
 * @param input_file path of the input file
 * @return double vector that contains all the values in order
 */
vector<double> getConnectivityValuesAsVector(ifstream &input_file) {
    int value{0};
    vector<double> connectivity_vector;
    while (input_file >> value) {
        connectivity_vector.push_back(value);
    }
    return connectivity_vector;
}

Matrix generateImportanceMatrix(double *values, int size) {
    Matrix matrix(values, size);
    double sum_of_column{0.0};
    vector<double> sum_of_columns_vector;

    for (int c = 0; c < matrix.getNumOfColumns(); c++) {
        for (int r = 0; r < matrix.getNumOfRows(); r++) {
            sum_of_column += matrix.getMatrix().at(r).at(c);
        }
        sum_of_columns_vector.push_back(sum_of_column);
        sum_of_column = 0.0;
    }


    for (int c = 0; c < matrix.getNumOfColumns(); c++) {
        for (int r = 0; r < matrix.getNumOfRows(); r++) {
            if (sum_of_columns_vector.at(c) == 0) {
                matrix.setValue(r, c, 1 / (double) matrix.getNumOfColumns());
            } else {
                matrix.setValue(r, c, (matrix.getValue(r, c) / sum_of_columns_vector.at(c)));
            }
        }
    }
    return matrix;
}

/**
 * Creates a probability teleport matrix from a given input size.
 * @param size the size of the matrix
 * @return probability teleport matrix
 */
Matrix generateProbabilityTeleportMatrix(int size) {
    Matrix matrix(size);
    for (int r = 0; r < matrix.getNumOfRows(); r++) {
        for (int c = 0; c < matrix.getNumOfColumns(); c++) {
            matrix.setValue(r, c, 1 / (double) matrix.getNumOfColumns());
        }
    }
    return matrix;
}

/**
 * Creates a transition matrix.
 * @param importance_matrix the importance matrix
 * @param prob_tele_matrix  the probability matrix
 * @return transition matrix
 */
Matrix generateTransitionMatrix(Matrix importance_matrix, Matrix prob_tele_matrix) {
    for (int r = 0; r < importance_matrix.getNumOfRows(); r++) {
        for (int c = 0; c < importance_matrix.getNumOfColumns(); c++) {
            importance_matrix.setValue(r, c, FOLLOW_PROBABILITY * importance_matrix.getValue(r, c));
        }
    }

    for (int r = 0; r < prob_tele_matrix.getNumOfRows(); r++) {
        for (int c = 0; c < prob_tele_matrix.getNumOfColumns(); c++) {
            prob_tele_matrix.setValue(r, c, NOT_FOLLOW_PROBABILITY * prob_tele_matrix.getValue(r, c));
        }
    }

    importance_matrix += prob_tele_matrix;

    // importance_matrix is now transition matrix;
    return importance_matrix;
}

/**
 * Perform Markov process to calculate the final matrix
 * @param transition_matrix transition matrix
 * @return final matrix that contains the page ranks
 */
Matrix doMarkovProcessToGetFinalMatrix(Matrix transition_matrix) {
    // Create a rank matrix.
    Matrix rank_matrix(transition_matrix.getNumOfColumns(), NUMBER_OF_COLUMN_FOR_DEFAULT_RANK_MATRIX);
    for (int r = 0; r < rank_matrix.getNumOfRows(); r++) {
        rank_matrix.setValue(r, 0, RANK_MATRIX_DEFAULT_VALUE);
    }

    Matrix final_rank_matrix = rankMatrixStopChanging(transition_matrix, rank_matrix);
    return final_rank_matrix;
}

/**
 * Checks whether the new rank is the same as the old rank and once the new rank equals to the rank,
 * returns the matrix.
 * @param transition_matrix transition matrix
 * @param rank_matrix rank matrix
 * @return final matrix that contains the page ranks
 */
Matrix rankMatrixStopChanging(Matrix transition_matrix, Matrix rank_matrix) {
    Matrix temp(rank_matrix.getNumOfRows(), NUMBER_OF_COLUMN_FOR_DEFAULT_RANK_MATRIX);

    Matrix new_rank_matrix = newRankMatrix(transition_matrix, rank_matrix);
    while (new_rank_matrix != rank_matrix) {
        rank_matrix = new_rank_matrix;
        Matrix temp = newRankMatrix(transition_matrix, rank_matrix);
        new_rank_matrix = temp;
    }
    return rank_matrix;
}

/**
 * Serves as a helper function to function rankMatrixStopChanging, does matrix multiplications.
 * @param transition_matrix transition matrix
 * @param rank_matrix rank matrix
 * @return final matrix that contains the page ranks
 */
Matrix newRankMatrix(Matrix transition_matrix, Matrix rank_matrix) {
    transition_matrix *= rank_matrix;
    return transition_matrix;
}

/**
 * Prints out the page rank from the given input.
 * @param final_matrix final page rank matrix
 */
void printResult(Matrix final_matrix) {
    double sum{0.0};
    char page = 'A';
    for (int r = 0; r < final_matrix.getNumOfRows(); r++) {
        sum += final_matrix.getValue(r, 0);
    }

    for (int r; r < final_matrix.getNumOfRows(); r++) {
        final_matrix.setValue(r, 0, final_matrix.getValue(r, 0) / sum);
        cout << "Page " << page++ << ": " << final_matrix.getValue(r, 0) * 100 << "%" << endl;
    }
}
