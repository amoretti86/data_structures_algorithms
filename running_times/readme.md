# Plotting Directly in C++ with Gnuplot

## Yes! You can plot directly in C++ - it's actually quite elegant!

This guide shows you how to do **everything in C++**: timing, analysis, AND plotting.

## How It Works

C++ calls **gnuplot** (a powerful plotting program) by:
1. Writing data to text files
2. Creating a gnuplot script file
3. Executing gnuplot via `system()` command

## Installation

### On Ubuntu/Debian:
```bash
sudo apt-get install gnuplot
```

### On macOS:
```bash
brew install gnuplot
```

### On Windows:
Download from http://www.gnuplot.info/

## Complete Example: Matrix Multiplication

**File:** `matrix_plot_cpp.cpp`

This single C++ program:
- ✓ Times matrix multiplication
- ✓ Calculates O(n³) theoretical fit
- ✓ Generates beautiful plots
- ✓ All in one executable!

**Compile and run:**
```bash
g++ -O2 -std=c++17 matrix_plot.cpp -o matrix_plot
./matrix_plot
# Creates: matrix_plot.png
```

## Multi-Algorithm Comparison

**File:** `compare_plot_cpp.cpp`

Compares O(n), O(n log n), and O(n²) algorithms with:
- Side-by-side plots
- Automatic analysis output
- Growth rate calculations

**Compile and run:**
```bash
g++ -O2 -std=c++17 compare_plot.cpp -o compare_plot_cpp
./compare_plot
# Creates: algorithm_comparison_plot.png
```

## The C++ Plotting Pattern

### Step 1: Write Data to File
```cpp
ofstream datafile("data.txt");
for (size_t i = 0; i < sizes.size(); i++) {
    datafile << sizes[i] << " " << times[i] << "\n";
}
datafile.close();
```

### Step 2: Create Gnuplot Script
```cpp
ofstream script("plot.gnu");
script << "set terminal png size 1200,600\n";
script << "set output 'plot.png'\n";
script << "set title 'My Plot'\n";
script << "set xlabel 'Input Size'\n";
script << "set ylabel 'Time (ms)'\n";
script << "plot 'data.txt' using 1:2 with linespoints\n";
script.close();
```

### Step 3: Execute Gnuplot
```cpp
int result = system("gnuplot plot.gnu");
if (result == 0) {
    cout << "Plot saved to: plot.png" << endl;
}
```

## Gnuplot Script Cheatsheet

### Basic Settings
```gnuplot
set terminal png size 1200,600        # Output format and size
set output 'filename.png'             # Output file
set title 'Title Text'                # Plot title
set xlabel 'X Axis Label'             # X axis label
set ylabel 'Y Axis Label'             # Y axis label
set grid                              # Show grid lines
set key left top                      # Legend position
```

### Plotting Styles
```gnuplot
# Line plot
plot 'data.txt' using 1:2 with lines

# Points only
plot 'data.txt' using 1:2 with points

# Lines and points
plot 'data.txt' using 1:2 with linespoints

# Customization
plot 'data.txt' using 1:2 with linespoints lw 2 pt 7 ps 1.5 lc rgb '#16A085'
#    lw = line width, pt = point type, ps = point size, lc = line color
```

### Multiple Plots
```gnuplot
plot 'data1.txt' using 1:2 with linespoints title 'Series 1', \
     'data2.txt' using 1:2 with linespoints title 'Series 2'
```

### Subplots (Multiplot)
```gnuplot
set multiplot layout 2,2    # 2x2 grid of plots
# First plot
set title 'Plot 1'
plot 'data1.txt'
# Second plot
set title 'Plot 2'
plot 'data2.txt'
# ... etc
unset multiplot
```

## Advantages of C++ Plotting

### ✓ Self-Contained
Everything in one C++ program - no Python dependency!

### ✓ Great for Teaching
Students see the complete workflow:
1. Write algorithm
2. Time it
3. Analyze results
4. Visualize

