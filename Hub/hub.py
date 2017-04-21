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
        while True:
            # self.request is the TCP socket connected to the client
            self.data = self.request.recv(1024).strip()
            print("{} wrote:".format(self.client_address[0]))
            print(">>")
            print(self.data)
            # just send back the same data, but upper-cased
            #self.request.sendall(self.data.upper())

            if(self.data == b'LIGHT:?'):
                print("<<")
                self.request.send(b'LIGHT:ON\n')
                print("b'LIGHT:ON\n'")

            if(self.data == b'SWITCH:ON'):
                print("<<")
                self.request.send(b'LIGHT:ON\n')
                print("b'LIGHT:ON\n'")

            if(self.data == b'SWITCH:OFF'):
                print("<<")
                self.request.send(b'LIGHT:OFF\n')
                print("b'LIGHT:OFF\n'")


if __name__ == "__main__":
    HOST, PORT = "", 9999

    # Create the server, binding to localhost on port 9999
    server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)

    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    server.serve_forever()
