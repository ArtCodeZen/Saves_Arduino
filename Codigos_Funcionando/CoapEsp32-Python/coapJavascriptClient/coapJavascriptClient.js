const coap = require('coap'); // Importa a biblioteca CoAP
const readline = require('readline'); // Para ler a entrada do usuário

// Função para alternar o estado do LED
async function toggleLED(state) {
    // Estado do LED: "1" para ligar e "0" para desligar
    
    
    return new Promise((resolve, reject) => {
        // Configura a mensagem CoAP para envio com método PUT
        const req = coap.request({
            method: 'PUT',
            confirmable: true,
            hostname: '192.168.1.79',
            pathname: '/light',
            port: 5683
        });

        // Adiciona o estado desejado no payload
        req.write(state);

        // Lida com a resposta do servidor
        req.on('response', (res) => {
            console.log(`Resposta recebida: ${res.payload.toString()}`);
            resolve(res.payload.toString());
        });

        // Lida com erros na requisição
        req.on('error', (err) => {
            console.error(`Falha ao alternar o LED: ${err}`);
            reject(err);
        });

        // Envia a mensagem
        req.end();
    });
}

// Função principal que solicita a entrada do usuário
async function main() {
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });

    while (true) {
        // Solicita comando ao usuário
        await new Promise((resolve) => {
            rl.question("Digite 'ligar' para acender o LED ou 'desligar' para apagar o LED: ", async (command) => {
                if (command.toLowerCase() === 'ligar') {
                    await toggleLED('1');
                } else if (command.toLowerCase() === 'desligar') {
                    await toggleLED('0');
                } else {
                    console.log("Comando inválido.");
                }
                resolve();
            });
        });
    }
}

// Executa a função principal
main().catch(console.error);
