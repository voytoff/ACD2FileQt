#include <QTest>
#include <QDirIterator>
#include "acdobject.h"

class ACD2Test : public QObject {
  Q_OBJECT

  public:
  ACD2Test();
  ~ACD2Test() override;

private:
  QVector<QString> getFiles(const QString &path);

  private slots:
  void test_case1();
};

ACD2Test::ACD2Test() {}

ACD2Test::~ACD2Test() = default;

void ACD2Test::test_case1() {
  QList<QString> files(this->getFiles("D:/Пример обработки/Крыло/Пуск 1 - 19gb/"));
  //files.append("D:/Пример обработки/Крыло/Пуск 1 - 19gb/datafile_2_55.acd");
  //files.append("D:/Телеметрия/Files/datafile_3470_1.acd");
  //files.append("D:/Телеметрия/УЭ3/Телеметрия/datafile_175_23.acd");
  ACDObject *acdo = new ACDObject(files, this);
  connect(acdo, &ACDObject::fileLoaded, this, [=](int index, QString fileName) { qDebug() << index << fileName; });
  acdo->load();
  qDebug() << acdo->channels.count() << "каналов";
}

QVector<QString> ACD2Test::getFiles(const QString &path) {
  QVector<QString> result;
  QDirIterator it(path, QStringList() << "*.acd", QDir::Files, QDirIterator::Subdirectories);
  while (it.hasNext())
    result.append(it.next());
  return result;
} // getFiles

QTEST_MAIN(ACD2Test)
//QTEST_APPLESS_MAIN(ACD2Test)

#include "tst_acd2test.moc"
