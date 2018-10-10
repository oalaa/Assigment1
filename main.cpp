#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

// A structure to store a matrix

struct matrix
{
    int* data;       // Pointer to 1-D array that will simulate matrix
    int row, col;
};

// Already implemented

void createMatrix (int row, int col, int num[], matrix& mat);
matrix operator+  (matrix mat1, matrix mat2); // Add if same dimensions
matrix operator-  (matrix mat1, matrix mat2); // Sub if same dimensions
matrix operator*  (matrix mat1, matrix mat2); // Multi if col1 == row2
matrix operator+  (matrix mat1, int scalar);  // Add a scalar
matrix operator-  (matrix mat1, int scalar);  // Subtract a scalar
matrix operator*  (matrix mat1, int scalar);  // Multiple by scalar

matrix operator+= (matrix& mat1, matrix mat2); // mat1 changes & return
// new matrix with the sum
matrix operator-= (matrix& mat1, matrix mat2); // mat1 changes + return new
// matrix with difference
matrix operator+= (matrix& mat, int scalar);   // change mat & return new matrix
matrix operator-= (matrix& mat, int scalar);   // change mat & return new matrix
void   operator++ (matrix& mat);   	// Add 1 to each element ++mat
void   operator-- (matrix& mat);    	// Sub 1 from each element --mat
istream& operator>> (istream& in, matrix& mat);
ostream& operator<< (ostream& out, matrix mat);
// Print matrix  as follows (2 x 3)			4	 6 	  8
// and return ostream to cascade printing	9	12  	123
bool   operator== (matrix mat1, matrix mat2);	// True if identical
bool   operator!= (matrix mat1, matrix mat2); 	// True if not same
bool   isSquare   (matrix mat);  // True if square matrix
bool   isSymetric (matrix mat);  // True if square and symmetric
bool   isIdentity (matrix mat);  // True if square and identity
matrix transpose(matrix& mat);    // Return new matrix with the transpose

//__________________________________________

int main()
{
    int data1 [] = {1,2,3,4,5,6,7,8};
    int data2 [] = {13,233,3,4,5,6};
    int data3 [] = {10,100,10,100,10,100,10,100};
    int num;
    matrix mat1, mat2, mat3;
    createMatrix (4, 2, data1, mat1);
    createMatrix (2, 3, data2, mat2);
    createMatrix (4, 2, data3, mat3);


    cout << mat1 << endl;
    cout << mat2 << endl;
    cout << mat3 << endl;



    //cout << (mat1 + mat3) << endl << endl;
    //cout << (mat3 + mat3) << endl << endl;

    ++mat1;
    cout << mat1 << endl;

    mat1+= mat3 += mat3;
    cout << mat1 << endl;
    cout << mat2 << endl;
    cout << mat3 << endl;
    cout <<"matrix1 + matrix3 "<<endl<< mat1 + mat3 <<endl;

    try
    {
        cout <<" matrix3 + matrix2 "<<endl;
        cout<< (mat3 + mat2) << endl;
    }

    catch (const char* except)
    {
        cout<<except<<endl;
    }

    cout <<" matrix3 - matrix3 "<<endl<< (mat3 - mat3) << endl;

    cout <<" matrix3 * matrix1 "<<endl;
    if(mat3.col==mat1.row)
    {
        cout <<mat3 * mat1 << endl;
    }
    else
    {
        cout<<"can't be multiplied as 1st matrix column and 2nd matrix row aren't equal"<<endl;
    }

    cout <<" matrix3 * matrix2 "<<endl<< (mat3 * mat2) << endl;


    cout<<"matrix3 + number "<<endl<<"Enter a number: ";
    cin>>num;
    cout<<endl<<mat3+num;

    cout<<"matrix1 - number "<<endl<<"Enter a number: ";
    cin>>num;
    cout<<endl<<mat1-num;

    cout<<"matrix3 * number "<<endl<<"Enter a number: ";
    cin>>num;
    cout<<endl<<mat3*num;


    if (mat1==mat3)
    {
        cout << "True" <<endl;
    }
    else
    {
        cout << "False" << endl;
    }
    if (mat1 != mat3)
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }
    cout << isSquare(mat1) << endl ;
    cout << isIdentity(mat1) << endl ;
    cout << transpose(mat2);

    return 0;
}
void createMatrix (int row, int col, int num[], matrix& mat)
{
    mat.row = row;
    mat.col = col;
    mat.data = new int [row * col];
    for (int i = 0; i < row * col; i++)
        mat.data [i] = num [i];
}
//function overloading to create a new empty matrix
matrix createMatrix(matrix mat1)
{
    matrix mat;
    mat.row=mat1.row;
    mat.col=mat1.col;
    mat.data=new int[mat.row*mat.col];
    return mat;
}

