#include "acdobject.h"

ACDObject::ACDObject(QObject *parent) : QObject{parent} {
}

ACDObject::ACDObject(QList<QString> fileNames, QObject *parent) : ACDObject(parent) {
  int n = 0;
  for (QString &fileName : fileNames) {
    auto file = new FileItem(fileName, n++, &channels, true);
    connect(file, &FileItem::fileLoaded, this, [=](int index, QString fileName) { this->fileLoaded(index, fileName); });
    files[fileName] = file;
  }
}

void ACDObject::load() {
  for (FileItem *file : std::as_const(files)) {
    file->loadInfo();
    file->loadData();
  }
}

ChannelBlock *ACDObject::operator[](QString name) {
  return channels[name];
}

bool ACDObject::containsChannel(QString name) {
  return (*this)[name] != nullptr;
}

QDateTime ACDObject::start() {
  return channels.start();
}

QDateTime ACDObject::stop() {
  return channels.stop();
}
