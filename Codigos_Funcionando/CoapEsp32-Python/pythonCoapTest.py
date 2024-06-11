import asyncio
from aiocoap import *

async def toggle_led(state):
    # Estado do LED: "1" para ligar e "0" para desligar
    uri = "coap://192.168.1.71/light"
    
    # Criando uma mensagem de PUT com o estado desejado
    request = Message(code=PUT, payload=state.encode('utf-8'))
    request.set_request_uri(uri)

    protocol = await Context.create_client_context()

    try:
        response = await protocol.request(request).response
        print(f'Received response: {response.payload.decode()}')
    except Exception as e:
        print(f'Failed to toggle LED: {e}')

async def main():
    while True:
        command = input("Digite 'ligar' para acender o LED ou 'desligar' para apagar o LED: ")
        if command.lower() == 'ligar':
            await toggle_led('1')
        elif command.lower() == 'desligar':
            await toggle_led('0')
        else:
            print("Comando inválido.")

# Inicia o loop assíncrono
if __name__ == "__main__":
    asyncio.run(main())
