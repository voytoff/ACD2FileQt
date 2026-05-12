#include <QTest>
#include "acdobject.h"

class ACD2Test : public QObject {
  Q_OBJECT

  public:
  ACD2Test();
  ~ACD2Test() override;

  private slots:
  void test_case1();
};

ACD2Test::ACD2Test() {}

ACD2Test::~ACD2Test() = default;

void ACD2Test::test_case1() {
  QList<QString> files;
  files.append("D:/Телеметрия/Files/datafile_3470_1.acd");
  //files.append("D:/Телеметрия/УЭ3/Телеметрия/datafile_175_23.acd");
  ACDObject *acdo = new ACDObject(files, this);
  qDebug() << acdo->channels.count() << "каналов";
}

QTEST_MAIN(ACD2Test)
//QTEST_APPLESS_MAIN(ACD2Test)

#include "tst_acd2test.moc"
