document.addEventListener("DOMContentLoaded", () => {
    const getBtn = document.querySelector("#mine-btn");
    getBtn.addEventListener("click", async () => {
        blockNum = 0;
        const blockDiv = document.querySelector(".block");
        blockDupe = null;

        while (1) {
            try {
                const response = await fetch("http://localhost:8080/mine",
                    {
                        method: "GET",
                    });
                console.log("Request sent.");
                const mineObj = await response.json();
                console.log(mineObj);
                    
                if (mineObj["number"] != blockNum) {

                    // Set prev block's winning hash
                    if (blockDupe) {
                        blockDupe.querySelector("#hash").innerText = mineObj["prevHash"];
                    }
                    
                    // Create new block
                    blockDupe = blockDiv.cloneNode(true);
                    
                    // Initialize values
                    blockDupe.style.display = "block";
                    blockNum = mineObj["number"];
                    blockDupe.querySelector("#number").innerText = blockNum;
                    blockDupe.querySelector("#timestamp").innerText = mineObj["timestamp"];
                    blockDupe.querySelector("#hash").innerText = mineObj["hash"];
                    
                    //Prepend block to chain
                    document.querySelector(".block-container").prepend(blockDupe);
                }
                else {
                    blockDupe.querySelector("#hash").innerText = mineObj["hash"];
                }
            }
            catch (error) {
                console.log("Error fetching hash");
            }

            //Hacky time.wait()
            timer = 0;
            while (timer < 100000000) {
                timer++;
            }
        }
    });
});