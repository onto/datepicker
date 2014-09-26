#include "datepicker/datepicker.h"
#include <QDate>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QVBoxLayout>
#include <QLabel>
#include "datepicker/datepickerpopup.h"
#include "datepicker/datepickerabstractformater.h"


class DatePickerPrivate {
    Q_DECLARE_PUBLIC(DatePicker)

    DatePicker *q_ptr;
    DatePickerType picker_type;
    QDate date_begin;
    QDate date_end;
    QLabel *date_label;
    DatePickerPopup *popup;
    DatePickerAbstractFormater *formater;
private:
    DatePickerPrivate(DatePicker *q) : q_ptr(q), date_label(0), popup(0), formater(0) {}
    ~DatePickerPrivate() { delete popup; }

    void initUi()
    {
        Q_Q(DatePicker);

        date_label = new QLabel(q);
        date_label->installEventFilter(q);
        date_label->setCursor(Qt::PointingHandCursor);

        popup = new DatePickerPopup();
        popup->installEventFilter(q);

        q->setLayout(new QVBoxLayout(q));
        q->layout()->setContentsMargins(QMargins());
        q->layout()->addWidget(date_label);

        q->setWindowTitle(QObject::tr("Date Picker"));
    }
};

DatePicker::DatePicker(QWidget *parent) :
    QWidget(parent),
    d_ptr(new DatePickerPrivate(this))
{
    Q_D(DatePicker);
    d->initUi();

    connect(d->popup, SIGNAL(dateSelected(QDate)), SLOT(setDate(QDate)));
    connect(d->popup, SIGNAL(periodSelected(QDate,QDate)), SLOT(setPeriod(QDate,QDate)));
}

DatePicker::~DatePicker()
{
    delete d_ptr;
}

QLabel *DatePicker::label() const
{
    Q_D(const DatePicker);
    return d->date_label;
}

QWidget *DatePicker::popup() const
{
    Q_D(const DatePicker);
    return d->popup;
}

DatePickerAbstractFormater *DatePicker::formater() const
{
    Q_D(const DatePicker);
    return d->formater;
}

void DatePicker::setFormater(DatePickerAbstractFormater *formater)
{
    Q_D(DatePicker);
    d->formater = formater;

    if (d->formater != 0) {
        if (d->picker_type == DayType)
            setDate(d->date_begin);
        if (d->picker_type == PeriodType)
            setPeriod(d->date_begin, d->date_end);
    }
}

DatePickerType DatePicker::pickerType() const
{
    Q_D(const DatePicker);
    return d->picker_type;
}

QDate DatePicker::selectedDate() const
{
    Q_D(const DatePicker);
    return d->date_begin;
}

QDate DatePicker::selectedPeriodBegin() const
{
    Q_D(const DatePicker);
    return d->date_begin;
}

QDate DatePicker::selectedPeriodEnd() const
{
    Q_D(const DatePicker);
    return d->date_end;
}

void DatePicker::setAllowedPickerTypes(DatePickerTypes picker_types)
{
    Q_D(DatePicker);
    d->popup->setAllowedPickerTypes(picker_types);
}

void DatePicker::setDate(const QDate &date)
{
    Q_D(DatePicker);

    d->picker_type = DayType;

    d->date_begin = date;
    d->date_end = date;

    d->popup->setDate(date);

    if (d->formater != 0)
        d->date_label->setText(d->formater->format(date));
    else
        d->date_label->clear();
}

void DatePicker::setPeriod(const QDate &begin, const QDate &end)
{
    Q_D(DatePicker);

    d->picker_type = PeriodType;

    d->date_begin = begin;
    d->date_end = end;

    d->popup->setPeriod(begin, end);

    if (d->formater != 0)
        d->date_label->setText(d->formater->format(begin, end));
    else
        d->date_label->clear();
}

bool DatePicker::eventFilter(QObject *object, QEvent *event)
{
    Q_D(DatePicker);

    if ((object == d->date_label) && (event->type() == QEvent::MouseButtonRelease)) {
        QMouseEvent *mouse_event = dynamic_cast<QMouseEvent *>(event);
        if (!mouse_event)
            return false;

        if (mouse_event->button() != Qt::LeftButton)
            return false;

        if (d->popup->isVisible()) {
            d->popup->close();
            emit editingFinished();
        }
        else {
            d->popup->reset();

            if (d->picker_type == DayType)
                d->popup->setDate(d->date_begin);
            if (d->picker_type == PeriodType)
                d->popup->setPeriod(d->date_begin, d->date_end);

            d->popup->show();
            d->popup->activateWindow();
        }
    }

    return false;
}

void DatePicker::moveEvent(QMoveEvent *event)
{
    QWidget::moveEvent(event);

    Q_D(DatePicker);
    d->popup->move(mapToGlobal(rect().bottomLeft()));
}

void DatePicker::closeEvent(QCloseEvent *event)
{
    Q_D(DatePicker);
    d->popup->close();
    QWidget::closeEvent(event);
}
