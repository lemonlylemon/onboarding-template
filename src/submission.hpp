  #pragma once

  #include <cstddef>
  #include <vector>

  // Starter Grid for the 2D heat-diffusion problem.
  //
  // The evaluation harness uses operator() to set initial conditions and to read
  // results; it never touches your internal storage. Keep this interface,
  // everything else is yours.
  class Grid {
  private:
    std::size_t rows_;
    std::size_t cols_;
    std::vector<std::vector<double>> grid_; //store temperature value

  public:
    Grid(std::size_t rows, std::size_t cols) :
    rows_(rows), cols_(cols), grid_(rows, std::vector<double>(cols,0.0)) {}

    std::size_t rows() const {
      return rows_;
    }

    std::size_t cols() const {
      return cols_;
    }

    double& operator()(std::size_t i, std::size_t j) {
      return grid_[i][j];
    }

    double operator()(std::size_t i, std::size_t j) const {
      return grid_[i][j];
    }

  };

  // Apply the five-point stencil over all interior points, copying the boundary
  // values unchanged from old_grid to new_grid. Implement your solution here.
  void apply_stencil(const Grid& old_grid, Grid& new_grid) {


    std::size_t numberOfRows = old_grid.rows();
    std::size_t numberOfCols = old_grid.cols();

    for (std::size_t x = 0; x < numberOfRows; ++x) {
      for (std::size_t y = 0; y < numberOfCols; ++y) {
        new_grid(x,y) = old_grid(x,y); ///map old grid to the new one
      }
    }

    for (std::size_t x = 1; x < numberOfRows - 1; ++x) {
      for (std::size_t y = 1; y < numberOfCols - 1; ++y) {
        new_grid(x,y) = 0.5 * old_grid(x,y) +
                0.125 * (old_grid(x-1,y) + old_grid(x+1,y) +
                         old_grid(x,y-1) + old_grid(x,y+1));
      }
    }
  }
