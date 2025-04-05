let search_field = document.getElementById('search_field');
const server_url = "http://localhost:8089";

document.getElementById('search_button').addEventListener('click', searchServerData);

function searchServerData() {
    fetch(server_url)
	.then(response => response.arrayBuffer())
	.then(buffer => {
	    const byteArray = new Uint8Array(buffer);
	    console.log(byteArray);
	    
	    const text = new TextDecoder().decode(byteArray);
	    console.log(text);
	    
	    let html_results = document.getElementById('search_results');
	    const results = text.split("|");
	    results.forEach((result) => {
		html_results.innerHTML += `<span class='result'>${result}</span>`;
	    })
	})
	.catch(error => console.error('Error fetching data:', error));
}
