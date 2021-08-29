//Author : Anmol Abhay Jain
//Date : 29/01/2021
//coding club cpp git task->

#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Matrix {
    private:
    vector<vector<T>> mat;           // Our matrix as vector of vector
    int rowSize = -1, colSize = -1;  // No. of rows and columns respectively

    public:
    //constructor
    Matrix(int N, int M, T defaultValue);  // initialises a MxN matrix with defaultValue
    Matrix(Matrix& temp);  // Must create a deep copy of the temp matrix
    Matrix eye(int size);   // Creates an identity matrix of shape = size x size

    //Logging Functions
    void printMatrix();

    //Constructor Overloading
    //matrix Operation
    Matrix<T> operator*(Matrix &);
    Matrix<T> operator+(Matrix &);
    Matrix<T> operator-(Matrix &);

    // Scalar Operations
    Matrix<T> operator+(double);
    Matrix<T> operator-(double);
    Matrix<T> operator*(double);
    Matrix<T> operator/(double);

    //getter functions
    vector<vector<T>>& getMatrix();
    int getRowSize();
    int getColSize();

    //setter functions
    void setMatrix(vector<vector<T>>& tempMat);

    //utility functions
    Matrix transpose(); // returns the transpose of the matrix
    Matrix matExponentiation(Matrix& M, int pow); // return M^n for the matrix
    Matrix matExponentiation(int pow); // return M^n for the matrix
    void PowerInteration(vector<T> eigenVector, double eigenValue);   // Using Power interation method to find
                                                    // the most dominant eigenVector and its corresponding eigenvalue
                                                    // In this function rather than returning ans we are going to
                                                    // fill the appropriate values in eigenVector and eigenValue which are passed as param

    // Many functionalites can now be added
    // like finding out the PCA of the matrix,
    // finding the Null space of the matrix and so on...


};
template <typename T>
Matrix<T>::Matrix(int N, int M, T defaultValue){
    mat.resize(N, vector<T>(M, defaultValue));  //initialize the matrix
    rowSize = N;
    colSize = M;
}

template <typename T>
Matrix<T>::Matrix(Matrix& temp){
    *this = temp;
    // this->mat = temp.getMatrix();
    // this->rowSize = temp.getRowSize();
    // this->colSize = temp.getColSize();
}

template <typename T>
Matrix<T> Matrix<T>::eye(int len){
    vector<vector<T>> ansMat(len, vector<T>(len), (T)0);    // the matrix which will store the identity matrix

    for(int i=0; i<len; i++){
        ansMat[i][i]=1;
    }

    Matrix<T> C(len, len, (T)0);
    C.setMatrix(ansMat);
    return C;
}

template <typename T>
void Matrix<T>::printMatrix(){
    cout << "Matrix: " << endl;
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            cout << " " << mat[i][j] << " ";
        }
        cout << endl;
    }
}

template <typename T>
vector<vector<T>>& Matrix<T>::getMatrix(){
    return this->mat;
}

template <typename T>
int Matrix<T>::getRowSize(){
    return this->rowSize;
}

template <typename T>
int Matrix<T>::getColSize(){
    return this->colSize;
}

template <typename T>
void Matrix<T>::setMatrix(vector<vector<T>>& tempMat){
    mat = tempMat;
    rowSize = tempMat.size();
    colSize = tempMat[0].size();
}

//Matrix operation

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix& rhs){
    vector<vector<T>> ansMat(rowSize, vector<T>(rhs.getColSize(), (T)0)); // the matrix which will store the value of multiplication
    vector<vector<T>> B = rhs.getMatrix();

    assert(colSize == rhs.getRowSize());
    int i,j,k;
    T temp;
    for (i = 0; i < rowSize; i++){
        for (j = 0; j < rhs.getColSize(); j++){
            temp = (T)0;
            for (k = 0; k < colSize; k++){
                temp += mat[i][k] * B[k][j];
            }
            ansMat[i][j] = temp;
        }
    }

    Matrix<T> C(rowSize, rhs.getColSize(), (T)0);
    C.setMatrix(ansMat);
    return C;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix& rhs){
	vector<vector<T>> ansMat(rowSize, vector<T>(colSize, (T)0)); // the matrix which will store the value of addition
    vector<vector<T>> B = rhs.getMatrix();

    assert(colSize == rhs.getColSize());
    assert(rowSize == rhs.getRowSize());
    int i,j;

    for (i = 0; i < rowSize; i++){
        for (j = 0; j < colSize; j++){
            ansMat[i][j] = mat[i][j] + B[i][j];
        }
    }

    Matrix<T> C(rowSize, colSize, (T)0);
    C.setMatrix(ansMat);
    return C;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix& rhs){
	vector<vector<T>> ansMat(rowSize, vector<T>(colSize, (T)0)); // the matrix which will store the value of subtraction
    vector<vector<T>> B = rhs.getMatrix();

    assert(colSize == rhs.getColSize());
    assert(rowSize == rhs.getRowSize());
    int i,j;

    for (i = 0; i < rowSize; i++){
        for (j = 0; j < colSize; j++){
            ansMat[i][j] = mat[i][j] - B[i][j];
        }
    }

    Matrix<T> C(rowSize, colSize, (T)0);
    C.setMatrix(ansMat);
    return C;
}

