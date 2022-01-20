/*minsweeper_gui
*
*
*Descripiton:
*
*Creates the GUI for the minsweeper game.
*
*How to play:
*
*To play the game in the gui, first you can set a seed value. If no seed value
*is set the game goes with the seed value of 0. After you've set the seed value
*the game starts when the 'start game' button is clicked. After the game starts
*a timer will start and show how much time has passed.
*                              
*By clicking the buttons on the gameboard you can choose, from the open/flag 
*image button, if youd like to open the square or put a flag on it. Opening the
*square can open 1 square or multiple squares if theres no mine under it or 
*near it. If there is a mine under it the game is over and you can restart it 
*again from the restart button. If you choose to place a flag, an image of a
*flag will appear in the square. If you want to delete the flag, click the same
*square again. You can not open a flagged square.
*         
*The game ends in victory when you've opened all the squares that dont have
*mines and flagged all the mines correctly. You can again reset the game by
*clicking the 'restart' button. After the game ends the timer stops and you can
*see how much time passed while you were playing the game.
*
* */

#include "mainwindow.hh"
#include "gameboard.hh"
#include "square.hh"
#include "ui_mainwindow.h"

#include <iostream>

const int TimerIntervalMS = 1000;

// Sets up the gui and changes the central widgets background to pink.
// Initializes the widgets seen in the gui window
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setStyleSheet("background-color: pink");

    init_window_objects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Creates the timer for the game
// Sets the timer so, that it has separate minute and second widgets that are
// linked to eachother and displays the numbers on the widgets.
void MainWindow::on_sec_timer()
{
    int second = timer_sec_->intValue();
    int minute = timer_min_->intValue();

    ++second;
    if (second == 60) {
        second = 0;
        ++minute;
    }

    timer_min_->display(minute);
    timer_sec_->display(second);
}

// When the player changes the seed spin boxes value, the function will update
// the new value to <unsigned int seed_value_>
void MainWindow::seed_spin_box_value_changed()
{
    seed_value_ = seed_spin_box_->value();
}

// Sets the <QSpinBox seed_spin_box> and <QPushButton start_game_button> so
// that they cannot be clicked while the game runs.
// Gives the value of <unsigned int seed_value_> to initialize the board in
// the GameBoard class.
// Calls 'void MainWindow::init_gameboard()' and starts the timer.
void MainWindow::start_game_button_is_clicked()
{
    seed_spin_box_->setEnabled(false);
    start_game_button_->setEnabled(false);
    ui->flag_or_open_push_button->setEnabled(true);

    ui->text_browser->setVisible(true);
    ui->reset_game_push_button->setVisible(true);
    ui->flag_or_open_push_button->setVisible(true);

    board_.init(seed_value_);
    init_gameboard();
    game_timer_->start(TimerIntervalMS);
}

// Makes the GUI gameboard which has the gameboards buttons. The button widgets
// are added to a grid layout that has been centered with spacers in
// mainwindow.ui.
// Adds the <QPushButton *gameboard_button> and the buttons coordinates
// to a map.
void MainWindow::init_gameboard()
{
    for (int i = 0; i < BOARD_SIDE; ++i) {
        for (int j = 0; j < BOARD_SIDE; ++j) {
            QPushButton *gameboard_button = new QPushButton(this);
            gameboard_button->setFixedWidth(30);
            gameboard_button->setStyleSheet("background-color: pink");

            std::vector<int> coordinates;
            coordinates.push_back(i);
            coordinates.push_back(j);

            game_buttons_[gameboard_button] = coordinates;

            // Using only a single row in the grid layout
            ui->game_board_grid->addWidget(gameboard_button, i, j);

            connect(gameboard_button,
                    &QPushButton::clicked,
                    this,
                    &MainWindow::gameboard_button_is_clicked);
        }
    }
    ui->game_board_grid->setHorizontalSpacing(0);
    ui->game_board_grid->setVerticalSpacing(0);
}

