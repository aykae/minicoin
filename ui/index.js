document.addEventListener("DOMContentLoaded", () => {
    isMining = false;
    document.addEventListener("keypress", async (event) => {
        if (event.key === 'Enter' && !isMining) {
            isMining = true;

            blockNum = 0;
            const blockDiv = document.querySelector(".block");
            blockClone = null;
            const chain = document.querySelector("#chain");

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
                        if (blockClone) {
                            blockClone.querySelector("#hash").innerText = mineObj["prevHash"];
                        }
                        
                        // Create new block
                        blockClone = blockDiv.cloneNode(true);
                        
                        // Initialize values
                        blockClone.style.display = "block";
                        blockNum = mineObj["number"];
                        blockClone.querySelector("#number").innerText = blockNum;
                        blockClone.querySelector("#timestamp").innerText = mineObj["timestamp"];
                        blockClone.querySelector("#hash").innerText = mineObj["hash"];
                        
                        //Prepend block to chain
                        chainClone = chain.cloneNode(false);
                        document.querySelector(".block-container").prepend(chainClone);
                        document.querySelector(".block-container").prepend(blockClone);
                    }
                    else {
                        blockClone.querySelector("#hash").innerText = mineObj["hash"];
                    }
                }
                catch (error) {
                    console.log("Error fetching hash");
                }

                //Hacky time.wait() to slowdown API calls
                timer = 0;
                while (timer < 100000000) {
                    timer++;
                }
            }
        }
        else if (event.key === 'Enter' && isMining) {
            isMining = false;
        }
    });
});