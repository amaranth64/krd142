#ifndef COMMONMETHOD_H
#define COMMONMETHOD_H

#include <QObject>
#include <QDebug>
#include <QTime>
#include <QSerialPortInfo>
#include "windows.h"

#include "common/enumTypeData.h"
#include "common/qcustomplot.h"
//#include "common/commondata.h"

//#include "Devices/FTDIAdapter/ftdiadapterdevice.h"
//#include "Devices/GDM78341/gdm78341.h"
//#include "Devices/GDS71072/gds71072.h"
//#include "Devices/GPD72303/gpd72303.h"
//#include "Devices/PCI1727/pci1727.h"
//#include "Devices/PSP405/psp405.h"
//#include "Devices/SDGWaveGenerator/sdgwavegenerator.h"
//#include "Devices/ResistorBox/resistorbox.h"

class CommonMethod : public QObject
{
    Q_OBJECT
public:
    explicit CommonMethod(QObject *parent = nullptr);
    virtual ~CommonMethod();
    
    // метод для старта проверки
    virtual void start() = 0;

    // метод для остановки проверки
    void stop();

    enum ButtonID{ REG_NO_ONE, REG_BTN1, REG_BTN2};

    // методы для работы с диалоговыми окнами с ожиданием их закрытия
    void showMessageDlg(QString caption, QString text);
    void closeMessageDlg();
    bool isMessageDlgShow();

    void startRegulation();
    void stopRegulation();
    bool isRegulation();

    void startRegulationTwoButton();
    void stopRegulationTwoButton(ButtonID btnID);
    bool isRegulationTwoButton();
    ButtonID getButtonID();

    void startMessage();
    void stopMessage();
    bool isMessage();

    QString getAdapterPortName(QString adapterName);



signals:

    void telemetryChanged(QString telemetry);
    void processChanged(QString process);
    void processImageChanged(QString filename);
    void errorChanged(QString error);

    void progressBarChanged(int d); // для работы с progressbar на форме

    // передача сигналов для показа различных окон на главной форме
    void showMessageBox(AppMessageType code, QString text); // для выдачи сообщений без ожидания закрытия окна
    void showMessage(QString caption, QString text); // сигнал для показа окна сообщения с ожиданием закрытия

    void showRegulationTwoButton(QString caption, QString text, QString buttonCaption1, QString buttonCaption2); // сигнал для показа окна регулировки с двумя кнопками
    void showRegulation(QString caption, QString text); // сигнал для показа окна регулировки
    void showRegulationData(QString data); // сигнал для передачи данных в окно регулировки




    // Сигналы для модели таблицы ProgressTable
    void stageChanged(StageData sd); // добавить новый этап (пункт) проверки в таблицу
    void clearAllStage(); // очистить таблицу

    // сигнал высылается после завершения работы со всеми устройствами для уничтожения потока
    void finished();

    // сигналы для вывода данных и результата на экран
    void dataReady(QString rowId, QVariant data);
    void resultReady(QString rowId, QVariant data);



protected:
//    FTDIAdapterDevice *deviceAdapter; // adapter
//    PCI1727 *devicePCI1727;
//    GDM78341 *deviceGDM78341_1;   // multimeter 1
//    GDM78341 *deviceGDM78341_2;   // multimeter 2
//    PSP405 *devicePSP405; // supply power 27V
//    GPD72303 *deviceGPD72303; // supply power 50V
//    GDS71072 *deviceGDS71072; // oscill
//    SDGWaveGenerator *deviceGenerator;
//    ResistorBox *deviceResistorBox; // resistor box секция protected



    // методы для управления работой потока
    void setRunning(bool value);
    bool isRunning();

    // метод ожидания аналог sleep
    void wait(quint16 mstime);

    // добавить этап проверки в таблицу ProgressTable
    void addStageLine(QString punkt, QString text);
    void addProcessLine(QString text);
    void addProcessImage(QVector<double> data);
    void addTelemetryLine(QString text);
    void addErrorLine(QString text);

private:
    bool running = false;
    bool messageDlg = false;
    bool regulation = false;
    bool message = false;
    bool regulationTwoButton = false;
    ButtonID regulationButtonID = REG_NO_ONE;

};

#endif // COMMONMETHOD_H
