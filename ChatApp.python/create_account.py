from tkinter import *
from tkinter import messagebox
import os
import sys

class Create_Account:

    def check_users_exists(self, username):
        file_path = "user_accounts/{}".format(username)
        return file_path

    def __init__(self):
        self.create_root = Toplevel()
        self.new_username_label = None
        self.new_username_input = None
        self.new_password_label = None
        self.new_password_input = None

        self.create_window()

    # Create account window starts here!
    def create_window(self):
        self.create_root.title("Create Account")
        self.create_root.geometry('855x830+875+150')

        self.create_root.configure(background="light blue")

        self.create_login_information()

        self.create_root.mainloop()

    # Creating username & password here!
    def create_login_information(self):
        self.new_username_label = Label(self.create_root)
        self.new_username_label["text"] = "New Username"
        self.new_username_label["bg"] = "light blue"
        self.new_username_label.pack(side=TOP)

        self.new_username_input = Entry(self.create_root)
        self.new_username_input.pack(side=TOP)

        self.new_password_label = Label(self.create_root)
        self.new_password_label["text"] = "New Password"
        self.new_password_label["bg"] = "light blue"
        self.new_password_label.pack(side=TOP)

        self.new_password_input = Entry(self.create_root)
        self.new_password_input["show"] = "*"
        self.new_password_input.pack(side=TOP)

        self.save_button = Button(self.create_root)
        self.save_button["text"] = "Save Changes"
        self.save_button["command"] = lambda: self.save_username_password()
        self.save_button.pack(side=TOP)

        self.cancel_button = Button(self.create_root)
        self.cancel_button["text"] = "Discard Changes"
        self.cancel_button["command"] = lambda: self.close_window()
        self.cancel_button.pack()

    def save_username_password(self):

        if os.path.isfile(self.check_users_exists(self.new_username_input.get())):
            messagebox.askokcancel("Username Exists", "This username already exists")
        else:
            with open(self.check_users_exists(self.new_username_input.get()), 'wb') as binary_File:
                binary_File.write(str("Username: {}".format(self.new_username_input.get())).encode())
                binary_File.write(str("\nPassword: {}".format(self.new_password_input.get())).encode())
                binary_File.close()
                self.create_root.destroy()
                sys.exit()

    def close_window(self):
        self.create_root.destroy()
        sys.exit()