class Car{
    constructor(company,colour){
        this.company=company;
        this.colour=colour;
    }
    getDetails(){
        console.log("The car is of "+this.company+" company and the colour is "+this.colour);    
    }
}

const car1 = new Car("Toyota", "Red");
const car2 = new Car("Honda", "Blue");

car1.getDetails(); 
car2.getDetails();