// This function is called when one of the <QPushButton *gameboard_button>
// is clicked. The function finds which button was clicked and then gets the
// corresponding square from class Square.
// If the square has a flag and set_flag_ is true, the flag will be removed.
// If square_flag is false and the square is not open the game will end.
// If the square is not open a flag will be added.
// After checking the value of set_flag and if the square is open, the
// gameboard is updated on the screen by calling
// 'void MainWindow::show_gameboard()'
// Then checks if the game is won. If the game is won
// void MainWindow::set_everything_enabled() is called.
void MainWindow::gameboard_button_is_clicked()
{
    int button_index = 0;
    for (std::map<QPushButton *,
                  std::vector<int>>::iterator it = game_buttons_.begin();
         it != game_buttons_.end();
         ++it) {
        if (it->first == sender()) {
            Square square = board_.getSquare((it->second).at(0),
                                             (it->second).at(1));

            if (square.hasFlag()) {
                if (set_flag_) {
                    square.removeFlag();
                }

            } else if (!set_flag_ and !square.open()) {
                ui->text_browser->setText("Game Over");
                ui->text_browser->setStyleSheet("color : #d10038");
                set_everything_enabled();

            } else if (!square.isOpen()) {
                square.addFlag();

                //Checking if game is over
                if (board_.isGameOver()) {
                    ui->text_browser->setText("congrats! you won!");
                    ui->text_browser->setStyleSheet("color : #d10038");
                    set_everything_enabled();
                }
            }

            board_.setSquare(square, (it->second).at(0), (it->second).at(1));
            show_gameboard();
        }
        ++button_index;
    }
}

// Initalizes the window objects shown in the gui.
// Sets a pink style sheet on all of them.
void MainWindow::init_window_objects()
{
    ask_seed_label_ = new QLabel("Enter seed value:", this);
    ask_seed_label_->setGeometry(1, 1, 120, ask_seed_label_->height());
    ask_seed_label_->setStyleSheet("color: #d10038");

    seed_spin_box_ = new QSpinBox(this);
    seed_spin_box_->setGeometry(120, 1, 100, 30);
    seed_spin_box_->setStyleSheet("background-color: pink ; color : #d10038");

    //make start game button
    start_game_button_ = new QPushButton("Start Game", this);
    start_game_button_->setGeometry(230, 1, 100, 30);
    start_game_button_->setStyleSheet("background-color : #d10038 "
                                      "; color : white "
                                      "; font : bold");
    connect(start_game_button_,
            &QPushButton::clicked,
            this,
            &MainWindow::start_game_button_is_clicked);

    //make game timer
    game_timer_ = new QTimer(this);
    connect(game_timer_, &QTimer::timeout, this, &MainWindow::on_sec_timer);

    timer_min_ = new QLCDNumber(this);
    timer_min_->display(0);
    timer_min_->setGeometry(270, 1, 100, 30);
    timer_min_->setFrameStyle(QFrame::NoFrame);
    timer_min_->setStyleSheet("color : white");

    timer_sec_ = new QLCDNumber(this);
    timer_sec_->display(0);
    timer_sec_->setGeometry(300, 1, 100, 30);
    timer_sec_->setFrameStyle(QFrame::NoFrame);
    timer_sec_->setStyleSheet("color : white");

    //make the flag or open button
    connect(ui->flag_or_open_push_button,
            &QPushButton::clicked,
            this,
            &MainWindow::on_flag_or_open_push_button_is_clicked);
    ui->flag_or_open_push_button->setVisible(false);
    ui->flag_or_open_push_button->setStyleSheet(
        "background-color : pink ; color : #d10038 ; font : bold");
    ui->flag_or_open_push_button->setText("open");
    ui->flag_or_open_push_button->setFixedSize(80, 50);

    //create the reset button
    connect(ui->reset_game_push_button,
            &QPushButton::clicked,
            this,
            &MainWindow::reset_game_push_button_is_clicked);
    ui->reset_game_push_button->setStyleSheet(
        "background-color : #d10038 ; color : white ; font : bold");
    ui->reset_game_push_button->setVisible(false);
    ui->reset_game_push_button->setFixedSize(80, 50);

    ui->text_browser->setVisible(false);
}

