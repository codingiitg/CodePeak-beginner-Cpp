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
    void padding();
    void setMatrix(vector<vector<T>>& tempMat);

    //utility functions
    Matrix transpose(); // returns the transpose of the matrix
    Matrix matExponentiation(Matrix& M, int pow); // return M^n for the matrix
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

template <typename T>                           //new generated
void Matrix<T>::padding(){
    vector<T>v(max(rowSize,colSize),(T)0);
    if(rowSize!=colSize){
        for(int i=0;i<max(rowSize,colSize);i++){
            if(i>=rowSize){
                mat.push_pack(v);
            }
            for(int j=0;j<max(colSize,rowSize);j++){
                if(j>=colSize) mat[i].push_back((T)0);
            }
        }
    }
}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix& rhs){
    assert(colSize == rhs.getColSize && rowSize == rhs.getRowSize());
    vector<vector<T>> B=rhs.getMatrix();
    vector<vector<T>> ansMat(rowSize, vector<T>(colSize,(T)0));
    for(int i=0;i<rowSize;i++){
        for(int j = 0;j < colSize; j++){
            ansMat[i][j]=B[i][j]+mat[i][j];
        }
    }
    Matrix<T> C(rowSize, colSize, (T)0);
    C.setMatrix(ansMat);
    return C;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix& rhs){
    assert(colSize == rhs.getColSize && rowSize == rhs.getRowSize());
    vector<vector<T>> B=rhs.getMatrix();
    vector<vector<T>> ansMat(rowSize, vector<T>(colSize,(T)0));
    for(int i=0;i<rowSize;i++){
        for(int j = 0;j < colSize; j++){
            ansMat[i][j]=mat[i][j]-B[i][j];
        }
    }
    Matrix<T> C(rowSize, colSize, (T)0);
    C.setMatrix(ansMat);
    return C;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix& rhs){
    vector<vector<T>> ansMat(rowSize, vector<T>(rhs.getColSize(), (T)0)); // the matrix which will store the value of multiplication
    vector<vector<T>> B = rhs.getMatrix();

    assert(colSize == rhs.getRowSize());
    
    int i,j,k;
    int rowSize1=rhs.getRowSize();
    int colSize1=rhs.getColSize();

    if(colSize==1 && rowSize==1 && colSize1==1 && rowSize1==1){
        Matrix<T> C(1,1,T(0));
        ansMat[0][0] = mat[0][0]*B[0][0];
        C.setMatrix(ansMat);
        return C;
    }
    vector<vector<T>> a(rowSize/2,vector<T>(colSize/2,(T)0));
    for(i=0;i<rowSize/2;i++){
        for(j=0;j<colSize/2;j++){
            a[i][j]=mat[i][j];
        }
    }
    Matrix<T> am(rowSize/2,colSize/2,(T)0);
    am.setMatrix(a);
    vector<vector<T>> b(rowSize/2,vector<T>((colSize-colSize/2),(T)0));
    for(i=0;i<rowSize/2;i++){
        for(j=colSize/2;j<colSize;j++){
            b[i][j-(colSize/2)]=mat[i][j];
        }
    }
    Matrix<T> bm(rowSize/2,(colSize-colSize/2),(T)0);
    bm.setMatrix(b);
    vector<vector<T>> c(rowSize-rowSize/2,vector<T>((colSize/2),(T)0));
    for(i=rowSize/2;i<rowSize;i++){
        for(j=0;j<colSize/2;j++){
            c[i-rowSize/2][j]=mat[i][j];
        }
    }
    Matrix<T> cm(rowSize-rowSize/2,(colSize/2),(T)0);
    cm.setMatrix(c);
    vector<vector<T>> d(rowSize-rowSize/2,vector<T>((colSize/2),(T)0));
    for(i=rowSize/2;i<rowSize;i++){
        for(j=colSize/2;j<colSize;j++){
            d[i-rowSize/2][j-colSize/2]=mat[i][j];
        }
    }
    Matrix<T> dm(rowSize-rowSize/2,(colSize/2),(T)0);
    dm.setMatrix(d);

    vector<vector<T>> e(rowSize1/2,vector<T>(colSize1/2,(T)0));
    for(i=0;i<rowSize1/2;i++){
        for(j=0;j<colSize1/2;j++){
            e[i][j]=B[i][j];
        }
    }
    Matrix<T> em(rowSize1/2,colSize1/2,(T)0);
    em.setMatrix(e);
    vector<vector<T>> f(rowSize1/2,vector<T>((colSize1-colSize1/2),(T)0));
    for(i=0;i<rowSize1/2;i++){
        for(j=colSize1/2;j<colSize1;j++){
            f[i][j-(colSize1/2)]=B[i][j];
        }
    }
    Matrix<T> fm(rowSize1/2,(colSize1-colSize1/2),(T)0);
    fm.setMatrix(f);
    vector<vector<T>> g(rowSize1-rowSize1/2,vector<T>((colSize1/2),(T)0));
    for(i=rowSize1/2;i<rowSize1;i++){
        for(j=0;j<colSize1/2;j++){
            g[i-rowSize1/2][j]=B[i][j];
        }
    }
    Matrix<T> gm(rowSize1-rowSize1/2,(colSize1/2),(T)0);
    gm.setMatrix(g);
    vector<vector<T>> h(rowSize1-rowSize1/2,vector<T>((colSize1/2),(T)0));
    for(i=rowSize1/2;i<rowSize1;i++){
        for(j=colSize1/2;j<colSize1;j++){
            d[i-rowSize1/2][j-colSize1/2]=B[i][j];
        }
    }
    Matrix<T> hm(rowSize1-rowSize1/2,(colSize1/2),(T)0);
    hm.setMatrix(h);
    
    //computing 7 products p1 to p7


    Matrix<T> C(rowSize, rhs.getColSize(), (T)0);
    C.setMatrix(ansMat);
    return C;
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
    
    (a*b).printMatrix();
    
    return 0;
}