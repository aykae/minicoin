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
                console.log(mineObj);

                const blockDiv = document.querySelector(".block");
                if (blockDiv) {
                    console.log("In if statement");
                    blockDiv.querySelector("#number").innerText = mineObj["number"];
                    blockDiv.querySelector("#timestamp").innerText = mineObj["timestamp"];
                    blockDiv.querySelector("#hash").innerText = mineObj["hash"];
                    // const duplicateDiv = divToDuplicate.cloneNode(true);
                    // duplicateDiv.querySelector("#number").innerText = blockNum++;
                    // console.log("Duplicated Block.")
                    // document.querySelector(".block-container").appendChild(duplicateDiv);
                } else {
                    console.log("No element with id 'block' found.");
                }

                hash = mineObj["hash"];

            } catch (error) {
                console.log("Error fetching hash");
            }

            //Hacky time.wait()
            timer = 0
            while (timer < 1000000000) {
                timer++;
            }
        }
    });

    blockNum = 2;

    document.addEventListener("keydown", (event) => {
        if (event.key === " ") {
            const divToDuplicate = document.querySelector(".block");
            if (divToDuplicate) {
                const duplicateDiv = divToDuplicate.cloneNode(true);
                duplicateDiv.querySelector("#number").innerText = blockNum++;
                console.log("Duplicated Block.")
                document.querySelector(".block-container").appendChild(duplicateDiv);
            } else {
                console.log("No element with id 'block' found.");
            }
        }
    });
});