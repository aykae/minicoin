document.addEventListener("DOMContentLoaded", () => {
    const getBtn = document.querySelector("#mine-btn");
    getBtn.addEventListener("click", async () => {
        prevHash = "0";
        hash = "";
        while (hash != prevHash) {
            prevHash = hash;

            try {
                const response = await fetch("http://127.0.0.1:8080/mine",
                    {
                        method: "GET",
                    });
                console.log("Request sent.");
                const mineObj = await response.json();

                const blockDiv = document.querySelector(".block");
                if (blockDiv) {
                    blockDiv.querySelector("#number") = blockNum;
                    blockDiv.querySelector("#timestamp") = mineObj["timestamp"];
                    blockDiv.querySelector("#timestamp") = mineObj["hash"];
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
        }
    });
});

// document.addEventListener("DOMContentLoaded", () => {
//     blockNum = 2;

//     document.addEventListener("keydown", (event) => {
//         if (event.key === " ") {
//             const divToDuplicate = document.querySelector(".block");
//             if (divToDuplicate) {
//                 const duplicateDiv = divToDuplicate.cloneNode(true);
//                 duplicateDiv.querySelector("#number").innerText = blockNum++;
//                 console.log("Duplicated Block.")
//                 document.querySelector(".block-container").appendChild(duplicateDiv);
//             } else {
//                 console.log("No element with id 'block' found.");
//             }
//         }
//     });
// });