//print the three matrices
void print(matrix mat1, matrix mat2, matrix mat3)
{

    cout<<"MATRIX 1:"<<endl;
    cout << mat1 << endl;
    cout<<"MATRIX 2:"<<endl;
    cout << mat2 << endl;
    cout<<"MATRIX 3:"<<endl;
    cout << mat3 << endl;
}

// add a matrix to another
matrix operator+  (matrix mat1, matrix mat2)
{
    if (mat1.row==mat2.row  && mat1.col==mat2.col)
    {
        matrix mat=createMatrix( mat1);

        for(int i=0; i<mat1.row*mat1.col; i++)
        {

            mat.data[i]=mat1.data[i]+mat2.data[i];
        }
        return mat;
    }
    else
    {
        throw "can't be added as the dimensions aren't the same";
    }

}

// subtract a matrix from another and return new one
matrix operator-  (matrix mat1, matrix mat2)
{
    matrix mat=createMatrix( mat1);
    if (mat1.row==mat2.row  && mat1.col==mat2.col)
    {



        for(int i=0; i<mat1.row*mat1.col; i++)
        {

            mat.data[i]=mat1.data[i]-mat2.data[i];
        }
        return mat;
    }
    else
    {
        cout<< "can't be subtracted as the dimensions aren't the same";
    }
    //return mat;
}

//multiplying two matrices and returning new matrix
matrix operator*  (matrix mat1, matrix mat2)
{
    int sum;
    matrix mat3;
    mat3.row=mat1.row;
    mat3.col=mat2.col;
    mat3.data=new int[mat3.row*mat3.col];
    for(int i=0; i<mat1.row; i++)
    {
        for(int j=0; j<mat2.col; j++)
        {

            sum=0;
            for(int k=0; k<mat1.col; k++)
            {

                sum+=mat1.data[i*mat1.col+k]*mat2.data[k*mat2.col+j];
            }
            mat3.data[i*mat3.col+j]=sum;
        }

    }

    return mat3;
}

//add a number to matrix returning a new matrix
matrix operator+  (matrix mat1, int scalar)
{
    matrix mat=createMatrix( mat1);
    for(int i=0; i<mat1.row*mat1.col; i++)
    {
        mat.data[i]=mat1.data[i]+scalar;

    }
    return mat;
}

//subtract a number form matrix returning new matrix
matrix operator-  (matrix mat1, int scalar)
{
    matrix mat=createMatrix( mat1);
    for(int i=0; i<mat1.row*mat1.col; i++)
    {
        mat.data[i]=mat1.data[i]-scalar;

    }
    return mat;
}


//multiply matrix by number returning a new matrix
matrix operator*  (matrix mat1, int scalar)
{
    matrix mat=createMatrix(mat1);
    for(int i=0; i<mat1.row*mat1.col; i++)
    {
        mat.data[i]=mat1.data[i]*scalar;

    }
    return mat;
}

matrix operator+= (matrix& mat1, matrix mat2)
{
    for (int i=0; i<mat1.row * mat1.col; i++)
    {
        mat1.data[i] = mat1.data[i] + mat2.data[i];
    }
    return mat1;
}


matrix operator-= (matrix& mat1, matrix mat2)
{
    for (int i=0; i< mat1.row * mat1.col; i++)
    {
        mat1.data[i] = mat1.data[i] - mat2.data[i];
    }
    return mat1;
}


