#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

// Naive matrix multiplication O(n^3)
vector<vector<double>> multiplyMatrices(const vector<vector<double>>& A, 
                                         const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> C(n, vector<double>(n, 0.0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Generate random matrix
vector<vector<double>> generateMatrix(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    
    vector<vector<double>> matrix(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

int main() {
    vector<int> sizes = {10, 20, 50, 100, 150, 200, 250, 300, 350, 400};
    vector<int> measured_sizes;
    vector<long long> measured_times;
    
    cout << "Running timing experiments..." << endl;
    cout << "Size\tTime (ms)" << endl;
    cout << "----\t---------" << endl;
    
    for (int n : sizes) {
        auto A = generateMatrix(n);
        auto B = generateMatrix(n);
        
        auto start = high_resolution_clock::now();
        auto C = multiplyMatrices(A, B);
        auto end = high_resolution_clock::now();
        
        auto duration = duration_cast<milliseconds>(end - start);
        
        cout << n << "\t" << duration.count() << endl;
        
        measured_sizes.push_back(n);
        measured_times.push_back(duration.count());
    }
    
    // Write data to file for gnuplot
    ofstream datafile("matrix_data.txt");
    for (size_t i = 0; i < measured_sizes.size(); i++) {
        datafile << measured_sizes[i] << " " << measured_times[i] << "\n";
    }
    datafile.close();
    
    // Calculate O(n^3) fit
    double sum_ratio = 0.0;
    int count = 0;
    for (size_t i = 0; i < measured_sizes.size(); i++) {
        if (measured_times[i] > 0) {
            double n = measured_sizes[i];
            sum_ratio += measured_times[i] / (n * n * n);
            count++;
        }
    }
    double c = (count > 0) ? sum_ratio / count : 1e-6;
    
    // Write theoretical curve
    ofstream theoryfile("theory_data.txt");
    for (int n = measured_sizes.front(); n <= measured_sizes.back(); n += 5) {
        double theory_time = c * n * n * n;
        theoryfile << n << " " << theory_time << "\n";
    }
    theoryfile.close();
    
    // Create gnuplot script
    ofstream gnuplotScript("plot_matrix.gnu");
    gnuplotScript << "set terminal png size 1200,600 enhanced font 'Arial,12'\n";
    gnuplotScript << "set output 'matrix_plot.png'\n";
    gnuplotScript << "set multiplot layout 1,2\n";
    gnuplotScript << "\n";
    
    // First plot - measured data
    gnuplotScript << "set title 'Matrix Multiplication: Running Time vs Input Size' font 'Arial,14'\n";
    gnuplotScript << "set xlabel 'Matrix Size (n)' font 'Arial,12'\n";
    gnuplotScript << "set ylabel 'Time (milliseconds)' font 'Arial,12'\n";
    gnuplotScript << "set grid\n";
    gnuplotScript << "set key left top\n";
    gnuplotScript << "plot 'matrix_data.txt' using 1:2 with linespoints lw 2 pt 7 ps 1.5 lc rgb '#16A085' title 'Measured Time'\n";
    gnuplotScript << "\n";
    
    // Second plot - with theoretical fit
    gnuplotScript << "set title 'Measured vs Theoretical O(n^3)' font 'Arial,14'\n";
    gnuplotScript << "set xlabel 'Matrix Size (n)' font 'Arial,12'\n";
    gnuplotScript << "set ylabel 'Time (milliseconds)' font 'Arial,12'\n";
    gnuplotScript << "set grid\n";
    gnuplotScript << "set key left top\n";
    gnuplotScript << "plot 'matrix_data.txt' using 1:2 with points pt 7 ps 1.5 lc rgb '#16A085' title 'Measured Time', \\\n";
    gnuplotScript << "     'theory_data.txt' using 1:2 with lines lw 2 dt 2 lc rgb '#FF6B9D' title 'O(n^3) fit: " << scientific << c << " * n^3'\n";
    gnuplotScript << "\n";
    gnuplotScript << "unset multiplot\n";
    gnuplotScript.close();
    
    // Execute gnuplot
    cout << "\nGenerating plot..." << endl;
    int result = system("gnuplot plot_matrix.gnu");
    
    if (result == 0) {
        cout << "Plot saved to: matrix_plot.png" << endl;
        cout << "\nTo view the plot:" << endl;
        cout << "  - Open matrix_plot.png with an image viewer" << endl;
        cout << "  - Or: display matrix_plot.png (on Linux with ImageMagick)" << endl;
    } else {
        cout << "Error: gnuplot not found or failed to execute" << endl;
        cout << "You can still plot manually using matrix_data.txt" << endl;
    }
    
    return 0;
}