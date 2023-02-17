from threading import *
from socket import *
from tkinter import *
from tkinter import messagebox
from time import sleep

class Client:

    def __init__(self, username):
        self.contain_username = username
        self.Buffer_Size = 1024
        self.Format = 'utf-8'
        self.list_of_clients = []
        self.recent_messages = None

        self.start_client_connections()
        self.start_chat_room()


    def start_client_connections(self):
        self.client_socket_root = socket(AF_INET, SOCK_STREAM)

        PORT = 1234
        # SERVER = gethostbyname(gethostname())
        SERVER = '127.0.0.1'

        self.client_address = (SERVER, PORT)

        self.client_socket_root.connect(self.client_address)

    def start_chat_room(self):
        self.chat_window_layout()
        self.chat_message_input()
        self.waiting_to_connect_threads()

    def waiting_to_connect_threads(self):
        connection_threads = Thread(target=self.messages_from_server, args=(self.client_socket_root,))
        connection_threads.start()

    def messages_from_server(self, client_socket):
        stay_connected = True

        while stay_connected:
            buffered_data = client_socket.recv(self.Buffer_Size)

            if not buffered_data:
                break
            self.chat_message_LOGS.insert(END, buffered_data.decode(self.Format) + '\n')
            self.chat_message_LOGS.yview(END)
        client_socket.close()

    # Main Chat Window Frame
    def chat_window_layout(self):
        chat_frame = Frame()

        joining_message = "{} has joined the chat!\n".format(self.contain_username.get())
        self.client_socket_root.send(joining_message.encode(self.Format))

        username_label = Label(chat_frame)
        username_label['textvariable'] = "Username: ".format(self.contain_username.get())
        username_label.pack(side=TOP, anchor=E)

        chat_message_label = Label(chat_frame)
        chat_message_label['text'] = "Chat Messages"
        chat_message_label.pack(side=TOP, anchor=W)

        logout_button = Button(chat_frame)
        logout_button['text'] = "Logout"
        logout_button['command'] = lambda: self.close_window()
        logout_button.pack(side=TOP, anchor=E)

        self.chat_message_LOGS = Text(chat_frame)
        self.chat_message_LOGS['width'] = 60
        self.chat_message_LOGS['height'] = 20

        chat_scrollbar = Scrollbar(chat_frame)
        chat_scrollbar['command'] = self.chat_message_LOGS.yview
        chat_scrollbar['orient'] = VERTICAL

        self.chat_message_LOGS.config(yscrollcommand=chat_scrollbar.set)
        self.chat_message_LOGS.bind('<Enter>', lambda e: 'break')

        self.chat_message_LOGS.pack(side=LEFT)

        chat_scrollbar.pack(side=LEFT, fill=Y)

        chat_frame.pack(side=TOP)

    # Handling chat messages input received and sent here!
    def chat_message_input(self):
        message_frame = Frame()

        message_label = Label(message_frame)
        message_label['text'] = "Enter Messages Here:"
        message_label.pack(side=TOP, anchor=W)

        self.message_input = Text(message_frame)
        self.message_input['width'] = 60
        self.message_input['height'] = 8

        message_scrollbar = Scrollbar(message_frame)
        message_scrollbar['command'] = self.message_input.yview
        message_scrollbar['orient'] = VERTICAL

        self.message_input.config(yscrollcommand=message_scrollbar.set)
        self.message_input.pack(side=LEFT)

        message_scrollbar.pack(side=LEFT, fill=Y)

        self.message_input.bind('<Return>', self.users_presses_enter_key)

        message_frame.pack(side=TOP)

    # Executed, when users presses the enter key!
    def users_presses_enter_key(self, event):

        if len(self.contain_username.get()) == 0:
            messagebox.showerror("Enter your name", "Enter your name to send a message")
            return

        # Sending sending messages here
        self.send_messages()
        # Clear messages in entry box!
        self.clear_messages()

    # Clear chat messages
    def clear_messages(self):
        self.message_input.delete(1.0, END)

    # Send the user chat messages
    def send_messages(self):
        messengers_name = self.contain_username.get().strip() + ": "

        message_data = self.message_input.get(1.0, END).strip()

        message_sent = (messengers_name + message_data).encode(self.Format)

        self.chat_message_LOGS.insert(END, message_sent.decode(self.Format) + '\n')
        self.chat_message_LOGS.yview(END)

        self.client_socket_root.send(message_sent)
        self.message_input.delete(1.0, END)

        return 'break'

    def close_window(self):
        # Disconnecting messages are being sent to the server!
        disconnecting_message = "[DISCONNECTING] Disconnecting from server...."
        self.client_socket_root.send(bytes(disconnecting_message, self.Format))
        sleep(1)
        disconnecting_message_2 = "{} left the chat".format(self.contain_username.get())
        self.client_socket_root.send(bytes(disconnecting_message_2, self.Format))
        self.client_socket_root.close()
        sys.exit()