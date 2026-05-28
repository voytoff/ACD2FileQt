#include <QTest>
#include <QDirIterator>
#include "acdobject.h"

class ACD2Test : public QObject {
  Q_OBJECT

  public:
  ACD2Test();
  ~ACD2Test() override;

private:
  QString path = "D:/Телеметрия/Files";
  QVector<QString> getFiles(const QString &path);

  private slots:
  void test_case1();
};

ACD2Test::ACD2Test() {}

ACD2Test::~ACD2Test() = default;

void ACD2Test::test_case1() {
  QList<QString> temp(this->getFiles(path));
  QList<QString> files;

  files.append(temp.first());

  ACDObject *acdo = new ACDObject(files, this);
  connect(acdo, &ACDObject::fileLoaded, this, [=](int index, QString fileName) { qDebug() << index << fileName; });
  acdo->load();
  qDebug() << acdo->channels->count() << "каналов";
  foreach (auto channel, *acdo->channels) {
    //for (DataBlock* db : *channel->dataBlockArray) { qDebug() << db->channel->name << db->blockID; }
    //std::sort(channel->data().begin(), channel->data().end());
    foreach (Parameter *p, channel->data()) {
      qDebug() << p->index << p->time.toString("dd.MM.yyyy HH:mm:ss.zzz") << p->value;
    }
  }
  acdo->close();
}

QVector<QString> ACD2Test::getFiles(const QString &path) {
  QVector<QString> result;
  QDirIterator it(path, QStringList() << pattern_acd, QDir::Files, QDirIterator::Subdirectories);
  while (it.hasNext())
    result.append(it.next());
  return result;
} // getFiles

QTEST_MAIN(ACD2Test)
//QTEST_APPLESS_MAIN(ACD2Test)

#include "tst_acd2test.moc"
