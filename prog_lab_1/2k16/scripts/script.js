var matrixes = ["A", "B", "I", "C"];
var consts = ["k"];

function setAction() {
    var wrappers = document.getElementById("wrappers");
    for(var i = 0; i<matrixes.length;i++){
        wrappers.innerHTML+='<div class="wrapper_table" id="wrapper_'+matrixes[i]+'"><h3>Матрица '+matrixes[i]+'</h3><table class="matrix" id="matrix_'+matrixes[i]+'"></table><div class="controls"><input type="button" value="Случайные числа" onclick="fillRandom(this);"></div></div>';
    }
    for(var i = 0; i<consts.length;i++){
        wrappers.innerHTML+='<div class="wrapper_table" id="wrapper_'+consts[i]+'"><h3>Константа '+consts[i]+'</h3><input type="number" class="const" id="const_'+consts[i]+'" value="'+getRandomInt()+'"></div>';
    }
}

function getRandomInt() {
    var max = 99
        , min = 0;
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

function updateTable(input) {
    console.log(input);
    console.log(matrixes.length);
    var cols = input.parentElement.querySelector(".cols").value;
    var rows = input.parentElement.querySelector(".rows").value;
    if(cols===""|rows===""){
        console.error("no values");
    }
    for(var m = 0; m<matrixes.length;m++){
        var table = document.getElementById("matrix_"+matrixes[m]);
        console.log(table);
        table.innerHTML = "";
        for (var i = 0; i < rows; i++) {
            var row = table.insertRow(i);
            for (var j = 0; j < cols; j++) {
                row.insertCell(j).innerHTML = "<input type='text' value='"+getRandomInt()+"'>";
            }
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
    var tables = document.querySelectorAll(".matrix");
    var consts = document.querySelectorAll(".const");
    try{
        var result;
        result = sumMatrix(getMatrix(tables[0]), transMatrix(getMatrix(tables[1])));
        result = subMatrix(result, multMatrixNumber(Number(consts[0].value), getMatrix(tables[2])));
        result = multiplyMatrix(result, transMatrix(getMatrix(tables[3])))
        showResult(result);
    }catch(e){
        alert(e);
    }
    
}

function getMatrix(table) {
    var matrix = [];
    for (var j = 0; j < table.rows.length; j++) {
        matrix[j] = [];
        for (var k = 0; k < table.rows[j].cells.length; k++) matrix[j][k] = parseInt(table.rows[j].cells[k].querySelector("input").value);
    }
    return matrix;
}

function showResult(finalMatrix) {
    var oldTable = document.getElementById("result_view");
    if (oldTable != undefined) document.getElementById("result").removeChild(oldTable);
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
    if (oldTable != undefined) document.getElementById("result").removeChild(oldTable);
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