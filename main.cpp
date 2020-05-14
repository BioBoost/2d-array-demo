#include <iostream>

using namespace std;

// NOT OK !!!!!!!
int * create_1d_array_on_stack(void) {
  // This array is created on the stack.
  // Its scope is local to this function.
  int array[2] = { 0, 0 };

  // We can do this but we are actually creating bug here
  // Compiler warns us:
  // warning: address of local variable 'array' returned [-Wreturn-local-addr]
  return array;

    // Syntax to return 2d array from function is a lot more
    // complex. Thats why i choose to return 1d array
}

int ** create_2d_array_on_heap(unsigned int rows, unsigned int cols) {
  // This array is created on the heap and exists as long as it
  // is not deleted or the application terminated.
  int ** array = new int*[rows];
  for (unsigned int r = 0; r < rows; r++) {
    array[r] = new int[cols];

    for (unsigned int c = 0; c < cols; c++) {
      array[r][c] = r * cols + c;
    }
  }

  return array;
}

// Passing 2D array to function/method
void print_array(int ** someArray, unsigned int rows, unsigned int cols) {
  for (unsigned int r = 0; r < rows; r++) {
    for (unsigned int c = 0; c < cols; c++) {
      cout << someArray[r][c] << " | ";
    }
    cout << endl;
  }
}

// BEST SOLUTION OF ALL. WRAP IT ALL UP IN A NICE CLASS

class Matrix {

  public:
    Matrix(unsigned int rows, unsigned int cols) {
      this->cols = cols;
      this->rows = rows;
      create_array_on_heap();
    }

    // Don't forget the destructor !!!!
    ~Matrix(void) {
      for (unsigned int i = 0; i < rows; i++) {
        delete[] array[i];
      }
      delete[] array;
    }

    // It's even better not to return the array to access
    // the elements but rather abstract them with some methods
    int get(unsigned int row, unsigned int col) {
      return array[row][col];
    }

    void set(int value, unsigned int row, unsigned int col) {
      array[row][col] = value;
    }

    unsigned int row_count(void) {
      return rows;
    }

    unsigned int col_count(void) {
      return cols;
    }

  private:
    void create_array_on_heap(void) {
      array = new int*[rows];
      for (unsigned int r = 0; r < rows; r++) {
        array[r] = new int[cols];

        for (unsigned int c = 0; c < cols; c++) {
          array[r][c] = r * cols + c;
        }
      }
    }
    
  private:
    int ** array = nullptr;
    unsigned int rows = 0;
    unsigned int cols = 0;
};

int main() {
  const unsigned int ROWS = 2;
  const unsigned int COLS = 3;

  // This is undefined behaviour
  // int * test = create_1d_array_on_stack();
  // cout << "Test: " << test[0] << endl;

  // SOLUTION: Create 2d array on the heap and store
  // it in pointer
  int ** array = create_2d_array_on_heap(ROWS, COLS);

  // How to pass this to a function/method
  print_array(array, ROWS, COLS);

  // Need to free the heap allocated array
  for (unsigned int i = 0; i < ROWS; i++) {
    delete[] array[i];
  }
  delete[] array;

  // Or even much much better.
  // Abstract it all away
  Matrix myField(2, 3);

  for (unsigned int r = 0; r < myField.row_count(); r++) {
    for (unsigned int c = 0; c < myField.col_count(); c++) {
      cout << myField.get(r, c) << " | ";
    }
    cout << endl;
  }

  return 0;
}