#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

// O(n) - Linear search
bool linearSearch(const vector<int>& arr, int target) {
    for (int x : arr) {
        if (x == target) return true;
    }
    return false;
}

// O(n log n) - Sorting
void sortArray(vector<int>& arr) {
    sort(arr.begin(), arr.end());
}

// O(n^2) - Bubble sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Generate random array
vector<int> generateArray(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Time a function and return milliseconds
template<typename Func>
long long timeFunction(Func f) {
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

int main() {
    // Two ranges: small for bubble sort, large for the fast algorithms
    vector<int> small_sizes = {1000, 2000, 3000, 5000, 7000, 10000, 15000};
    vector<int> large_sizes = {10000, 20000, 30000, 50000, 70000, 100000, 150000};
    
    // Combine and deduplicate
    vector<int> all_sizes = small_sizes;
    for (int n : large_sizes) {
        if (find(all_sizes.begin(), all_sizes.end(), n) == all_sizes.end()) {
            all_sizes.push_back(n);
        }
    }
    sort(all_sizes.begin(), all_sizes.end());
    
    // Store results
    vector<int> measured_sizes;
    vector<long long> linear_times;
    vector<long long> sort_times;
    vector<long long> bubble_times;
    
    cout << "Running algorithm comparisons..." << endl;
    cout << "Size\tLinear\tSort\tBubble" << endl;
    cout << "----\t------\t----\t------" << endl;
    
    for (int n : all_sizes) {
        auto arr = generateArray(n);
        
        // Linear Search - O(n) - do 1000 searches to make it visible
        long long time_linear = timeFunction([&]() {
            for (int i = 0; i < 1000; i++) {
                linearSearch(arr, -1);
            }
        });
        
        // Sort - O(n log n)
        long long time_sort = timeFunction([&]() {
            auto temp = arr;
            sortArray(temp);
        });
        
        // Bubble Sort - O(n^2) - only for smaller sizes
        long long time_bubble = 0;
        if (n <= 15000) {
            time_bubble = timeFunction([&]() {
                auto temp = arr;
                bubbleSort(temp);
            });
        }
        
        cout << n << "\t" << time_linear << "\t" << time_sort << "\t" << time_bubble << endl;
        
        measured_sizes.push_back(n);
        linear_times.push_back(time_linear);
        sort_times.push_back(time_sort);
        bubble_times.push_back(time_bubble);
    }
    
    // Write data files for gnuplot
    ofstream datafile("algorithm_data.txt");
    for (size_t i = 0; i < measured_sizes.size(); i++) {
        datafile << measured_sizes[i] << " " 
                << linear_times[i] << " " 
                << sort_times[i] << " " 
                << bubble_times[i] << "\n";
    }
    datafile.close();
    
    // Create gnuplot script with better handling
    ofstream gnuplotScript("plot_algorithms.gnu");
    gnuplotScript << "set terminal png size 1600,900 enhanced font 'Arial,12'\n";
    gnuplotScript << "set output 'algorithm_comparison_plot.png'\n";
    gnuplotScript << "set multiplot layout 2,2\n";
    gnuplotScript << "\n";
    
    // Main comparison plot - all three algorithms
    gnuplotScript << "set title 'Algorithm Comparison: Growth Rates Matter!' font 'Arial,14'\n";
    gnuplotScript << "set xlabel 'Input Size (n)' font 'Arial,12'\n";
    gnuplotScript << "set ylabel 'Time (milliseconds)' font 'Arial,12'\n";
    gnuplotScript << "set grid\n";
    gnuplotScript << "set key left top\n";
    gnuplotScript << "plot 'algorithm_data.txt' using 1:2 with linespoints lw 2 pt 7 ps 1 lc rgb '#2ECC71' title 'Linear Search O(n)', \\\n";
    gnuplotScript << "     'algorithm_data.txt' using 1:3 with linespoints lw 2 pt 9 ps 1 lc rgb '#3498DB' title 'Sort O(n log n)', \\\n";
    gnuplotScript << "     'algorithm_data.txt' using 1:($4 > 0 ? $4 : 1/0) with linespoints lw 2 pt 11 ps 1 lc rgb '#F39C12' title 'Bubble Sort O(n^2)'\n";
    gnuplotScript << "\n";
    
    // Linear vs Sort comparison (skip bubble for clarity)
    gnuplotScript << "set title 'Fast Algorithms: O(n) vs O(n log n)' font 'Arial,13'\n";
    gnuplotScript << "set xlabel 'Input Size (n)' font 'Arial,11'\n";
    gnuplotScript << "set ylabel 'Time (ms)' font 'Arial,11'\n";
    gnuplotScript << "set grid\n";
    gnuplotScript << "set key left top\n";
    gnuplotScript << "plot 'algorithm_data.txt' using 1:2 with linespoints lw 2 pt 7 ps 1.2 lc rgb '#2ECC71' title 'Linear Search O(n)', \\\n";
    gnuplotScript << "     'algorithm_data.txt' using 1:3 with linespoints lw 2 pt 9 ps 1.2 lc rgb '#3498DB' title 'Sort O(n log n)'\n";
    gnuplotScript << "\n";
    
    // Bubble Sort detail (only where it has data)
    gnuplotScript << "set title 'Bubble Sort: O(n^2) - Why It Gets Slow' font 'Arial,13'\n";
    gnuplotScript << "set xlabel 'Input Size (n)' font 'Arial,11'\n";
    gnuplotScript << "set ylabel 'Time (ms)' font 'Arial,11'\n";
    gnuplotScript << "set grid\n";
    gnuplotScript << "unset key\n";
    gnuplotScript << "plot 'algorithm_data.txt' using 1:($4 > 0 ? $4 : 1/0) with linespoints lw 2 pt 11 ps 1.2 lc rgb '#F39C12'\n";
    gnuplotScript << "\n";
    
    // Log-log plot to show growth rates
    gnuplotScript << "set title 'Log-Log Plot: Identifying Complexity' font 'Arial,13'\n";
    gnuplotScript << "set xlabel 'log(Input Size)' font 'Arial,11'\n";
    gnuplotScript << "set ylabel 'log(Time)' font 'Arial,11'\n";
    gnuplotScript << "set logscale xy\n";
    gnuplotScript << "set grid\n";
    gnuplotScript << "set key left top\n";
    gnuplotScript << "plot 'algorithm_data.txt' using 1:($2 > 0 ? $2 : 1/0) with linespoints lw 2 pt 7 ps 1 lc rgb '#2ECC71' title 'Linear O(n)', \\\n";
    gnuplotScript << "     'algorithm_data.txt' using 1:($3 > 0 ? $3 : 1/0) with linespoints lw 2 pt 9 ps 1 lc rgb '#3498DB' title 'Sort O(n log n)', \\\n";
    gnuplotScript << "     'algorithm_data.txt' using 1:($4 > 0 ? $4 : 1/0) with linespoints lw 2 pt 11 ps 1 lc rgb '#F39C12' title 'Bubble O(n^2)'\n";
    gnuplotScript << "\n";
    gnuplotScript << "unset multiplot\n";
    gnuplotScript.close();
    
    // Execute gnuplot
    cout << "\nGenerating plot..." << endl;
    int result = system("gnuplot plot_algorithms.gnu");
    
    if (result == 0) {
        cout << "Plot saved to: algorithm_comparison_plot.png" << endl;
        
        // Print analysis
        cout << "\n" << string(60, '=') << endl;
        cout << "ANALYSIS: Why Asymptotic Notation Matters" << endl;
        cout << string(60, '=') << endl;
        
        // Find some good comparison points
        cout << "\n1. BUBBLE SORT (O(n²)) - Gets Slow Fast:" << endl;
        cout << string(60, '-') << endl;
        for (size_t i = 1; i < measured_sizes.size() && measured_sizes[i] <= 15000; i++) {
            if (bubble_times[i-1] > 0 && bubble_times[i] > 0) {
                int n1 = measured_sizes[i-1];
                int n2 = measured_sizes[i];
                double ratio = static_cast<double>(n2) / n1;
                double time_ratio = static_cast<double>(bubble_times[i]) / bubble_times[i-1];
                
                cout << "n: " << n1 << " -> " << n2 << " (" << ratio << "x)" << endl;
                cout << "  Time: " << bubble_times[i-1] << "ms -> " << bubble_times[i] 
                     << "ms (" << time_ratio << "x slower)" << endl;
                cout << "  Expected O(n²): " << (ratio * ratio) << "x" << endl;
                cout << endl;
            }
        }
        
        // Compare final performance
        cout << "\n2. FINAL COMPARISON at n=100,000:" << endl;
        cout << string(60, '-') << endl;
        size_t last = measured_sizes.size() - 1;
        cout << "Linear Search O(n):     " << linear_times[last] << " ms" << endl;
        cout << "Sort O(n log n):        " << sort_times[last] << " ms" << endl;
        cout << "Bubble Sort O(n²):      Would take ~" << (bubble_times[6] * 100) << " ms (extrapolated!)" << endl;
        cout << "\nNotice: Even though all start near 0ms, they diverge dramatically!" << endl;
        
    } else {
        cout << "Error generating plot" << endl;
    }
    
    return 0;
}