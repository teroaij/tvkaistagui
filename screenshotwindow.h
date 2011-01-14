#ifndef SCREENSHOTWINDOW_H
#define SCREENSHOTWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include "programme.h"
#include "thumbnail.h"

namespace Ui {
    class ScreenshotWindow;
}

class QLabel;
class QComboBox;
class QSettings;
class TvkaistaClient;

class ScreenshotWindow : public QMainWindow {
    Q_OBJECT
public:
    ScreenshotWindow(QSettings *settings, QWidget *parent = 0);
    ~ScreenshotWindow();
    void setClient(TvkaistaClient *client);
    TvkaistaClient* client() const;
    void fetchScreenshots(const Programme &programme);

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);

private slots:
    void numScreenshotsChanged();
    void feedRequestFinished();
    void thumbnailRequestFinished();
    void networkError(QNetworkReply::NetworkError error);

private:
    void thumbnailsToQueue();
    void fetchNextScreenshot();
    void startLoadingAnimation();
    void stopLoadingAnimation();
    Ui::ScreenshotWindow *ui;
    QSettings *m_settings;
    QLabel *m_loadLabel;
    QComboBox *m_numScreenshotsComboBox;
    QMovie *m_loadMovie;
    TvkaistaClient *m_client;
    QNetworkReply *m_reply;
    QList<Thumbnail> m_thumbnails;
    QList<Thumbnail> m_queue;
    int m_redirections;
    Programme m_programme;
};

#endif // SCREENSHOTWINDOW_H