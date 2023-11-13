#include <iostream>

using namespace std;

struct Node {
    int row;
    int col;
    int data;
};

struct Head {
    int row; // Total rows
    int col; // Total columns
    int numNodes;
    Node* nodes;
};

bool isSparse(int** mat, int rows, int columns) {
    int zeroCounter = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (mat[i][j] == 0) {
                zeroCounter++;
            }
        }
    }

    if (zeroCounter >= (rows * columns) / 2) {
        return true;
    }
    return false;
}

Head toSparse(int** mat, int rows, int columns) {
    if (isSparse(mat, rows, columns)) {
        Head newHead;
        newHead.row = rows;
        newHead.col = columns;
        newHead.numNodes = 0;

        int Counter = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (mat[i][j] != 0) {
                    Counter++;
                }
            }
        }

        newHead.nodes = new Node[Counter];
        int tempIndex = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (mat[i][j] != 0) {
                    newHead.nodes[tempIndex].row = i;
                    newHead.nodes[tempIndex].col = j;
                    newHead.nodes[tempIndex].data = mat[i][j];
                    newHead.numNodes++;
                    tempIndex++;
                }
            }
        }
        return newHead;
    } else {
        Head newHead;
        newHead.row = rows;
        newHead.col = columns;
        newHead.numNodes = 0;
        newHead.nodes = NULL;
        return newHead; // Not Sparse
    }
}

void display(int** mat, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << mat[i][j] << " ";
        }
       cout << endl;
    }
}

void sparseDisplay(Head sparseMatrix) {
    cout << "Sparse Matrix:" << endl;
    cout << "\tRow\tColumn\tData" << endl;
    for (int i = 0; i < sparseMatrix.numNodes; i++) {
        cout << "\t" << sparseMatrix.nodes[i].row << "\t" << sparseMatrix.nodes[i].col << "\t" << sparseMatrix.nodes[i].data << endl;
    }
}

int main() {
    int rows , columns ;
    cout << "Enter row & columns : " ;
    cin >> rows >> columns ;
    int** mat = new int*[rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new int[columns];
        for (int j = 0 ; j < columns ; j++){
        	int tempNum ;
        	cout << "Enter element of [" << i << "][" << j << "] : " ;
			cin >> tempNum ;
			mat[i][j] = tempNum ; 
		}
    }
	
	display(mat , rows , columns) ;3

    Head sparseMatrix = toSparse(mat, rows, columns);

    sparseDisplay(sparseMatrix);

    return 0;
}

/*
    Reza Asadi (Github : RezaGooner)
	1402/08/22 ~ 2023/11/13
*/