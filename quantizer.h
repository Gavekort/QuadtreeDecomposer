#ifndef QUANTIZER_H
#define QUANTIZER_H
#include <QObject>


class Quantizer : public QObject
{
    Q_OBJECT
public:
    explicit Quantizer(QObject *parent = 0);
    ~Quantizer();
signals:
    void sliderUpdated(int newValue);
private:
    int sliderValue;
};

#endif // QUANTIZER_H
