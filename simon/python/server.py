import socket

# Server configuration
HOST = "0.0.0.0"  # Listen on all available network interfaces
PORT = 8080

# Create a socket and bind it to the address and port
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(1)

print("Server started on port 8080...")

# Variable to keep track of button presses
press_count = 0

# Main server loop
while True:
    try:
        client_socket, client_address = server_socket.accept()
        print(f"Connection from {client_address}")

        # Read the client's request
        request = client_socket.recv(1024).decode('utf-8')
        print(f"Received request: {request}")

        # Handle POST request to increment button press count
        if "POST /button_pressed" in request:
            press_count += 1
            print(f"Button pressed {press_count} times!")
            response = "HTTP/1.1 200 OK\r\n\r\nButton press counted"
            client_socket.sendall(response.encode('utf-8'))

        # Handle GET request for the main webpage
        elif "GET / " in request or "GET /HTTP" in request:
            response_body = f"""
            <html>
                <head><title>Pico W Button Pressed Counter</title>
                    <script>
                        function fetchButtonStatus() {{
                            fetch("/status")
                                .then(response => response.text())
                                .then(data => {{
                                    document.getElementById("button_status").innerText = data;
                                }})
                                .catch(error => {{
                                    console.error("Error:", error);
                                }});
                        }}

                        setInterval(fetchButtonStatus, 1000);  // Update every second
                    </script>
                </head>
                <body>
                    <h1>Pico W Button Pressed Count</h1>
                    <p>Button presses so far: <span id="button_status">{press_count}</span></p>
                </body>
            </html>
            """
            response_headers = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
            response = response_headers + response_body
            client_socket.sendall(response.encode('utf-8'))

        # Handle GET request to fetch the button press count
        elif "GET /status" in request:
            response = f"HTTP/1.1 200 OK\r\n\r\n{press_count}"
            client_socket.sendall(response.encode('utf-8'))

        # Close the client connection
        client_socket.close()

    except KeyboardInterrupt:
        print("Server stopped")
        break

# Close the server socket when exiting
server_socket.close()

