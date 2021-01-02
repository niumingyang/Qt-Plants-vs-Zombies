#include "common.h"

PVZ_Widget::PVZ_Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PVZ_Widget)
{
    ui->setupUi(this);
    newgame = nullptr;
    // 设置窗口信息
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    resize(widw, widh);
    setWindowTitle("植物大战僵尸");
    setWindowIcon(QIcon(":/images/interface/icon.ico"));
    // 设置背景音乐
    player = new QMediaPlayer;
    player->setVolume(100);
    player->setMedia(QUrl("qrc:/audio/Faster.mp3"));
    player->play();
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(replay(QMediaPlayer::MediaStatus)));
    // 设置背景
    QPixmap pixmap = QPixmap(":/images/interface/SelectorBackground.png").scaled(this->size());
    QPalette palette (this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(palette);
    // 设置游戏按钮
    vector<QString> v{"简单模式", "正常模式", "困难模式", "排行榜"};
    for (int i = 0; i < 4; ++i){
        gamebutton[i] = new QLabel(this);
        gamebutton[i]->setGeometry(buttonstartw, buttonstarth+i*buttonh, buttonw, buttonh);
        gamebutton[i]->setAlignment(Qt::AlignCenter);
        gamebutton[i]->setStyleSheet(QString("border-image:url(:/images/interface/OptionsButton.png);"
                                        "color:black;"
                                        "font-weight: bold;"
                                        "font-size: 24px;"));
        gamebutton[i]->setText(v[i]);
    }
    logo = new QLabel(this);
    logo->setGeometry(0, 0, 600, 100);
    logo->setPixmap(QPixmap(":/images/interface/LogoWord.jpg"));
}


PVZ_Widget::~PVZ_Widget()
{
    delete ui;
}

void PVZ_Widget::startgame(int level){
    // 释放主界面控件
    for (int i = 0; i < 4; ++i)
        delete gamebutton[i];
    delete logo;
    // 初始化ui
    QPixmap pixmap = QPixmap(":/images/interface/background1unsodded2.jpg").copy(0, 0, widw, widh).scaled(this->size());
    QPalette palette (this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(palette);
    // 设置背景音乐
    player->setMedia(QUrl("qrc:/audio/UraniwaNi.mp3"));
    player->play();
    // 初始化游戏
    newgame = new Game(this, level);
    // 设置刷新定时器
    QTimer* timer = new QTimer(this);
    timer->setInterval(1000/FPS);
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));
    timer->start();
    // 设置帧率定时器
    QTimer* ftimer = new QTimer(this);
    ftimer->setInterval(1000);
    connect(ftimer, SIGNAL(timeout()), this, SLOT(fps()));
    ftimer->start();
}

void PVZ_Widget::run()
{
    newgame->run();
}

void PVZ_Widget::fps()
{
    newgame->showfps();
}

void PVZ_Widget::keyPressEvent(QKeyEvent *event)
{
    if (newgame != nullptr){
        switch(event->key()){
            case Qt::Key_F1:
                newgame->store.addSun(100);
                return;
            case Qt::Key_F2:
                newgame->store.cool2full();
                return;
        }
        switch(newgame->state){
            case RUNNING:  newgame->running(event);  break;
            case CHOOSING: newgame->choosing(event); break;
            case BUYING:   newgame->buying(event);   break;
            case REMOVING: newgame->removing(event); break;
            case GAMEOVER: newgame->gameover(event); break;
            case PAUSE:    newgame->pause(event);    break;
            default: exit(-1);
        }
    }
}

void PVZ_Widget::keyReleaseEvent(QKeyEvent *event)
{
    return;
}

void PVZ_Widget::mousePressEvent(QMouseEvent * event){
//    qDebug() << event->x() << "," << event->y()
//             << "instore:" << instore(event->x(), event->y())
//             << "ingrid:" << ingrid(event->x(), event->y())
//             << "inshovel" << inshovel(event->x(), event->y())
//             << "cardnum:" << cardnum(event->x(), event->y())
//             << "blocks:" << blockx(event->y()) << "," << blocky(event->x());
    if (newgame != nullptr){
        if (newgame->state == RUNNING)
            newgame->keyprocess(event->x(), event->y());
    }
    else {
        for (int i = 0; i < 3; ++i)
            if (inbutton(event->x(), event->y(), i)){
                    startgame(i);
                    return;
            }
        if (inbutton(event->x(), event->y(), 3)){
            vector<vector<string> > rec(3, vector<string>(3, "0"));
            ifstream in("PVZrecord.txt", ios::in);
            if (in){
                for (int i = 0; i < 3; ++i)
                    for (int j = 0; j < 3; ++j)
                        in >> rec[i][j];
            }
            in.close();
            QDialog* dialog = new QDialog(this);
            dialog->setWindowTitle("排行榜");
            dialog->resize(600, 400);
            QLabel* reclab = new QLabel(dialog);
            reclab->resize(600, 400);
            reclab->setAlignment(Qt::AlignCenter);
            reclab->setStyleSheet("color:black;"
                                  "font-weight: bold;"
                                  "font-size: 24px;");
            string recshow = "简单模式:\n"+rec[0][0]+"   "+rec[0][1]+"   "+rec[0][2]+"\n\n"+
                              "正常模式:\n"+rec[1][0]+"   "+rec[1][1]+"   "+rec[1][2]+"\n\n"+
                              "困难模式:\n"+rec[2][0]+"   "+rec[2][1]+"   "+rec[2][2];
            reclab->setText(QString::fromStdString(recshow));
            dialog->show();
            reclab->show();
        }
    }
}

void PVZ_Widget::closeEvent(QCloseEvent *event){
    if (newgame != nullptr) newgame->state = PAUSE;
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出"), QString(tr("确认退出程序")), QMessageBox::Yes|QMessageBox::No);
    if(button == QMessageBox::No){
        event->ignore();
        if (newgame != nullptr) newgame->state = RUNNING;
    }
    else if(button == QMessageBox::Yes){
        if (newgame == nullptr) return;
        else refreshrecord(newgame->level, newgame->score);
        event->accept();
    }
}

void PVZ_Widget::replay(QMediaPlayer::MediaStatus status){
    if(status == QMediaPlayer::EndOfMedia){
        player->setPosition(0);
        player->play();
    }
}

void PVZ_Widget::refreshrecord(int level, int score){
    vector<vector<int>> rec(3, vector<int>(3, 0));
    ifstream in("PVZrecord.txt", ios::in);
    if (in){
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                in >> rec[i][j];
    }
    in.close();
    if (score > rec[level][0]){
        rec[level][1] = rec[level][0];
        rec[level][2] = rec[level][1];
        rec[level][0] = score;
    }
    else if (score > rec[level][1]){
        rec[level][2] = rec[level][1];
        rec[level][1] = score;
    }
    else if (score > rec[level][2])
        rec[level][2] = score;
    ofstream out("PVZrecord.txt", ios::out);
    for (int i = 0; i < 3; ++i)
        out << rec[i][0] << ' ' << rec[i][1] << ' ' << rec[i][2] << '\n';
    out.close();
}
