var action = 0;
var title;
var titles = ["Вывод матрицы",
              "Умножение на число",
              "Сложение",
              "Вычитание",
              "Умножение",
              "Транспонирование",
              "Обратная матрица",
              "Решение СЛАУ по Гауссу"];

function setAction(action) {
    this.action = action;
    document.getElementById("wrapper2").style.display = action == 2 | action == 3 | action == 4 ? "block" : "none";
    if (action == 7) {
        var rows = document.getElementById("1").rows;
        for (var i = 0; i < rows.length; i++) {
            rows[i].insertCell(-1).innerHTML = "<input type='text' value='" + i + "'>";
        }
    }
    document.getElementById("number").style.display = action == 1 ? "block" : "none";
    if (title == undefined)
        title = document.getElementById("title");
    title.innerHTML = titles[action];
}

function getRandomInt() {
    var max = 9,
        min = 0;
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

function updateTable(input) {
    var table = input.parentElement.parentElement.querySelector("TABLE");
    var cols = input.parentElement.querySelector(".cols").value;
    var rows = input.parentElement.querySelector(".rows").value;
    table.innerHTML = "";
    for (var i = 0; i < rows; i++) {
        var row = table.insertRow(i);
        for (var j = 0; j < cols; j++) {
            row.insertCell(j).innerHTML = "<input type='text' value='" + i + ":" + j + "'>";
        }
    }
}

function fillRandom(input) {
    var table = input.parentElement.parentElement.querySelector("TABLE");
    var rows = table.rows;
    for (var i = 0; i < rows.length; i++) {
        var row = table.rows[i];
        for (var j = 0; j < row.cells.length; j++) {
            row.cells[j].querySelector("input").value = getRandomInt();
        }
    }
}


function start() {
    var tables = document.querySelectorAll(".tables table");
    switch (action) {
    case 0:
        showResult(getMatrix(tables[0]));
        break;
    case 1:
        showResult(multMatrixNumber(parseInt(document.getElementById("number").value), getMatrix(tables[0])));
        break;
    case 2:
        showResult(sumMatrix(getMatrix(tables[0]), getMatrix(tables[1])));
        break;
    case 3:
        showResult(subMatrix(getMatrix(tables[0]), getMatrix(tables[1])));
        break;
    case 4:
        showResult(multiplyMatrix(getMatrix(tables[0]), getMatrix(tables[1])));
        break;
    case 5:
        showResult(transMatrix(getMatrix(tables[0]), getMatrix(tables[1])));
        break;
    case 6:
        showResult(inverseMatrix(getMatrix(tables[0]), getMatrix(tables[1])));
        break;
    case 7:
        showGaussResult(gauss(getMatrix(tables[0])));
        break;
    }
}

function getMatrix(table) {
    var matrix = [];
    for (var j = 0; j < table.rows.length; j++) {
        matrix[j] = [];
        for (var k = 0; k < table.rows[j].cells.length; k++)
            matrix[j][k] = parseInt(table.rows[j].cells[k].querySelector("input").value);
    }
    return matrix;
}

function showResult(finalMatrix) {
    var oldTable = document.getElementById("result_view");
    if (oldTable != undefined)
        document.getElementById("result").removeChild(oldTable);
    if (finalMatrix === false) {
        var error = document.createElement("H4");
        error.id = "result_view";
        error.innerHTML = "Ошибка!";
        document.getElementById("result").appendChild(error);
        return;
    }
    var newTable = document.createElement("TABLE");
    newTable.id = "result_view";
    for (var i = 0; i < finalMatrix.length; i++) {
        var row = finalMatrix[i];
        var tableRow = newTable.insertRow(i);
        for (var j = 0; j < row.length; j++) {
            tableRow.insertCell(j).innerHTML = row[j];
        }
    }
    document.getElementById("result").appendChild(newTable);
}

function showGaussResult(finalMatrix) {
    var oldTable = document.getElementById("result_view");
    if (oldTable != undefined)
        document.getElementById("result").removeChild(oldTable);
    var newTable = document.createElement("TABLE");
    newTable.id = "result_view";
    for (var i = 0; i < finalMatrix.length; i++) {
        var row = finalMatrix[i];
        var tableRow = newTable.insertRow(i)
        tableRow.insertCell(0).innerHTML = "Решение №" + (i + 1);
        tableRow.insertCell(1).innerHTML = finalMatrix[i];
    }
    document.getElementById("result").appendChild(newTable);
}