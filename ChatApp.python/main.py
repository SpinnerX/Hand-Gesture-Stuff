from tkinter import *
import login

def Main():
    root = Toplevel()
    login.Login_Page(root)
    root.mainloop()

if __name__ == "__main__":
    Main()