// Shows the gameboard in the gui window.
// Sets an image for the mine or flag and the numbers for possible
// adjacent mines.
void MainWindow::show_gameboard()
{
    for (std::map<QPushButton *, std::vector<int>>::iterator it = game_buttons_.begin();
         it != game_buttons_.end();
         ++it) {
        Square square = board_.getSquare((it->second).at(0),
                                         (it->second).at(1));
        if (square.hasFlag()) {
            it->first->setIcon(QIcon("images/pink_flag.png"));
        } else if (!square.isOpen()) {
            it->first->setIcon(QIcon());
            it->first->setText("");
        }

        else if (square.hasMine()) {
            it->first->setIcon(QIcon("images/pink_mine.png"));
        } else {
            it->first->setText(QString::number(square.countAdjacent()));
            if (QString::number(square.countAdjacent()) == "0") {
                it->first->setStyleSheet("color : #ffc7d6");
            } else if (QString::number(square.countAdjacent()) == "1") {
                it->first->setStyleSheet("color : #ed809d");
            } else if (QString::number(square.countAdjacent()) == "2") {
                it->first->setStyleSheet("color : #b5244b");
            } else if (QString::number(square.countAdjacent()) == "3") {
                it->first->setStyleSheet("color : #8a0428");
            } else {
                it->first->setStyleSheet("color : #66001b");
            }
        }
        ui->game_board_grid->addWidget(it->first,
                                       (it->second).at(0),
                                       (it->second).at(1));
    }

    ui->game_board_grid->setHorizontalSpacing(0);
    ui->game_board_grid->setVerticalSpacing(0);
}

// Resets the game by creating a new GameBoard board, deletes and erases the
// existing button and their cordinates from the game_buttons map.
// Sets all the widgets so that they are clickable and stops the timer and sets
// time to 0 : 0. Clears the possible text shown in the text_browser.
void MainWindow::reset_game_push_button_is_clicked()
{
    //resetting the gameboards
    board_ = GameBoard();

    for (std::map<QPushButton *,
                  std::vector<int>>::iterator it = game_buttons_.begin();
         it != game_buttons_.end();
         ++it) {
        delete it->first;
    }
    game_buttons_.clear();

    //resetting other widgets
    start_game_button_->setEnabled(true);
    seed_spin_box_->setEnabled(true);
    seed_spin_box_->setValue(0);
    ui->text_browser->clear();

    ui->text_browser->setVisible(false);
    ui->flag_or_open_push_button->setVisible(false);
    ui->flag_or_open_push_button->setIcon(QIcon());
    ui->flag_or_open_push_button->setText("open");
    set_flag_ = false;

    ui->reset_game_push_button->setVisible(false);

    //resetting the timer
    game_timer_->stop();
    timer_min_->display(0);
    timer_sec_->display(0);
}

// When the game ends this function gets called.
// Sets all the other widgets, except the reset button to be not clickable and
// stops the timer.
void MainWindow::set_everything_enabled()
{
    start_game_button_->setEnabled(false);
    seed_spin_box_->setEnabled(false);
    ui->flag_or_open_push_button->setEnabled(false);
    /*
    ui->flag_radio_button->setEnabled(false);
    ui->open_flag_button->setEnabled(false);*/

    game_timer_->stop();

    for (std::map<QPushButton *,
                  std::vector<int>>::iterator it = game_buttons_.begin();
         it != game_buttons_.end();
         ++it) {
        it->first->setEnabled(false);
    }
}

// Changes the image of a flag and the text on the radio button, depending on
// which one is being diplayed when the user clicks it. Also changes the value
// of set_flag_ according to the display.
void MainWindow::on_flag_or_open_push_button_is_clicked()
{
    if (!set_flag_) {
        ui->flag_or_open_push_button->setText("");
        ui->flag_or_open_push_button->setIcon(QIcon("images/pink_flag.png"));
        ui->flag_or_open_push_button->setIconSize(QSize(30, 30));
        set_flag_ = true;
    } else if (set_flag_) {
        ui->flag_or_open_push_button->setIcon(QIcon());
        ui->flag_or_open_push_button->setText("open");
        set_flag_ = false;
    }
}
