document.addEventListener("DOMContentLoaded", () => {
    const getBtn = document.querySelector("#mine-btn");
    getBtn.addEventListener("click", async () => {
        prevHash = "0";
        hash = "";
        while (hash != prevHash) {
            prevHash = hash;

            try {
                const response = await fetch("http://localhost:8080/mine",
                    {
                        method: "GET",
                    });
                console.log("Request sent.");
                const mineObj = await response.json();

                document.querySelector("#mine-hash").innerText = mineObj["message"];
                hash = mineObj["message"];

            } catch (error) {
                console.log("Error fetching hash");
            }
        }
    });
});