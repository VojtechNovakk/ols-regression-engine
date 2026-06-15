# Custom Linear Regression Engine in C++
**An Ordinary Least Squares (OLS) solver and custom linear regression implementation in pure C++ with zero external dependencies.**

This project implements a low-level engine for linear regression. Built entirely on top of a custom matrix operations library, it utilizes the modified Gram-Schmidt process and QR decomposition, ensuring high numerical stability of the algorithm.

Originally developed to **predict weekend cinema box office attendance in the Czech Republic** based on historical data, its universal architecture makes it fully adaptable for solving any other linear regression tasks.

## ✨ Features
* **Zero Dependencies:** No Eigen, no external math libraries. Just pure, standard C++.
* **Custom Matrix Library:** A complete implementation of foundational matrix operations (multiplication, transposition, operator overloading).
* **Numerical Stability:** Instead of naive matrix inversions, the computation relies on the modified Gram-Schmidt orthogonalization and QR decomposition.
* **Accuracy Evaluation:** Integrated calculation of model error metrics (RSS / MAE) against the provided dataset.

## 🎬 How It Works with Data
The repository includes a test dataset (`.csv`) containing real-world data from the Czech film market (e.g., weather impact, YouTube trailer views).
The application parses this data and computes the feature weights using the method of least squares. To solve your own regression problem, simply provide your own `.csv` file following the same format.

## 🛠️ Tech Stack
* **Language:** C++ (utilizing standard libraries like `<vector>`, `<fstream>`)
* **Build System:** CMake (includes a ready-to-use `CMakeLists.txt`)

## 🚀 Build & Run
This project uses standard `CMake`. To compile, open your terminal in the project root directory and run the following commands:

```bash
# 1. Create a build directory (to keep the source tree clean)
mkdir build 
cd build 

# 2. Generate build files via CMake
cmake .. 

# 3. Compile the code
make 

# 4. Run the application
./cinema_app 
```
## 🎓 Acknowledgments
The core mathematical logic and algorithms were implemented based on the knowledge acquired during the **Linear algebra (BI-LA1 / LA2) course** at the [Faculty of Information Technology, CTU in Prague](https://fit.cvut.cz/cs).
