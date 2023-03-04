#include "commonmethod.h"

CommonMethod::CommonMethod(QObject *parent) : QObject(parent)
{
    qDebug() << "create CommonMethod";


//    devicePCI1727 = new PCI1727("PCI-1727", this);
//    deviceGDM78341_1 = new GDM78341("Multimeter 1", "COM9", QSerialPort::Baud115200, this);
//    deviceGDM78341_2 = new GDM78341("Multimeter 2", "COM11", QSerialPort::Baud115200, this);
//    devicePSP405 = new PSP405("PSP405", "COM2", QSerialPort::Baud2400, this);
//    deviceGPD72303 = new GPD72303("GPD72303", "COM7", QSerialPort::Baud9600, this);
//    deviceGDS71072 = new GDS71072("GDS71072", "COM8", QSerialPort::Baud9600, this);
//    deviceGenerator = new SDGWaveGenerator("Generator", this);
//    deviceResistorBox = new ResistorBox("ResistBox", "COM1", QSerialPort::Baud9600, this);



//    connect(devicePCI1727,&PCI1727::telemetryChanged, this, &CommonMethod::telemetryChanged);
//    connect(devicePCI1727,&PCI1727::errorChanged, this, &CommonMethod::errorChanged);

//    connect(deviceGDM78341_1,&GDM78341::telemetryChanged, this, &CommonMethod::telemetryChanged);
//    connect(deviceGDM78341_1,&GDM78341::errorChanged, this, &CommonMethod::errorChanged);

//    connect(deviceGDM78341_2,&GDM78341::telemetryChanged, this, &CommonMethod::telemetryChanged);
//    connect(deviceGDM78341_2,&GDM78341::errorChanged, this, &CommonMethod::errorChanged);

//    connect(devicePSP405,&PSP405::telemetryChanged, this, &CommonMethod::telemetryChanged);
//    connect(devicePSP405,&PSP405::errorChanged, this, &CommonMethod::errorChanged);

//    connect(deviceGPD72303,&GPD72303::telemetryChanged, this, &CommonMethod::telemetryChanged);
//    connect(deviceGPD72303,&GPD72303::errorChanged, this, &CommonMethod::errorChanged);

//    connect(deviceGDS71072,&GDS71072::telemetryChanged, this, &CommonMethod::telemetryChanged);
//    connect(deviceGDS71072,&GDS71072::errorChanged, this, &CommonMethod::errorChanged);

//    connect(deviceGenerator,&SDGWaveGenerator::telemetryChanged, this, &CommonMethod::telemetryChanged);
//    connect(deviceGenerator,&SDGWaveGenerator::errorChanged, this, &CommonMethod::errorChanged);

//    connect(deviceResistorBox,&ResistorBox::telemetryChanged, this, &CommonMethod::telemetryChanged);
//    connect(deviceResistorBox,&ResistorBox::errorChanged, this, &CommonMethod::errorChanged);
}

CommonMethod::~CommonMethod()
{

//    devicePCI1727->deleteLater();
//    deviceGDM78341_1->deleteLater();
//    deviceGDM78341_2->deleteLater();
//    devicePSP405->deleteLater();
//    deviceGPD72303->deleteLater();
//    deviceGDS71072->deleteLater();
//    deviceGenerator->deleteLater();
	


    qDebug() << "delete CommonMethod";
}

//==============================================================

void CommonMethod::stop()
{
//    devicePSP405->setVoltage(0.0);
//    devicePSP405->setOutput(PSP405::OFF);

//    deviceGPD72303->setVoltageOne(0.0);
//    deviceGPD72303->setOutput(GPD72303::OFF);

//    deviceAdapter->closeDevice();
//    devicePCI1727->closeDevice();
//    deviceGDM78341_1->closeDevice();
//    deviceGDM78341_2->closeDevice();
//    devicePSP405->closeDevice();
//    deviceGPD72303->closeDevice();
//    deviceGDS71072->closeDevice();
//    deviceGenerator->closeDevice();

    emit finished();
    setRunning(false);
    emit progressBarChanged(100);
}

void CommonMethod::wait(quint16 mstime)
{
    mstime = static_cast<quint16>(mstime/100);
    for (quint16 i=0; i < mstime; i++){
        Sleep(100);

        if (!isRunning()) {
            qDebug() << "CommonMethod::wait exit";
            return;
        }
    }
}

