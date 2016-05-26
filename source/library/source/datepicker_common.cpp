#include "datepicker/datepicker_common.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>


void init_datepicker(QApplication *app, const QLocale &locale)
{
#ifdef DATEPICKER_LIBRARY_ENABELD
    Q_INIT_RESOURCE(datepicker_resources);
#endif
    QString lang = locale.name().mid(0, 2);

    QTranslator *datepicker_translator = new QTranslator(app);
    if (!datepicker_translator->load(QString(":/datepicker_translations/%1").arg(lang)))
        qDebug() << "failed to load datepicker lib translations for" << lang;

    app->installTranslator(datepicker_translator);
}
