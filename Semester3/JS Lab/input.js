const readline=require('readline');
const r1=readline.createInterface({
    input:process.stdin,
    output:process.stdout,
});

r1.question('Enter your name:',input=>{
    if(input){
        console.log(`Hello ${input}`);
    }
    else{
        console.log('You have not entered your name');
    }
    r1.close();
})