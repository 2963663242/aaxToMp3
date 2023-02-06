#include <QWidget>

class QPushButton;
class QGroupBox;
class TaskTableWidget;
class QLabel;
class ConvertWidget : public QWidget
{
    Q_OBJECT

public:
    ConvertWidget(QWidget* parent = nullptr);

private slots:
    void importFile();
private:
    QPushButton* addFile;
    TaskTableWidget* TaskContainer;
    QPushButton* allStart;
    QPushButton* allStop;
    QPushButton* openSave;
    QPushButton* selectSave;
    QLabel* labSavePath;
};