document.addEventListener("DOMContentLoaded", function() {
    const form = document.getElementById("input-form");
    const input = document.getElementById("input-message");
    const log = document.getElementById("chat-window");
  

    form.addEventListener("submit", function(event) {
      event.preventDefault();
  
      const query = input.value.trim();
  
      if (query !== "") {
        logMessage(`You: ${query}`);
  
        fetch("/chat", {
          method: "POST",
          headers: {
            "Content-Type": "application/x-www-form-urlencoded",
          },
          body: `query=${encodeURIComponent(query)}`,
        })
          .then((response) => response.json())
          .then((data) => {
            const response = data.response;
            logMessage(`CarboSmart: ${response}`);
          })
          .catch((error) => {
            console.error(error);
          });
  
        input.value = "";
      }
    });
  



    function logMessage(message) {
      const entry = document.createElement("div");
      entry.innerText = message;
      log.appendChild(entry);
    }
  });
  