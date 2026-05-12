#include "acdobject.h"

ACDObject::ACDObject(QObject *parent) : QObject{parent} {
}

ACDObject::ACDObject(QList<QString> fileNames, QObject *parent) : ACDObject(parent) {
  for (QString &fileName : fileNames) {
    files[fileName] = new FileItem(fileName, 0, &channels, true);
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
