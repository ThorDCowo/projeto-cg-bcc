#include <QTest>

class TestQString: public QObject
{
    Q_OBJECT
    private slots:
        void toUpper();
        void toUpper_data();
};