from socket import *
from threading import Thread
from threading import activeCount
from time import sleep
from termcolor import colored
import os
import sys

class Host:

    # Constructor
    def __init__(self):
        self.list_of_clients = []
        self.recent_msg_received = ""
        self.Buffer_Size = 1024
        self.Format = "utf-8"
        self.Max_Connected = 5
        self.start_server()     # Starting server here!

    def start_server(self):
        start_text = "[STARTING] Server ON"
        color_text = colored(start_text, color="green")

        print(color_text)
        sleep(1)
        self.server_connecting()

    def server_connecting(self):
        self.server_root_socket = socket(AF_INET, SOCK_STREAM)

        PORT = 1234
        HOST_SERVER = gethostbyname(gethostname())

        self.host_address = (HOST_SERVER, PORT)

        self.server_root_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
        self.server_root_socket.bind(self.host_address)

        # Color-Coded the text here! with termcolor!
        wait_text = "[WAITING] Waiting for connections"
        color_text = colored(wait_text, color="green")
        print(color_text)

        self.server_root_socket.listen(self.Max_Connected)
        # Start receiving messages through this thread
        self.threads_receive_message()

    def threads_receive_message(self):
        amt_of_threads = 1

        while amt_of_threads:
            client = server_socket, (self.host_address) = self.server_root_socket.accept()

            # APPENDING USERS HERE!
            self.appending_users(client)

            print("[CONNECTED] Connected to {}".format(self.host_address))

            # Start connection thread here, when
            # user makes the successfully makes connection!
            connection_thread = Thread(target=self.receiving_msg, args=(server_socket,))
            connection_thread.start()

            # Counting how many users are connected!
            print(colored("There are {} users connected to the server!".format(activeCount()-1), color="blue"))

    # Adding new users to the connection of the server!
    def appending_users(self, clients_users):
        if clients_users not in self.list_of_clients:
            self.list_of_clients.append(clients_users)

    # Method for receiving messages
    def receiving_msg(self, server_socket):
        stay_connected = True

        while stay_connected:
            receiving_buffering_data = server_socket.recv(self.Buffer_Size)

            if not receiving_buffering_data:
                break

            self.recent_msg_received = receiving_buffering_data.decode(self.Format)
            # BROADCAST MESSAGES HERE!
            self.show_message_to_clients(server_socket)
        server_socket.close()

    # Show thee message being sent to the user!
    def show_message_to_clients(self, sender_sockets):
        for client in self.list_of_clients:
            users_sockets, (self.host_address) = client
            if users_sockets is not sender_sockets:
                users_sockets.sendall(self.recent_msg_received.encode(self.Format))

if __name__ == "__main__":
    Host()