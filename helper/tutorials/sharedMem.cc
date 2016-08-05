Class Dialog
{
private:
	QSharedMemory sharedMemory;
}

Dialog::Dialog()
: sharedMemory("QSharedMemoryExample")
{

}

void Dialog::loadFromFile()
{
	//testa se ta attached a um process
	if(sharedMemory.isAttached())
		detach();

	//Creating a shared memory segment automatically 
	//attaches the segment to the process.
	if (!sharedMemory.create(size)) {
        ui.label->setText(tr("Unable to create shared memory segment."));
        return;
    }

    sharedMemory.lock();
    char *to = (char*)sharedMemory.data();
    const char *from = buffer.data().data();
    memcpy(to, from, qMin(sharedMemory.size(), size));
    sharedMemory.unlock();
}

void Dialog::loadFromMemory()
{
	if (!sharedMemory.attach()) {
        ui.label->setText(tr("Unable to attach to shared memory segment.\n" \
                             "Load an image first."));
        return;
    }

    QBuffer buffer;
    QDataStream in(&buffer);
    QImage image;

    sharedMemory.lock();
    buffer.setData((char*)sharedMemory.constData(), sharedMemory.size());
    buffer.open(QBuffer::ReadOnly);
    in >> image;
    sharedMemory.unlock();

    sharedMemory.detach();
    ui.label->setPixmap(QPixmap::fromImage(image));
}
