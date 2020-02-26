#ifndef APPLICATIONWINDOW_HPP
#define APPLICATIONWINDOW_HPP

#include "adminpanel.hpp"
#include "manualvehicleentry.hpp"
#include "manualvehicleexit.hpp"
#include "settingspanel.hpp"
#include "currentplanwindow.hpp"
#include "vehiclesearch.hpp"
#include "ThreadManager.hpp"

#include <QWidget>
#include <QMap>
#include <QString>

class ParkYerim;
class DatabaseManager;
class User;
class PricingPlan;
class Logger;


namespace Ui {
class ApplicationWindow;
}

class ApplicationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationWindow(DatabaseManager* dbmanager, User* user, Logger* logger, QWidget *parent = nullptr);
    ~ApplicationWindow();

    void ClearVehicleInStats();
    void ClearVehicleOutStats();
    QMap<QString, QString> GetAssetPaths();
    DatabaseManager* GetDBManager();
    User* GetCurrentUser();
    QList<PricingPlan*>& GetPricingPlanList();
    void updateCurrentPlan(qint32 planID);
    qint32 getCurrentPlanID() const;

public slots:
    float calculatePrice(qint64 minutes, QString& currentplan);

    void updateRemainingSpots(qint32);
    void increaseRemainingSpotCount();
    void decreaseRemainingSpotCount();
    void drawCamInput_vehicle_in(QPixmap);
    void drawCamInput_vehicle_out(QPixmap);
    void displayLicensePlateString_vehicle_in(QString);
    void displayLicensePlateString_vehicle_out(QString);
    void openCameraStream_in();
    void closeCameraStream_in();
    void openCameraStream_out();
    void closeCameraStream_out();

    qint32 getRemainingSpotCount() const;

private slots:
    void on_toolButton_quit_clicked();
    void showTime();
    void enableToggleCameraButton();
    void on_toolButton_vehicle_in_clicked();

    void on_toolButton_vehicle_out_clicked();

    void on_toolButton_adminpanel_clicked();

    void on_toolButton_settings_clicked();


    void on_pushButton_search_clicked();

    void on_pushButton_currentPlanDetails_clicked();

    void on_pushButton_parkingSpots_clicked();

    void on_pushButton_toggleCameras_clicked();

signals:
    float getPricePlanCalculation(qint64 minutes);
    void terminateAllThreads();

private:
    Ui::ApplicationWindow *ui;
    ParkYerim* m_parent = nullptr;
    DatabaseManager* m_dbmanager = nullptr;
    User* m_currentuser = nullptr;
    Logger* m_logger = nullptr;
    AdminPanel* m_window_admin = nullptr;
    ManualVehicleEntry* m_window_vehicle_in = nullptr;
    ManualVehicleExit* m_window_vehicle_out = nullptr;
    SettingsPanel* m_window_settings = nullptr;
    CurrentPlanWindow* m_window_currentplan = nullptr;
    VehicleSearch* m_window_vehiclesearch = nullptr;
    ThreadManager* m_threadManager = nullptr;

    qint32 m_remainingSpots = 0;
    QList<PricingPlan*> m_pricingPlans;
    qint32 m_currentPlanID = 0;
    PricingPlan* currentPricingPlan = nullptr;

    // camera settings
    bool m_isCameraInputOn = false;
    unsigned int m_vehicleInCameraDeviceIndex = 0;
    unsigned int m_vehicleOutCameraDeviceIndex = 1;

    void initializeAssetPaths();
    void setupIcons();
    void setupCustomComponents();


    QMap<QString, QString> m_assetPaths;

    // programda kullanılacak tüm asset'lerin adları ve dosya yolları burada girilmelidir.
    QList<QString> m_params = {
        "icon_close,        :/Images/assets/images/close.png",
        "icon_print,        :",
        "image_background,  :",
        "icon_settings,     :/Images/assets/images/settings.png",
        "icon_adminpanel,   :/Images/assets/images/adminpanel.png",
        "icon_vehicle_in,   :/Images/assets/images/add_vehicle.png",
        "icon_vehicle_out,  :/Images/assets/images/remove_vehicle.png",
        "icon_search,       :/Images/assets/images/search.png",
        "icon_list,         :/Images/assets/images/list.png",
        "icon_parkingspot,  :/Images/assets/images/parking-icon.png",
        "icon_camera,       :/Images/assets/images/security-camera.png"
    };
};

#endif // APPLICATIONWINDOW_HPP
