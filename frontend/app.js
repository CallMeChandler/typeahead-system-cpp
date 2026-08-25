const searchBox = document.getElementById("searchBox");
const suggestionsDiv = document.getElementById("suggestions");

searchBox.addEventListener("input", async () => {

    const query = searchBox.value.trim();

    if (query.length === 0) {
        suggestionsDiv.innerHTML = "";
        return;
    }

    const response = await fetch(`/search?q=${query}`);
    const data = await response.json();

    renderSuggestions(query, data.suggestions);
});

function renderSuggestions(query, suggestions) {

    suggestionsDiv.innerHTML = "";

    suggestions.forEach(item => {

        const div = document.createElement("div");
        div.className = "item";

        div.innerHTML = `
            <span>${item.word}</span>
            <span class="freq">${item.frequency}</span>
        `;

        div.onclick = async () => {

            await fetch("/select", {
                method: "POST",
                headers: {
                    "Content-Type": "application/json"
                },
                body: JSON.stringify({
                    query,
                    word: item.word
                })
            });

            searchBox.value = item.word;
            suggestionsDiv.innerHTML = "";
        };

        suggestionsDiv.appendChild(div);
    });
} 