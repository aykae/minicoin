document.addEventListener("DOMContentLoaded", function() {
    const genBtn = document.querySelector("#mine-btn");
    genBtn.addEventListener("click", async () => {
        try {
            const response = await fetch("http://localhost:8080/mine",
            {
                method: "GET",
            });
            const mineObj = await response.json();
            console.log(sentObj);
            
            document.querySelector("#mine-hash").innerText = mineObj[""];

        } catch (error) {
            console.log("Error fetching hash")
        }
    });
});