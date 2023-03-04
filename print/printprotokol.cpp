#include "printprotokol.h"

PrintProtokol::PrintProtokol(QObject *parent) : QObject(parent)
{
    wordApp = new QAxObject("Word.Application", this);
    wordApp->dynamicCall("SetVisible(bool)", false);
    wordApp->setProperty("DisplayAlerts", "0");
    wordDoc = wordApp->querySubObject("Documents");

//    wordApp = new QAxObject("Excel.Application", nullptr);
//    wordApp->dynamicCall("SetVisible(bool)", false);
//    wordApp->setProperty("DisplayAlerts", "0");
//    wordDoc = wordApp->querySubObject("Workbooks");

}

PrintProtokol::~PrintProtokol()
{
    wordApp->dynamicCall("Quit()");
    delete wordDoc;
    delete wordApp;
}

void PrintProtokol::setFileName(QString name)
{
    fileName = name;
}

bool PrintProtokol::print(QMap<QString, QString> data)
{

    QString filePath = QCoreApplication::applicationDirPath() + "\\protokols\\" + fileName;
    bool bOk = QFile::exists(filePath);
    if (!bOk) {
        return false;
    }
    //=======================================================================
    QAxObject *wordOpenDoc = wordDoc->querySubObject("Open(QVariant)", filePath);

    foreach (QString key, data.keys()){
        replaceString(wordApp,"#" + key + "#", data.value(key));
    }

    for (quint8 i=0; i<100; i++)  {
        if (!replaceString(wordApp, "#*#" , "---")) break;
    }

    wordOpenDoc->dynamicCall("PrintOut()");

    Sleep(1000);
    qApp->processEvents();

    QString path = "SaveAs(" + QCoreApplication::applicationDirPath()+ "\\temp.xlsx)";
    std::string stlPath = path.toStdString();
    wordOpenDoc->dynamicCall(stlPath.c_str());

    wordOpenDoc->dynamicCall("Close()");
    wordOpenDoc->deleteLater();
    return true;

}

bool PrintProtokol::replaceString(QAxObject* wordApp, const QString& oldString, const QString& newString)
{
    QAxObject* WordSelection = wordApp->querySubObject("Selection");

    QAxObject* Find = WordSelection->querySubObject("Find");

   if (!Find) return false;
   Find->dynamicCall("ClearFormatting()");


  QList<QVariant> params;
  params.operator << (QVariant(oldString));
  params.operator << (QVariant("0"));
  params.operator << (QVariant("0"));
  params.operator << (QVariant("1"));
  params.operator << (QVariant("0"));
  params.operator << (QVariant("0"));
  params.operator << (QVariant(true));
  params.operator << (QVariant("0"));
  params.operator << (QVariant("0"));
  params.operator << (QVariant(newString));
  params.operator << (QVariant("2"));
  params.operator << (QVariant("0"));
  params.operator << (QVariant("0"));
  params.operator << (QVariant("0"));
  params.operator << (QVariant("0"));
  QVariant res = Find->dynamicCall("Execute(const QVariant&,const QVariant&,"
                    "const QVariant&,const QVariant&,"
                    "const QVariant&,const QVariant&,"
                    "const QVariant&,const QVariant&,"
                    "const QVariant&,const QVariant&,"
                    "const QVariant&,const QVariant&,"
                    "const QVariant&,const QVariant&,const QVariant&)",
                    params);

  delete Find;
  delete WordSelection;
  return res.toBool();
}
