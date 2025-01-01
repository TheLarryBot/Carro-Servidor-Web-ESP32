const serverIP = "http://192.168.1.77";

document.getElementById('up').addEventListener('click', () => sendCommand('up'));
document.getElementById('down').addEventListener('click', () => sendCommand('down'));
document.getElementById('left').addEventListener('click', () => sendCommand('left'));
document.getElementById('right').addEventListener('click', () => sendCommand('right'));
document.getElementById('stop').addEventListener('click', () => sendCommand('stop'));

function sendCommand(command) {
    fetch(`${serverIP}/move?direction=${command}`)
        .then(response => response.text())
        .then(data => console.log(data))
        .catch(error => console.error('Error:', error));
}
