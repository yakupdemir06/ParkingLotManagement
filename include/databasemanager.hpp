#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QString>
#include <QDateTime>
#include <QList>

#include "User.hpp"
#include "pricingplan.hpp"


class DatabaseManager
{
public:
    DatabaseManager(QString dbpath);
    ~DatabaseManager();

    bool ValidateUserLogin(QString username, QString password, QString& errormsg, User** currentUser);
    bool DeleteUser(QString username, QString& errmsg);
    bool CreateUser(QString firstname, QString lastname, QString phone, QString username, QString password, qint32 usertype, QString& errmsg);
    bool NewVehicleEntry(QString plate, QString model, QString type, QString color, QString& errmsg, qint32& vehicleID);
    bool NewPaymentEntry(qint32 vehicleID, QString& errmsg);
    bool GetBillingResult(QString plate, QString& errmsg, qint32& out_paymentID, qint64& out_minutes, qint32& out_vehicleID, QDateTime& out_entryDate);
    bool CompletePayment(qint32 vehicleID, QDateTime exitDate,float hours, float price, QString& errmsg, QString payerName = "");
    bool GetVehicleInformation(qint32 vehicleID, QString& errmsg, QString& out_plate, QString& out_color, QString& out_type, QString& out_model);
    bool GetPricingPlans(QList<PricingPlan*>& out_plans, QString& errmsg);
    bool SetQueryModel_Employees(QSqlQueryModel* out_model, QString& errmsg);
    bool SetQueryModel_Managers(QSqlQueryModel* out_model, QString& errmsg);
    bool SetQUeryModel_Payments(QSqlQueryModel* out_model, QString& errmsg);

    bool isConnected();

    QMap<QString,qint32> getColors();
    QMap<QString,qint32> getVehicleTypes();

private:
    QSqlDatabase database;
    QMap<QString,qint32> m_colors;
    QMap<QString,qint32> m_vehicleTypes;

    void getColorsFromDB();
    void getVehicleTypesFromDB();
};

#endif // DATABASEMANAGER_HPP