matrix operator+= (matrix& mat, int scalar)
{
    for (int i=0; i<mat.row * mat.col; i++)
    {
        mat.data[i] = mat.data[i] + scalar ;
    }
    return mat;


}


matrix operator-= (matrix& mat, int scalar)
{
    for (int i=0; i<mat.row * mat.col; i++)
    {
        mat.data[i] = mat.data[i] - scalar ;
    }
    return mat;


}


void   operator++ (matrix& mat)
{
    for (int i=0; i<mat.row * mat.col; i++)
    {
        mat.data[i] = mat.data[i] + 1 ;
    }

}

void   operator-- (matrix& mat)
{
    for (int i=0; i<mat.row * mat.col; i++)
    {
        mat.data[i] = mat.data[i] - 1 ;
    }

}

istream& operator>> (istream& in, matrix& mat)
{
    int row, col ;
    cout << "Enter number of rows : " ;
    cin >> row;
    cout << "\nEnter number of columns : " ;
    cin >> col ;
    cout << "\nEnter data : " ;
    int num [row * col];
    for (int i=0; i<row*col; i++)
    {
        cin >> num[i];
    }

    createMatrix(row, col, num, mat );

}

ostream& operator<< (ostream& out, matrix mat)
{
    out << "The Content Of Matrix : "<< endl;

    for (int i=0 ; i<mat.row ; i++)
    {
        for (int j=0 ; j<mat.col ; j++)
        {
            out << mat.data[i*mat.col+j] << " ";
        }
        cout << endl;

    }
    cout << endl;
    return out ;
}
bool   operator== (matrix mat1, matrix mat2)
{
    if ((mat1.row == mat2.row) && (mat1.col == mat2.col))
    {
        for (int i=0 ; i<mat1.row ; i++ )
        {
            for (int j=0 ; j<mat1.col ; j++)
            {
                if (mat1.data[i*mat1.col+j] == mat2.data[i*mat2.col+j])
                {
                    return true;
                }
                else
                    return false;
            }
        }
    }
    else
    {
        return false;
    }

}

bool   operator!= (matrix mat1, matrix mat2)
{
    if ((mat1.row == mat2.row) && (mat1.col == mat2.col))
    {
        for (int i=0 ; i<mat1.row ; i++ )
        {
            for (int j=0 ; j<mat1.col ; j++)
            {
                if (mat1.data[i*mat1.col+j] != mat2.data[i*mat2.col+j])
                {
                    return true;
                }
                else
                    return false;
            }
        }
    }
    else if ((mat1.row != mat2.row) && (mat1.col != mat2.col) )
        return true;
}
bool   isSquare   (matrix mat)
{
    if (mat.row == mat.col)
    {
        return true;
    }
    else
        return false;
}
bool   isIdentity (matrix mat)
{


    if (isSquare(mat) ==1 )
    {
        for (int i = 0; i < mat.row; i++)
        {
            for (int j = 0; j < mat.col; j++)
            {
                if (i == j && mat.data[i*mat.col+j] == 1) {}
                else if (i!= j && mat.data[i*mat.col+j] == 0)
                    return true;
            }
        }
        return false;
    }
    else
        return false;
}
bool   isSymetric (matrix mat)
{
    if (isSquare(mat) == 1)
    {


        for (int i=0 ; i< mat.row ; i++)
        {
            for (int j=0 ; j< mat.col ; j++)
            {
                if (mat.data[i*mat.col+j] == mat.data[j*mat.col+i])
                {
                    return true;

                }
                else
                    return false;
            }
        }
    }
    else
        return false;
}
matrix transpose(matrix& mat)
{
    matrix TransposeMatrix;
    TransposeMatrix.row = mat.col;
    TransposeMatrix.col = mat.row;
    TransposeMatrix.data = new int [TransposeMatrix.col * TransposeMatrix.row];


    for (int i=0 ; i<mat.row ; i++)
    {
        for (int j=0 ; j<mat.col ; j++)
        {
            TransposeMatrix.data[j*mat.row+i] = mat.data[i*mat.col+j];
        }
    }
    return TransposeMatrix;
}

