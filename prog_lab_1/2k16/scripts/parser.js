function parseMath(inputString){
    console.log(inputString);
    var expression = new Expression();
}
var operators = {
    "(":0,
    ")":0,
    "^":1,
    "*":2,
    "/":2,
    "+":3,
    "-":3;
}
function Value(){
    this.name = undefined;
    this.number = 0;
}
function Operator(){
    this.name = undefined;
    this.priority = undefined;
}
function Expression(){
    this.name = undefined;
    this.value = null;
    this.exp1 = null;
    this.operator = null;
    this.exp2 = null;
    this.result = 0;
}