### ✓ Publication Quality
Gnuplot produces professional-grade plots

### ✓ Portable
Works on Linux, macOS, Windows

### ✓ Scriptable
Easy to automate for batch experiments

## Classroom Usage

### For Lectures
1. **Live demonstration:**
   - Compile program in front of class
   - Run and generate plot
   - Open plot.png to show results
   
2. **Interactive exploration:**
   - Modify sizes array
   - Recompile and see new results
   - Students see immediate feedback

### For Assignments
Students can:
- Write their own algorithms
- Add timing code
- Generate plots automatically
- Submit both code and plots

## Common Gnuplot Customizations

### Colors (RGB hex codes)
```gnuplot
lc rgb '#16A085'  # Teal
lc rgb '#FF6B9D'  # Pink
lc rgb '#2ECC71'  # Green
lc rgb '#3498DB'  # Blue
lc rgb '#F39C12'  # Orange
```

### Point Types
```gnuplot
pt 1   # Plus sign (+)
pt 2   # Cross (×)
pt 5   # Square
pt 7   # Circle (filled)
pt 9   # Triangle
pt 11  # Diamond
```

### Line Types
```gnuplot
dt 1   # Solid line
dt 2   # Dashed line
dt 3   # Dotted line
```

### Log Scale
```gnuplot
set logscale y     # Log scale on Y axis
set logscale xy    # Log scale on both axes
```

## Advanced: Fitting Curves

Gnuplot can fit theoretical curves to data:

```gnuplot
# Define function
f(x) = c * x**3

# Fit to data
fit f(x) 'data.txt' using 1:2 via c

# Plot both
plot 'data.txt' using 1:2 with points title 'Measured', \
     f(x) with lines title sprintf('O(n³) fit: %.2e·n³', c)
```

## Comparison: C++ vs Python Plotting

| Aspect | C++ + Gnuplot | Python + Matplotlib |
|--------|---------------|---------------------|
| **Setup** | Install gnuplot | Install Python + matplotlib |
| **Speed** | C++ timing is faster | Python timing has overhead |
| **Dependencies** | Just gnuplot | Python + numpy + pandas + matplotlib |
| **Learning Curve** | Learn gnuplot syntax | Learn matplotlib API |
| **Interactivity** | Static plots | Can be interactive |
| **Publication Quality** | Excellent | Excellent |
| **For Teaching C++** | ✓ Everything in C++! | × Need Python too |

## Best Practices

### 1. Error Handling
```cpp
int result = system("gnuplot plot.gnu");
if (result != 0) {
    cerr << "Error: gnuplot failed. Is it installed?" << endl;
    cerr << "Install with: apt-get install gnuplot" << endl;
    return 1;
}
```

### 2. Data Validation
```cpp
// Check for valid measurements
if (duration.count() == 0 && n > small_threshold) {
    cout << "Warning: timing too fast for size " << n << endl;
}
```

### 3. Clean Output
```cpp
// Write data with clear headers
datafile << "# Size Time(ms)" << endl;
for (...) {
    datafile << size << " " << time << endl;
}
```

## Troubleshooting

**Problem:** "gnuplot: command not found"
**Solution:** Install gnuplot (see Installation section above)

**Problem:** Plot looks wrong
**Solution:** Check your data file has correct format (space-separated values)

**Problem:** Times are all 0
**Solution:** Increase input sizes or repeat operations more times

**Problem:** Can't see the plot
**Solution:** Make sure to view the .png file with an image viewer

## Conclusion

Plotting in C++ is:
- ✓ **Easy** - Just write data files and gnuplot script
- ✓ **Powerful** - Professional-quality plots
- ✓ **Self-contained** - One C++ program does everything
- ✓ **Great for teaching** - Students see complete workflow

Perfect for teaching asymptotic notation where you want students to see the entire process from algorithm → timing → visualization in pure C++!
