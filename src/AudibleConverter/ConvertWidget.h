#include <QWidget>

class QPushButton;
class QGroupBox;

class ConvertWidget : public QWidget
{
    Q_OBJECT

public:
    ConvertWidget(QWidget* parent = nullptr);
private:
    QPushButton* addFile;
    QGroupBox * TaskContainer;
    QPushButton* allStart;
    QPushButton* allStop;
};