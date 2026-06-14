#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <numbers>
#include "../include/Matrix.hpp"
#include "../include/Regression.hpp"

struct Dataset {
    Matrix X;
    Matrix Y;
};

double getSeasonality(int week) {
    return std::cos(2.0*std::numbers::pi * week / 52.0);
}

inline Dataset loadData(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open())
        throw std::runtime_error("Cannot open CSV!");

    std::string line;
    std::getline(file, line);
    size_t x_columns = std::count(line.begin(), line.end(), ';');
    std::vector<std::vector<double>> X;
    std::vector<double> Y;

    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        std::stringstream ss(line);
        std::string cell;
        std::vector<double> current_x;

        current_x.push_back(1.0);

        for (size_t i = 0; i < x_columns; ++i) {
            std::getline(ss, cell, ';');
            current_x.push_back(std::stod(cell));
        }

        std::getline(ss, cell, ';');
        Y.push_back(std::stod(cell));
        X.push_back(current_x);
    }
    size_t num_records = X.size();
    Dataset ds(Matrix(num_records, X[0].size()), Matrix(num_records, 1));
    for (size_t r = 0; r < num_records; ++r) {
        ds.Y(r, 0) = Y[r];
        for (size_t c = 0; c < X[0].size(); ++c) {
            ds.X(r,c) = X[r][c];
        }
    }
    return ds;
}

int main() {
    try {
        Dataset data = loadData("data/movies1.csv");
        std::cout << "Successfully loaded " << data.X.rows() << " movies from the database.\n\n";

        Matrix weights = trainModel(data.X, data.Y);
        // YT Views  Weather (1-5)  Sequel (1/0)  Week of year  Attendance
        double sum = 0;
        Matrix x_T = data.X.transpose();
        for (size_t i = 0; i < data.Y.rows(); ++i) {
            double miss = data.Y(i, 0) - weights.dotColumns(0, x_T, i);
            sum += miss*miss;
        }

        double rmse = sqrt(sum / data.Y.rows());
        std::cout << "RMSE (Average Mismatch): " << rmse << "\n";

        Matrix new_movie(data.X.cols(), 1);
        new_movie(0, 0) = 1.0;
        new_movie(1, 0) = 259000.0;
        new_movie(2, 0) = 4.0;
        new_movie(3, 0) = getSeasonality(16.0);
        new_movie(4, 0) = 1.0;


        double out = new_movie.dotColumns(0, weights, 0);
        std::cout << "Estimated attendance at Czech movie theaters for the first weekend: " << out << " people!" << "\n";
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << '\n';
    }
    return 0;
}