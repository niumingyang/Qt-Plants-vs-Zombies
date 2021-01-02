#ifndef PVZ_WIDGET_H
#define PVZ_WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QMediaPlayer>

#define buttonstartw 700
#define buttonstarth 70
#define buttonw 200
#define buttonh 80
#define inbutton(x, y, i) (buttonstartw<=(x) && (x)<=buttonstartw+buttonw\
    && buttonstarth+(i)*buttonh<=(y) && (y)<=buttonstarth+(i+1)*buttonh)

class Game;

QT_BEGIN_NAMESPACE
namespace Ui { class PVZ_Widget; }
QT_END_NAMESPACE

class PVZ_Widget : public QWidget
{
    Q_OBJECT

public:
    PVZ_Widget(QWidget *parent = nullptr);
    ~PVZ_Widget();
    void refreshrecord(int level, int score);
    friend class Game;

private:
    Ui::PVZ_Widget *ui;
    QLabel* gamebutton[4];
    QLabel* logo;
    Game* newgame;
    QMediaPlayer* player;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void closeEvent(QCloseEvent *event);

public slots:
    void run();
    void fps();
    void replay(QMediaPlayer::MediaStatus status);
    void startgame(int level = 1);
};
#endif
