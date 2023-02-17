from tkinter import *
from tkinter import messagebox
# import ImageTk, Image
import os
import sys
# from Chat_App.client import Client
import client
# from Chat_App.create_account import Create_Account
import create_account

class Login_Page:
    # img_path = "images/Sword Icon.png"
    # img_path = "/images/Sword Icon"

    # Check if users files exists here!
    def username_file_path(self, username):
        file_path = f"user_accounts/{username}"
        return file_path

    def __init__(self, master):
        self.client_tkinter_root = master
        # self.my_imgs = ImageTk.PhotoImage(file=self.img_path)

        self.login_window()

    def login_window(self):
        self.client_tkinter_root.title("Login")
        self.client_tkinter_root.geometry('855x830+875+150')
        self.client_tkinter_root.configure(width=400, height=500, bg="light blue")

        # self.background_images()
        self.login_widgets_layout()

    # def background_images(self):
    #    background_images = Label(self.client_tkinter_root)
    #    background_images['image'] = self.my_imgs
    #    background_images['bg'] = 'light blue'
    #    # relx goes to the right and top
    #    # rely goes to the left and bottom
    #    background_images.place(relx=0.5, rely=0.4, anchor=CENTER)

    def login_widgets_layout(self):
        self.contain_username = StringVar()

        # Username Label & Input
        username_label = Label(self.client_tkinter_root)
        username_label["text"] = "Username"
        username_label["bg"] = "light blue"
        username_label["font"] = ("Helvetica", 13, "bold")
        # username_label.grid(row=1, column=15)
        username_label.place(relx=0.3, rely=0.7)
        # username_label.grid(row=1, column=0, padx=10, pady=10, columnspan=5)

        self.username_input = Entry(self.client_tkinter_root)
        self.username_input['textvariable'] = self.contain_username
        self.username_input.place(relx=0.4, rely=0.7)
        # self.username_input.grid(row=1, column=1, padx=10, pady=10, columnspan=10)

        # Password Label & Input!
        password_label = Label(self.client_tkinter_root)
        password_label["text"] = "Password"
        password_label["bg"] = "light blue"
        password_label["font"] = ("Helvetica", 13, "bold")
        password_label.place(relx=0.3, rely=0.8)
        # password_label.grid(row=2, column=0, padx=10, pady=10, columnspan=5) # NOTE: columnspan is like moving the column a little bit across the grid!

        self.password_input = Entry(self.client_tkinter_root)
        self.password_input['show'] = "*"
        self.password_input.place(relx=0.4, rely=0.8)
        # self.password_input.grid(row=2, column=1, pady=10, columnspan=10)

        self.password_input.bind('<Return>', self.password_input_binded)

        # Login Button here!
        login_button = Button(self.client_tkinter_root)
        login_button['text'] = "Login"
        login_button['command'] = lambda: self.check_username()
        login_button.place(relx=0.4, rely=0.9)
        # login_button.grid(row=3, column=1, padx=10, pady=10, columnspan=5)

        # Leave Login Button Here!
        cancel_button = Button(self.client_tkinter_root)
        cancel_button['text'] = "Leave Login"
        cancel_button['command'] = lambda: self.close_window()
        cancel_button.place(relx=0.5, rely=0.9)
        # cancel_button.grid(row=3, column=2, padx=10, pady=10, columnspan=10)

        create_account_button = Button(self.client_tkinter_root)
        create_account_button['text'] = 'Register'
        create_account_button['command'] = lambda: self.create_account()
        # RELX moves to the right or the left
        # RELY moves up or down
        create_account_button.place(relx=0.4, rely=0.97)

    # Check if username exists!
    def check_username(self):
        if os.path.isfile(self.username_file_path(self.username_input.get())):
            self.verify_password()
        else:
            messagebox.showerror("Username not found", "Username has not been found!")

    def password_input_binded(self, event):
        if os.path.isfile(self.username_file_path(self.username_input.get())):
            self.verify_password()
        else:
            messagebox.showerror("Username not found", "Username has not been found!")


    def verify_password(self):
        with open(self.username_file_path(self.username_input.get()), 'rb') as binaryFile:
            read_password = binaryFile.read().decode()

            if self.password_input.get() in read_password:
                # messagebox.askokcancel("LOGGED IN", "MESSAGE SAYS YOU LOGGED IN!")
                self.start_chat_room()
            else:
                messagebox.showerror("Password not found!", "Password has not been found!")
        binaryFile.close()

    def close_window(self):
        self.client_tkinter_root.destroy()
        sys.exit()

    def start_chat_room(self):
        self.client_tkinter_root.destroy()
        client.Client(self.contain_username)

    def create_account(self):
        self.client_tkinter_root.destroy()
        create_account.Create_Account()

# def Main():
#    root = Toplevel()
#    Login_Page(root)
#    root.mainloop()

# if __name__ == "__main__":
#    Main()