void CommonMethod::addStageLine(QString punkt, QString text)
{
    StageData data;
    data.setStageData(QTime::currentTime().toString("hh:mm:ss"), punkt, text);
    emit stageChanged(data);
}

void CommonMethod::addProcessLine(QString text)
{
    emit processChanged(text);
}

void CommonMethod::addTelemetryLine(QString text)
{
    emit telemetryChanged("Методика: " + text);
}

void CommonMethod::addErrorLine(QString text)
{
    emit telemetryChanged("ERROR: Методика - " + text);
}

//==============================================================

void CommonMethod::startRegulation()
{
    regulation = true;
}

void CommonMethod::stopRegulation()
{
    regulation = false;
}

bool CommonMethod::isRegulation()
{
    return regulation;
}

void CommonMethod::startRegulationTwoButton()
{
    regulationTwoButton = true;
    regulationButtonID = REG_NO_ONE;
}

void CommonMethod::stopRegulationTwoButton(CommonMethod::ButtonID btnID)
{
    regulationTwoButton = false;
    regulationButtonID = btnID;
}

bool CommonMethod::isRegulationTwoButton()
{
    return regulationTwoButton;
}

CommonMethod::ButtonID CommonMethod::getButtonID()
{
   return regulationButtonID;
}

void CommonMethod::startMessage()
{
    message = true;
}

void CommonMethod::stopMessage()
{
    message = false;
}

bool CommonMethod::isMessage()
{
    return message;
}

void CommonMethod::showMessageDlg(QString caption, QString text)
{
    emit showRegulation(caption, text);
    messageDlg = true;
}

void CommonMethod::closeMessageDlg()
{
    messageDlg = false;
}

bool CommonMethod::isMessageDlgShow()
{
    return messageDlg;
}

//==============================================================

QString CommonMethod::getAdapterPortName(QString adapterName)
{
    QString result;
    QSerialPortInfo *iPort;
    iPort = new QSerialPortInfo();
    QList<QSerialPortInfo> listPorst;
    listPorst = iPort->availablePorts();

    foreach (QSerialPortInfo port, listPorst){
        qDebug() << port.serialNumber();
        if (port.serialNumber().contains(adapterName)) {

            result = port.portName();
            break;

        }
    }

    delete iPort;
    return result;
}

void CommonMethod::addProcessImage(QVector<double> data)
{
    QCustomPlot *wGraphic = new QCustomPlot();

    // Добавляем график на полотно
    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);

    QVector<double> dataX;
    for (int i=0; i < data.size(); i++) {
        dataX.append(i);
    }

    //=================================================================
    // Смещаем осциллограмму вверх, чтобы убрать отрицательные значения
    //=================================================================
        int nullCount = 0;
        double nullValue = 0;

        for (int i=0; i < data.size(); i++) {
            if (data.at(i) < 0){
                nullCount = nullCount + 1;
                nullValue = nullValue + data.at(i);
            }
        }
        double add = nullValue / nullCount;

        QVector<double> dataOffset;
        for (int i=0; i < data.size(); i++) {
            dataOffset.append(data.at(i) + abs(add));
        }


    wGraphic->graph(0)->setData(dataX, dataOffset);     // Устанавливаем координаты точек графика

    // Подписываем оси координат
    wGraphic->xAxis->setLabel("Отсчеты");
    wGraphic->yAxis->setLabel("I,А");

    // Устанавливаем максимальные и минимальные значения координат
    wGraphic->xAxis->setRange(0, 1000);
    wGraphic->yAxis->setRange(-0.5, 1.5);

//    QString tmp = "image//"
//            + dataASK.getWorkItemType() + "_"
//            + dataASK.getWorkItemNumber() + "_"
//            + QDate::currentDate().toString("ddMMyy") + "_"
//            + QString::number(QTime::currentTime().hour())
//            + QString::number(QTime::currentTime().minute())
//            + QString::number(QTime::currentTime().second())
//            + ".jpg";

//    wGraphic->savePng(tmp);
//    QFile(tmp).copy("telemetry//" + tmp);

//    processImageChanged(tmp);

    wGraphic->deleteLater();
}

//==============================================================

void CommonMethod::setRunning(bool value)
{
    running = value;
}

bool CommonMethod::isRunning()
{
    return running;
}

//==============================================================