//Scalar overloading

template <typename T>
Matrix<T> Matrix<T>::operator+(double unit){
	vector<vector<T>> ansMat(rowSize, vector<T>(colSize, (T)0)); // the matrix which will store the value of addition

    int i,j;

    for (i = 0; i < rowSize; i++){
        for (j = 0; j < colSize; j++){
            ansMat[i][j] = mat[i][j] + unit;
        }
    }

    Matrix<T> C(rowSize, colSize, (T)0);
    C.setMatrix(ansMat);
    return C;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(double unit){
	vector<vector<T>> ansMat(rowSize, vector<T>(colSize, (T)0)); // the matrix which will store the value of subtraction

    int i,j;

    for (i = 0; i < rowSize; i++){
        for (j = 0; j < colSize; j++){
            ansMat[i][j] = mat[i][j] - unit;
        }
    }

    Matrix<T> C(rowSize, colSize, (T)0);
    C.setMatrix(ansMat);
    return C;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(double unit){
	vector<vector<T>> ansMat(rowSize, vector<T>(colSize, (T)0)); // the matrix which will store the value of multiplication

    int i,j;

    for (i = 0; i < rowSize; i++){
        for (j = 0; j < colSize; j++){
            ansMat[i][j] = mat[i][j] * unit;
        }
    }

    Matrix<T> C(rowSize, colSize, (T)0);
    C.setMatrix(ansMat);
    return C;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(double unit){
	vector<vector<T>> ansMat(rowSize, vector<T>(colSize, (T)0)); // the matrix which will store the value of division

    int i,j;
    assert(unit != 0);

    for (i = 0; i < rowSize; i++){
        for (j = 0; j < colSize; j++){
            ansMat[i][j] = mat[i][j] / unit;
        }
    }

    Matrix<T> C(rowSize, colSize, (T)0);
    C.setMatrix(ansMat);
    return C;
}

//Matrix Transpose

template <typename T>
Matrix<T> Matrix<T>::transpose(){
    vector<vector<T>> ansMat(rowSize, vector<T>(colSize, (T)0)); // the matrix which will store the value transpose

    int i,j;

    for (i = 0; i < rowSize; i++){
        for (j = 0; j < colSize; j++){
            ansMat[j][i] = mat[i][j];
        }
    }

    Matrix<T> C(rowSize, colSize, (T)0);
    C.setMatrix(ansMat);
    return C;
}

//Matrix exponentiation

template <typename T>
Matrix<T> Matrix<T>::matExponentiation(int pow){
    assert(colSize == rowSize);
    assert(pow >= 0);

    if(pow == 0){
        Matrix temp(colSize, rowSize, (T)1);
        return temp;
    }

    Matrix B(rowSize, colSize, (T)0);
    Matrix temp(rowSize, colSize, (T)0);
    B.setMatrix(mat);
    temp.setMatrix(mat);
    pow--;

    while(pow > 0){
        if(pow % 2 == 0){
            B = B*B;
            pow /= 2;
        }
        else{
            B = B*temp;
            pow--;
        }
    }

    return B;
}

int main(){
    cout<<"elementry tests ->"<<endl;

    Matrix<int> a(4, 2, 2);
    a.printMatrix();

    Matrix<int> b(a);
    b.printMatrix();

    vector<vector<int>> tempMat(3, vector<int>(4, 5));
    a.setMatrix(tempMat);
    a.printMatrix();

    Matrix<int> c(2, 3, 3), z(4,2,8);
    cout<<"Operator tests ->"<<endl<<endl;

    cout<<"Matrix multiplication"<<endl;
    (b*c).printMatrix();

    cout<<"Matrix addition"<<endl;
    (b+z).printMatrix();

    cout<<"Matrix subtraction"<<endl;
    (b-z).printMatrix();

    cout<<"Scalar addition"<<endl;
    (b+5.0).printMatrix();

    cout<<"Scalar subtraction"<<endl;
    (b-5.0).printMatrix();

    cout<<"Scalar multiplication"<<endl;
    (b*5.0).printMatrix();

    Matrix<double> e(4, 2, 2);
    cout<<"Scalar division (double)"<<endl;
    (e/5.0).printMatrix();

    cout<<"Matrix transpose ->"<<endl;
    vector<vector<int>> trans(3,vector<int>(3,0));
    int it=1;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            trans[i][j] = it++;
        }
    }
    Matrix<int> d(3, 3, 0);
    d.setMatrix(trans);
    cout<<"Original matrix"<<endl;
    d.printMatrix();
    cout<<"Transposed matrix"<<endl;
    (d.transpose()).printMatrix();

    cout<<"Matrix exponentiation ->"<<endl;
    cout<<"Original matrix"<<endl;
    d.printMatrix();
    cout<<"Power = 3"<<endl;
    (d.matExponentiation(3)).printMatrix();

    return 0;
}
