'''
Main Hub software for IoT.
Written By Liam T. Brand.
'''

import socketserver
import time

class MyTCPHandler(socketserver.BaseRequestHandler):
    """
    The RequestHandler class for our server.

    It is instantiated once per connection to the server, and must
    override the handle() method to implement communication to the
    client.
    """

    def handle(self):
        # self.request is the TCP socket connected to the client
        self.data = self.request.recv(1024).strip()
        print("{} wrote:".format(self.client_address[0]))
        print(">>")
        print(self.data)
        # just send back the same data, but upper-cased
        #self.request.sendall(self.data.upper())

        print("<<")
        self.request.send(b'LIGHT:ON\n')
        print("b'LIGHT:ON\n'")

        while True:
            time.sleep(5)
            self.request.send(b'LIGHT:OFF\n')
            time.sleep(5)
            self.request.send(b'LIGHT:ON\n')

        #self.request.sendall();

if __name__ == "__main__":
    HOST, PORT = "", 9999

    # Create the server, binding to localhost on port 9999
    server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)

    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    server.serve_forever()
