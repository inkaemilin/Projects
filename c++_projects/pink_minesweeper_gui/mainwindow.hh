#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include <QMainWindow>

#include <map>
#include <QGridLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const QString IS_CLOSED = ".";
const QString HAS_FLAG = "P";
const QString HAS_MINE = "*";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sec_timer();
    void seed_spin_box_value_changed();
    void start_game_button_is_clicked();
    void init_gameboard();
    void gameboard_button_is_clicked();
    void init_window_objects();
    void show_gameboard();
    void reset_game_push_button_is_clicked();
    void set_everything_enabled();
    void on_flag_or_open_push_button_is_clicked();

private:
    Ui::MainWindow *ui;

    QTimer *game_timer_ = nullptr;
    QLabel *ask_seed_label_ = nullptr;
    QSpinBox *seed_spin_box_ = nullptr;
    QPushButton *start_game_button_ = nullptr;
    QGridLayout *gameboard_grid_ = nullptr;
    QLCDNumber *timer_min_ = nullptr;
    QLCDNumber *timer_sec_ = nullptr;

    GameBoard board_;
    std::map<QPushButton *, std::vector<int>> game_buttons_;
    bool set_flag_ = false;

    unsigned int seed_value_ = 0;
};
#endif // MAINWINDOW_HH
