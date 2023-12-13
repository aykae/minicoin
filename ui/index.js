document.addEventListener("DOMContentLoaded", function() {
    const genBtn = document.querySelector("#mine-btn");
    window.addEventListener('keydown', async function(event) {
        if (event.key === ' ') {
            try {
                const response = await fetch("http://localhost:8080/mine",
            {
                method: "GET",
            });
            console.log("Request sent.");
            const mineObj = await response.json();
            console.log(mineObj);

            document.querySelector("#mine-hash").innerText = mineObj["message"];

            } catch (error) {
                console.log("Error fetching hash")
            }
        }
    });
});
//     genBtn.addEventListener("click", async () => {
//         try {
//             const response = await fetch("http://localhost:8080/hi",
//             {
//                 method: "GET",
//             });
//             console.log("Request sent.");
//             console.log(response);
//             // console.log(await response.json());
            
//             document.querySelector("#mine-hash").innerText = mineObj[""];

//         } catch (error) {
//             console.log("Error fetching hash")
//         }
//     });
// });