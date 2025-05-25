window.alert("This is a webpage")

function changeText() {
    const dynamicText = document.getElementById("dynamic-text");

    // Change the content dynamically
    if (dynamicText.innerHTML === "Click the button to change this text dynamically!") {
        dynamicText.innerHTML = "You've changed the text! Try clicking again!";
    } else {
        dynamicText.innerHTML = "Click the button to change this text dynamically!";
    }
}




