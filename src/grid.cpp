#include "grid.h"
#include "colors.h"
#include <iostream>

extern const int CELL_OFFSET_VALUE;

Grid::Grid() {
  numRows = 20;
  numCols = 10;
  cellSize = 30;
  Initialize();
  colors = GetCellColors();
}

void Grid::Initialize() {
  for (int row = 0; row < numRows; row++) {
    for (int column = 0; column < numCols; column++) {
      grid[row][column] = 0;
    }
  }
}

void Grid::Print() {
  for (int row = 0; row < numRows; row++) {
    for (int column = 0; column < numCols; column++) {
      std::cout << grid[row][column] << " ";
    }
    std::cout << std::endl;
  }
}

void Grid::Draw() {
  for (int row = 0; row < numRows; row++) {
    for (int column = 0; column < numCols; column++) {
      int cellValue = grid[row][column];
      DrawRectangle(column * cellSize + CELL_OFFSET_VALUE,
                    row * cellSize + CELL_OFFSET_VALUE, cellSize - 1,
                    cellSize - 1, colors[cellValue]);
    }
  }
}

bool Grid::IsCellOutside(int row, int column) {
  if (row >= 0 && row < numRows && column >= 0 && column < numCols) {
    return false;
  }
  return true;
}

bool Grid::IsCellEmpty(int row, int column) {
  if (grid[row][column] == 0) {
    return true;
  }
  return false;
}

bool Grid::isRowFull(int row) {
  for (int column = 0; column < numCols; column++) {
    if (grid[row][column] == 0) {
      return false;
    }
  }
  return true;
}

void Grid::ClearRow(int row) {
  for (int column = 0; column < numCols; column++) {
    grid[row][column] = 0;
  }
}

void Grid::MoveRowDown(int row, int numRows) {
  for (int column = 0; column < numCols; column++) {
    grid[row + numRows][column] = grid[row][column];
    grid[row][column] = 0;
  }
}

int Grid::ClearFullRows() {
  int completed = 0;
  for (int row = numRows - 1; row >= 0; row--) {
    if (isRowFull(row)) {
      ClearRow(row);
      completed++;
    } else if (completed > 0) {
      MoveRowDown(row, completed);
    }
  }
  return completed;
}