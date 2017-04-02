function sumMatrix(A, B) {
    if (A.length != B.length || A[0].length != B[0].length)
        return false;
    var m = A.length,
        n = A[0].length,
        C = [];
    for (var i = 0; i < m; i++) {
        C[i] = [];
        for (var j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    }
    return C;
}

function subMatrix(A, B) {
    if (A.length != B.length || A[0].length != B[0].length)
        return false;
    var m = A.length,
        n = A[0].length,
        C = [];
    for (var i = 0; i < m; i++) {
        C[i] = [];
        for (var j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    }
    return C;
}

function multiplyMatrix(A, B) {
    var rowsA = A.length,
        colsA = A[0].length,
        rowsB = B.length,
        colsB = B[0].length,
        C = [];
    if (colsA != rowsB) return false;
    for (var i = 0; i < rowsA; i++)
        C[i] = [];
    for (var k = 0; k < colsB; k++) {
        for (var i = 0; i < rowsA; i++) {
            var t = 0;
            for (var j = 0; j < rowsB; j++)
                t += A[i][j] * B[j][k];
            C[i][k] = t;
        }
    }
    return C;
}

function multMatrixNumber(a, A) {
    var m = A.length,
        n = A[0].length,
        B = [];
    for (var i = 0; i < m; i++) {
        B[i] = [];
        for (var j = 0; j < n; j++)
            B[i][j] = a * A[i][j];
    }
    return B;
}

function transMatrix(A) {
    var m = A.length,
        n = A[0].length,
        AT = [];
    for (var i = 0; i < n; i++) {
        AT[i] = [];
        for (var j = 0; j < m; j++)
            AT[i][j] = A[j][i];
    }
    return AT;
}

function determinant(A) {
    var N = A.length,
        B = [],
        denom = 1,
        exchanges = 0;
    for (var i = 0; i < N; ++i) {
        B[i] = [];
        for (var j = 0; j < N; ++j)
            B[i][j] = A[i][j];
    }
    for (var i = 0; i < N - 1; ++i) {
        var maxN = i,
            maxValue = Math.abs(B[i][i]);
        for (var j = i + 1; j < N; ++j) {
            var value = Math.abs(B[j][i]);
            if (value > maxValue)
                maxN = j;
            maxValue = value;
        }
        if (maxN > i) {
            var temp = B[i];
            B[i] = B[maxN];
            B[maxN] = temp;
            ++exchanges;
        } else {
            if (maxValue == 0) return maxValue;
        }
        var value1 = B[i][i];
        for (var j = i + 1; j < N; ++j) {
            var value2 = B[j][i];
            B[j][i] = 0;
            for (var k = i + 1; k < N; ++k)
                B[j][k] = (B[j][k] * value1 - B[i][k] * value2) / denom;
        }
        denom = value1;
    }
    if (exchanges % 2)
        return -B[N - 1][N - 1];
    else
        return B[N - 1][N - 1];
}

function adjugateMatrix(A) {
    var N = A.length,
        adjA = [];
    for (var i = 0; i < N; i++) {
        adjA[i] = [];
        for (var j = 0; j < N; j++) {
            var B = [],
                sign = ((i + j) % 2 == 0) ? 1 : -1;
            for (var m = 0; m < j; m++) {
                B[m] = [];
                for (var n = 0; n < i; n++)
                    B[m][n] = A[m][n];
                for (var n = i + 1; n < N; n++)
                    B[m][n - 1] = A[m][n];
            }
            for (var m = j + 1; m < N; m++) {
                B[m - 1] = [];
                for (var n = 0; n < i; n++)
                    B[m - 1][n] = A[m][n];
                for (var n = i + 1; n < N; n++)
                    B[m - 1][n - 1] = A[m][n];
            }
            adjA[i][j] = sign * determinant(B); // Функцию Determinant см. выше
        }
    }
    return adjA;
}

function inverseMatrix(A) {
    if (A.length != A[0].length)
        return false;
    var det = determinant(A);
    if (det == 0)
        return false;
    var N = A.length,
        A = adjugateMatrix(A);
    for (var i = 0; i < N; i++)
        for (var j = 0; j < N; j++)
            A[i][j] /= det;
    return A;
}

function gauss(matrix) {
    var i, j, n, m,
        tmp,
        result = [],
        k;

    n = matrix.length;
    m = matrix[0].length + 1;

    for (i = 0; i < n; i++) {
        tmp = matrix[i][i];
        for (j = n; j >= i; j--)
            matrix[i][j] /= tmp;
        for (j = i + 1; j < n; j++) {
            tmp = matrix[j][i];
            for (k = n; k >= i; k--)
                matrix[j][k] -= tmp * matrix[i][k];
        }
    }

    result[n - 1] = matrix[n - 1][n];
    for (i = n - 2; i >= 0; i--) {
        result[i] = matrix[i][n];
        for (j = i + 1; j < n; j++) result[i] -= matrix[i][j] * result[j];
    }
    return result;
}