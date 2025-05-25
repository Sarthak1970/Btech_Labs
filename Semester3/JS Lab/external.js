// //write a js program to implement comparison and control flow

let sum=0
for(let i=1;i<=5;i++){
    sum+=i;
}
console.log(`sum of first five numbers is ${sum}`)


const readline = require('readline');
const r1 = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
});

var x;
var y;

r1.question('Enter the first number: ', input1 => {
    x = parseInt(input1);
    r1.question('Enter the second number: ', input2 => {
        const y = parseInt(input2);
        if(x>y){
            console.log(`${x} is greater than ${y}`);
        } 
        else if(x<y){
            console.log(`${y} is greater than ${x}`);
        } 
        else{
            console.log(`Both numbers are equal`);
        }
        r1.close();
    });
});


