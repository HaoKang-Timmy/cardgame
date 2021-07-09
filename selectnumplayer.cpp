#include "selectnumplayer.h"
#include "ui_selectnumplayer.h"
#include "_21_points.h"
#include "mainwindow.h"
#include "QDebug"
#include "const.h"

selectNumPlayer::selectNumPlayer(QWidget *parent, TYPEGAMES type) :
    QMainWindow(parent),
    ui(new Ui::selectNumPlayer)
{
    ui->setupUi(this);
    port = 2333;
    typeGame = type;
    switch (type) {
        case _21_POINTS:
        setWindowTitle("21点");
        break;
    }
    setWindowFlags(this->windowFlags()& ~Qt::WindowCloseButtonHint);
    //ui->lineEdit->setText("Player1");
    //ui->lineEdit_2->setText("Player2");
    //ui->lineEdit_3->setText("Player3");
    //ui->lineEdit_5->setText("Player4");
    ui->comboBox->setCurrentIndex(2);
}

selectNumPlayer::~selectNumPlayer()
{
    delete ui;
    delete client;
}

/*void selectNumPlayer::on_pushButton_clicked()
{
    switch (ui->comboBox->currentIndex()) {
    case 0: //其实对应的是2，后面以此类推
        if(typeGame == _21_POINTS)
        {
            _21_points *twentyone = new _21_points(nullptr, 2);
            twentyone->setPlayers(ui->lineEdit->text(), ui->lineEdit_2->text());
            this->close();
            twentyone->show();
        }
        break;
    case 1:
        if(typeGame == _21_POINTS)
        {
            _21_points *twentyone = new _21_points(nullptr, 3);
            twentyone->setPlayers(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text());
            this->close();
            twentyone->show();
        }
        break;
    case 2:
        if(typeGame == _21_POINTS)
        {
            _21_points *twentyone = new _21_points(nullptr, 4);
            twentyone->setPlayers(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(), ui->lineEdit_5->text());
            this->close();
            twentyone->show();
        }
        break;
    }
    this->~selectNumPlayer();
}*/


void selectNumPlayer::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0: // 2 players
        ui->Player3->setDisabled(true);
        ui->Player4->setDisabled(true);
        ui->Seatid->clear();
        ui->Seatid->addItem("1");
        ui->Seatid->addItem("2");
        break;
    case 1:
        ui->Player4->setDisabled(true);
        ui->Seatid->clear();
        ui->Seatid->addItem("1");
        ui->Seatid->addItem("2");
        ui->Seatid->addItem("3");
        break;
    default:
        ui->Player3->setDisabled(false);
        ui->Player4->setDisabled(false);
        ui->Seatid->clear();
        ui->Seatid->addItem("1");
        ui->Seatid->addItem("2");
        ui->Seatid->addItem("3");
        ui->Seatid->addItem("4");
    }
}

void selectNumPlayer::on_pushButton_2_clicked()
{
    w1->setHidden(false);
    this->close();
}

void selectNumPlayer::on_CreateBtn_clicked()
{
    QComboBox* comb[5];
    comb[1] = ui->Player1;
    comb[2] = ui->Player2;
    comb[3] = ui->Player3;
    comb[4] = ui->Player4;
    SeatStatus Player[5];
    for(int i = 1; i <= 4; i++)
        if(comb[i]->currentIndex() == 0)
            Player[i] = Free;
        else
            Player[i] = Robot;
    qDebug()<<"player status";
    for(int i = 1; i <= 4; i++)
        qDebug()<<Player[i];
    int Playernum = ui->comboBox->currentIndex() + 2;
    ws = new waitserver(Playernum, Player);
    wt = new waitroom(typeGame, 1, this, ws);
    client = new QUdpSocket(this);
    connect(this,SIGNAL(sendData(QString)), wt,SLOT(getData(QString)));
    sendMessage(NewParticipant);
    wt->show();
    QString Seatid = QString::number(ui->Seatid->currentIndex() + 1);
    emit sendData(Seatid);//发送数据，使用emit
    this->close();
    this->~selectNumPlayer();
}

void selectNumPlayer::on_EnterBtn_clicked()
{
    wt = new waitroom(typeGame, 0, this);
    client = new QUdpSocket(this);
    connect(this,SIGNAL(sendData(QString)), wt,SLOT(getData(QString)));
    sendMessage(NewParticipant);
    wt->show();
    QString Seatid = QString::number(ui->Seatid->currentIndex() + 1);
    emit sendData(Seatid);//发送数据，使用emit
    this->close();
    //this->~selectNumPlayer();
}

void selectNumPlayer::sendMessage(MessageType type)
{
    QByteArray data;    //字节数组
    //QDataStream类是将序列化的二进制数据送到io设备，因为其属性为只写
    QDataStream out(&data, QIODevice::WriteOnly);
    //将type，getUserName()，localHostName按照先后顺序送到out数据流中，消息类型type在最前面
    out << type;
    int Seatid;
    QString localHostName = QHostInfo::localHostName();
    switch(type)
    {

        case NewParticipant :
            Seatid = ui->Seatid->currentIndex() + 1;
            out << localHostName << ui->Username->text()<<Seatid;    //为什么此时只是输出地址这一项呢？因为此时不需要传递聊天内容
            break;

    }
    //一个udpSocket已经于一个端口bind在一起了，这里的data是out流中的data，最多可以传送8192个字节，但是建议不要超过
    //512个字节，因为这样虽然可以传送成功，但是这些数据需要在ip层分组，QHostAddress::Broadcast是指发送数据的目的地址
    //这里为本机所在地址的广播组内所有机器，即局域网广播发送
    client->writeDatagram(data,data.length(),QHostAddress::Broadcast, port);//将data中的数据发送
}

