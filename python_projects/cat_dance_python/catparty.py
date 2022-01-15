"""
This is a simple user interface, where you have an image of a cat and some
buttons to change the image. By clicking the different buttons the user can
add a hat and balloons and tiny cats to the image. The user can click a button
only once then it gets deactivated.

The last button will start an animation. If the user clicks 'say goodbye' on
the main window a goodbye message will be displayed and then the program will
end.
"""

from tkinter import *
import time


class CatDance:
    """
    This class defines the CatDance interface. It adds the images and the
    defines and adds the buttons to the main window. This class also defines
    what the different buttons do.
    """
    def __init__(self):

        self.__crazycounter = 0

        self.__mainwindow = Tk()
        self.__mainwindow.configure(background="light blue")


        self.__cat = PhotoImage(file="cat.png")
        self.__cat_hat = PhotoImage(file="cat+hat.png")
        self.__cat_hat_balloons = PhotoImage(file="cat+hat+balloons.png")
        self.__cat_hat_balloons_tiny = PhotoImage(
            file="cat+hat+balloons+tiny.png")
        self.__goodbye = PhotoImage(file="goodbye.png")

        self.__crazy_animation = []
        for photo in ["crazy1.png", "crazy2.png", "crazy3.png",
                      "crazy4.png", "crazy5.png", "crazy6.png",
                      "crazy7.png", "crazy8.png", "crazy9.png",
                      "crazy10.png"]:
            self.__crazy_animation.append(PhotoImage(file=photo))


        self.__picture_label = Label(self.__mainwindow, image=self.__cat)
        self.__cat_hat_button = Button(self.__mainwindow,
                                        text="add a hat",
                                        command=self.add_hat,
                                        background="orange",
                                        foreground="white")
        self.__cat_hat_balloons_button = Button(self.__mainwindow,
                                        text="add a hat & balloons",
                                        command=self.add_hat_balloons,
                                        background="orange",
                                        foreground="white")
        self.__cat_hat_balloons_tiny_button = Button(self.__mainwindow,
                                        text="add a hat & balloons & tiny cats"
                                        , command=self.add_hat_balloons_tiny,
                                        background="orange",
                                        foreground="white")
        self.__gocrazy_button = Button(self.__mainwindow, text="go crazy",
                                        command=self.goCRAZY,
                                        background="orange",
                                        foreground="white")
        self.__end_button = Button(self.__mainwindow, text="say goodbye",
                                        command=self.end,
                                        background="orange",
                                        foreground="white")

        self.__picture_label.grid(row=1, column=2, sticky=E)
        self.__cat_hat_button.grid(row=4, column=2, sticky=W+E, columnspan=2)
        self.__cat_hat_balloons_button.grid(row=5, column=1, sticky=W+E,
                                            columnspan=2)
        self.__cat_hat_balloons_tiny_button.grid(row=6, column=1, sticky=W+E,
                                                 columnspan=2)
        self.__gocrazy_button.grid(row=7, column=1, sticky=W+E, columnspan=2)
        self.__end_button.grid(row=9, column=2, sticky=E+W, columnspan=2)

        self.__mainwindow.mainloop()

    def end(self):
        """
        Displays an end message with a black background and then ends the
        program.
        """

        time.sleep(0.5)
        self.__end_button.destroy()
        self.__gocrazy_button.destroy()
        self.__cat_hat_button.destroy()
        self.__cat_hat_balloons_button.destroy()
        self.__cat_hat_balloons_tiny_button.destroy()

        self.__picture_label.configure(image=self.__goodbye)
        self.__mainwindow.configure(background="black")
        self.__mainwindow.update_idletasks()
        time.sleep(2)
        self.__mainwindow.destroy()


    def add_hat(self):
        """
        Changes the image that is being displayed on the picture_label to a cat
        with a hat on. Also it disables the button 'add a hat' so it cant be
        clicked twice.
        """

        self.__cat_hat_button.configure(state=DISABLED)
        self.__picture_label.configure(image=self.__cat_hat)


    def add_hat_balloons(self):
        """
        Changes the image that is being displayed on the picture_label to a
        cat with a hat and some balloons. Also it disables the button 'add a
        hat & balloons' so it cant be clicked twice.
        """

        self.__cat_hat_balloons_button.configure(state=DISABLED)
        self.__picture_label.configure(image=self.__cat_hat_balloons)


    def add_hat_balloons_tiny(self):
        """
        Changes the image that is being displayed on the picture_label to a
        cat with a hat, some balloons and other tiny cats. Also it disables
        the button 'add a hat & balloons & tiny cats' so it cant be clicked
        twice.
        """

        self.__cat_hat_balloons_tiny_button.configure(state=DISABLED)
        self.__picture_label.configure(image=self.__cat_hat_balloons_tiny)



    def goCRAZY(self):
        """
        Creates an animation by changing the displayed picture_label quickly.
        """

        self.__gocrazy_button.configure(state=DISABLED)
        self.__picture_label.configure(
            image=self.__crazy_animation[self.__crazycounter % 2])
        self.__crazycounter += 1
        self.__mainwindow.after(200, self.goCRAZY)


def main():
    CatDance()


if __name__ == "__main__":
    main()