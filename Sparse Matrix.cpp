#include <iostream>
#include <cassert>

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
    Node* nodes; // nodes Array
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



Head createSMatrix(){
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

    display(mat , rows , columns) ;

    Head sparseMatrix = toSparse(mat, rows, columns);

    sparseDisplay(sparseMatrix);

    return sparseMatrix ;
}

Head adder(Head head1, Head head2) {
    assert(head1.row == head2.row && head1.col == head2.col);

    Head newHead;
    newHead.row = head1.row;
    newHead.col = head1.col;
    newHead.numNodes = 0;
    newHead.nodes = new Node[head1.numNodes + head2.numNodes];

    int index1 = 0, index2 = 0, newIndex = 0;
    while (index1 < head1.numNodes && index2 < head2.numNodes) {
        if (head1.nodes[index1].row < head2.nodes[index2].row
            || (head1.nodes[index1].row == head2.nodes[index2].row && head1.nodes[index1].col < head2.nodes[index2].col)) {
            newHead.nodes[newIndex].row = head1.nodes[index1].row;
            newHead.nodes[newIndex].col = head1.nodes[index1].col;
            newHead.nodes[newIndex].data = head1.nodes[index1].data;
            index1++;
        } else if (head1.nodes[index1].row > head2.nodes[index2].row
            || (head1.nodes[index1].row == head2.nodes[index2].row && head1.nodes[index1].col > head2.nodes[index2].col)) {
            newHead.nodes[newIndex].row = head2.nodes[index2].row;
            newHead.nodes[newIndex].col = head2.nodes[index2].col;
            newHead.nodes[newIndex].data = head2.nodes[index2].data;
            index2++;
        } else {
            newHead.nodes[newIndex].row = head1.nodes[index1].row;
            newHead.nodes[newIndex].col = head1.nodes[index1].col;
            newHead.nodes[newIndex].data = head1.nodes[index1].data + head2.nodes[index2].data;
            index1++;
            index2++;
        }
        newIndex++;
        newHead.numNodes++;
    }

    // Copy remaining nodes from head1
    while (index1 < head1.numNodes) {
        newHead.nodes[newIndex].row = head1.nodes[index1].row;
        newHead.nodes[newIndex].col = head1.nodes[index1].col;
        newHead.nodes[newIndex].data = head1.nodes[index1].data;
        index1++;
        newIndex++;
        newHead.numNodes++;
    }

    // Copy remaining nodes from head2
    while (index2 < head2.numNodes) {
        newHead.nodes[newIndex].row = head2.nodes[index2].row;
        newHead.nodes[newIndex].col = head2.nodes[index2].col;
        newHead.nodes[newIndex].data = head2.nodes[index2].data;
        index2++;
        newIndex++;
        newHead.numNodes++;
    }
	
	if (newHead.numNodes >= ((newHead.row * newHead.col)/2) ){
		cout << "New matrix isn't sparse!" << endl ;
	}
    return newHead;
}

Head subtractor(Head head1, Head head2) {
    assert(head1.row == head2.row && head1.col == head2.col);

    Head newHead;
    newHead.row = head1.row;
    newHead.col = head1.col;
    newHead.numNodes = 0;
    newHead.nodes = new Node[head1.numNodes + head2.numNodes];

    int index1 = 0, index2 = 0, newIndex = 0;
    while (index1 < head1.numNodes && index2 < head2.numNodes) {
        if (head1.nodes[index1].row < head2.nodes[index2].row
            || (head1.nodes[index1].row == head2.nodes[index2].row && head1.nodes[index1].col < head2.nodes[index2].col)) {
            newHead.nodes[newIndex].row = head1.nodes[index1].row;
            newHead.nodes[newIndex].col = head1.nodes[index1].col;
            newHead.nodes[newIndex].data = head1.nodes[index1].data;
            index1++;
        } else if (head1.nodes[index1].row > head2.nodes[index2].row
            || (head1.nodes[index1].row == head2.nodes[index2].row && head1.nodes[index1].col > head2.nodes[index2].col)) {
            newHead.nodes[newIndex].row = head2.nodes[index2].row;
            newHead.nodes[newIndex].col = head2.nodes[index2].col;
            newHead.nodes[newIndex].data = -head2.nodes[index2].data; // ????? ???????
            index2++;
        } else {
            newHead.nodes[newIndex].row = head1.nodes[index1].row;
            newHead.nodes[newIndex].col = head1.nodes[index1].col;
            newHead.nodes[newIndex].data = head1.nodes[index1].data - head2.nodes[index2].data; // ????? ???????
            index1++;
            index2++;
        }
        newIndex++;
        newHead.numNodes++;
    }

    // ??? ???? ???? ??????? ?? head1
    while (index1 < head1.numNodes) {
        newHead.nodes[newIndex].row = head1.nodes[index1].row;
        newHead.nodes[newIndex].col = head1.nodes[index1].col;
        newHead.nodes[newIndex].data = head1.nodes[index1].data;
        index1++;
        newIndex++;
        newHead.numNodes++;
    }

    // ??? ???? ???? ??????? ?? head2
    while (index2 < head2.numNodes) {
        newHead.nodes[newIndex].row = head2.nodes[index2].row;
        newHead.nodes[newIndex].col = head2.nodes[index2].col;
        newHead.nodes[newIndex].data = -head2.nodes[index2].data; // ????? ???????
        index2++;
        newIndex++;
        newHead.numNodes++;
    }

	if (newHead.numNodes >= ((newHead.row * newHead.col)/2) ){
		cout << "New matrix isn't sparse!" << endl ;
	}
    return newHead;
}

void scalarProduct(Head* head, int num) {
    for (int i = 0; i < head->numNodes; i++) {
        head->nodes[i].data *= num;
    }
}

int main() {
    //Head mat1 = createSMatrix();
	//Head mat2 = createSMatrix();
	
    //scalarProduct(&mat1, 2);
    //sparseDisplay(adder(mat1 , mat2));
	//sparseDisplay(subtractor(mat1 , mat2));

    return 0;
}

/*
    Reza Asadi (Github : RezaGooner)
	1402/08/22 ~ 2023/11/13
	Edited : 08/24 ~ 11/15
*/