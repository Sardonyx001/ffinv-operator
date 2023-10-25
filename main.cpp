#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

double f(double x) {
    return std::exp(std::sqrt(std::abs(x)));
}

double g(double x, double bias) {
    return x+bias;
}

double f_inv(double x) {
    return std::pow(std::log(std::abs(x)),2);
}

double h(double x, double bias) {
    return f_inv(g(f(x), bias));
}

int main() {
    int N = 1000;
    int steps = 100000;
    std::vector<double> seeds;
    std::vector<double> results;
    std::vector<double> biases;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-100.0, 100.0);

    for (int i = 0; i < steps; ++i) {
        double bias = dist(gen);
        biases.push_back(bias);
        double seed = dist(gen);
        seeds.push_back(seed);
        double next_val = h(seed, bias);
        std::vector<double> result = {seed, next_val};

        for (int j = 0; j < N - 2; ++j) {
            next_val = h(next_val, bias);
            result.push_back(next_val);
        }

        results.push_back(result.back());
        std::cout << "Seed: " << std::round(seed * 100) / 100 << " | Final: " << std::round(result.back() * 100000) / 100000 << std::endl;
    }

    // Sort the values by seed in ascending order
    std::vector<std::pair<double, double>> sortedValues;
    for (size_t i = 0; i < seeds.size(); ++i) {
        sortedValues.push_back(std::make_pair(seeds[i], results[i]));
    }
    std::sort(sortedValues.begin(), sortedValues.end());

    std::ofstream file;
    // file.open(std::to_string(rand() % 90000 + 10000) + ".csv");
    file.open("data.csv");
    if (file.is_open()) {
        file << "x,y\n";
        for (const auto& pair : sortedValues) {
            file << pair.first << "," << pair.second << "\n";
        }
        file.close();
    } else {
        std::cerr << "Failed to create file." << std::endl;
        return 1;
    }

    return 0;
}
