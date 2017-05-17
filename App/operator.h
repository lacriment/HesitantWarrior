#ifndef OPERATOR_H
#define OPERATOR_H

#include <QObject>

class Operator : public QObject
{
    Q_OBJECT
public:
    explicit Operator(QObject *parent = 0);

signals:

public slots:
};

#endif // OPERATOR_H