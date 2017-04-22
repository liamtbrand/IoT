'''
Main Hub software for IoT.
Written By Liam T. Brand.
'''

from http.server import BaseHTTPRequestHandler, HTTPServer
import socketserver
import time
import _thread

class MyTCPHandler(socketserver.BaseRequestHandler):
    """
    The RequestHandler class for our server.

    It is instantiated once per connection to the server, and must
    override the handle() method to implement communication to the
    client.
    """

    def handle(self):
        while True:
            if(toSend == True):
                self.request.send(message)
                print(message)
                message = ""
                toSend = False
            '''
            else:
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
            '''

class S(BaseHTTPRequestHandler):
    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def do_GET(self):
        self._set_headers()
        message = self.rfile.read()
        print('\n')
        print('>>')
        print(message)
        print('\n')
        toSend = True
        self.wfile.write(b'OK')

    def do_HEAD(self):
        self._set_headers()

    def do_POST(self):
        # Doesn't do anything with posted data
        self._set_headers()
        #self.wfile.write("hi")
        message = self.rfile.read()
        print('\n')
        print('>>')
        print(message)
        print('\n')
        toSend = True
        self.wfile.write(b'OK')

message = b''
toSend = False

def run():
    HOST, PORT = "", 9999

    # Create the server, binding to localhost on port 9999
    server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)
    server.serve_forever()

if __name__ == "__main__":

    server_address = ('', 8081)
    httpd = HTTPServer(server_address, S)
    _thread.start_new_thread( httpd.serve_forever, () )

    print("Running.")
    run()
