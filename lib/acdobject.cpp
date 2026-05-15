#include "acdobject.h"

ACDObject::ACDObject(QObject *parent) : QObject{parent} {
  channels = new ChannelArray();
  files = new QList<FileItem*>();
}

ACDObject::ACDObject(QStringList fileNames, QObject *parent) : ACDObject(parent) {
  int n = 0;
  for (const QString &fileName : fileNames) {
    FileItem *file = new FileItem(fileName, n++, channels, true);
    connect(file, &FileItem::fileLoaded, this, [this](int index, QString fileName) {
      emit fileLoaded(index, fileName);
    });
    files->append(file);
  }
}

void ACDObject::load() {
  for (FileItem *file : *files) {
    file->loadInfo();
    file->loadData();
  }
}

void ACDObject::close() {
  for (FileItem *file : *files) {
    file->file()->close();
  }
  foreach (ChannelBlock* channel, *channels) {
    foreach (DataBlock* dataBlock, *channel->dataBlockArray) {
      dataBlock->payload.clear();
      dataBlock->data().clear();
    }
  }
  channels->clear();
}

ChannelBlock *ACDObject::operator[](QString name) {
  return (*channels)[name];
}

bool ACDObject::containsChannel(QString name) {
  return (*this)[name] != nullptr;
}

QDateTime ACDObject::start() {
  return channels->start();
}

QDateTime ACDObject::stop() {
  return channels->stop();
}
