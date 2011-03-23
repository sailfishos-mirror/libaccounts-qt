/* vi: set et sw=4 ts=4 cino=t0,(0: */
/*
 * This file is part of libaccounts-qt
 *
 * Copyright (C) 2009-2010 Nokia Corporation.
 *
 * Contact: Alberto Mardegan <alberto.mardegan@nokia.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QObject>
#include <QSettings>
#include <QString>
#include <QStringList>

#include "Accounts/accountscommon.h"
#include "Accounts/account.h"
#include "Accounts/error.h"
#include "Accounts/provider.h"
#include "Accounts/service.h"
#include "Accounts/service-type.h"

/*! @namespace Accounts
 *
 */
namespace Accounts
{

/*!
 * @class Manager
 *
 * @brief Manager of accounts, services and providers.
 *
 * @details The Manager offers ways to create accounts, list accounts, services
 * and providers. It also emits signals when accounts are created and removed.
 */
class ACCOUNTS_EXPORT Manager : public QObject
{
    Q_OBJECT

public:

    /*!
     * Constructor.
     * Users should check for manager->lastError() to check if manager construction
     *  was fully succesful, other than just checking for if manager != NULL
     */
    Manager(QObject *parent = 0);

    /*!
     * Constructs a manager initialized with service type. This constructor
     * should be used when there is an interest for just one service type.
     * Such a manager has influence on some class methods. When listing the
     * accounts and services only the ones supporting the given service type
     * will be returned. Also the creating account with this manager will
     * affect the acccount class method for listing services in same manner.
     * The signal enabledEvent() will be emitted only when manager is created
     * with this constructor.
     * Users should check for manager->lastError() to check if manager construction
     * was fully succesful, other than just checking for if manager != NULL
     */
    Manager(const QString &serviceType, QObject *parent = 0);

    /*!
     * Destructor.
     */
    ~Manager();

    /*!
     * Loads an account from the database.
     * @param id Id of the account to be retrieved.
     *
     * @return Requested account or NULL if not found. If NULL is returned,
     * call lastError() to find out why.
     */
    Account *account(const AccountId &id) const;

    /*!
     * Lists the accounts which support the requested service.
     *
     * @param serviceType Type of service that returned accounts must support.
     * If not given and the manager is not constructed with service type,
     * all accounts are returned.
     *
     * @return List of account IDs.
     */
    AccountIdList accountList(const QString &serviceType = QString::null) const;

    /*!
     * Lists the enabled accounts which support the requested service that also
     * must be enabled.
     *
     * @param serviceType Type of service that returned accounts must support.
     * If not given and the manager is not constructed with service type,
     * all enabled accounts are returned.
     *
     * @return List of account IDs.
     */
    AccountIdList accountListEnabled(const QString &serviceType = QString::null) const;

    /*!
     * Creates a new account.
     * @param providerName Name of account provider.
     *
     * @return Created account or NULL if some error occurs.
     */
    Account *createAccount(const QString &providerName);

    /*!
     * Gets an object representing a service.
     * @param serviceName Name of service to get.
     *
     * @return Requested service or NULL if not found.
     */
    Service *service(const QString &serviceName) const;

    /*!
     * Gets the service list. If the manager is constructed with given service type
     * only the services which supports the service type will be returned.
     *
     * @param serviceType Type of services to be listed. If not given and
     * the manager is not constructed with service type, all
     * services are listed.
     *
     * @return List of Service objects.
     */
    ServiceList serviceList(const QString &serviceType = QString::null) const;

    /*!
     * Gets an object representing a provider.
     * @param providerName Name of provider to get.
     *
     * @return Requested provider or NULL if not found.
     */
    Provider *provider(const QString &providerName) const;

    /*!
     * Gets a provider list.
     *
     * @return List of registered providers.
     */
    ProviderList providerList() const;

    /*!
     * Gets an object representing a service type.
     * @param name Name of service type to load.
     *
     * @return Requested service type or NULL if not found.
     */
    ServiceType *serviceType(const QString &name) const;

    /*!
     * Gets the service type if given in manager constructor.
     *
     * @return Service type or NULL if not given.
     */
    QString serviceType() const;

    /*!
     * Sets the timeout for database operations.
     * @param timeout The new timeout in milliseconds.
     *
     * This tells the library how long it is allowed to block while waiting
     * for a locked DB to become accessible. Higher values mean a higher
     * chance of successful reads, but also mean that the execution might be
     * blocked for a longer time. The default is 5 seconds.
     */
    void setTimeout(quint32 timeout);

    /*!
     * Gets the database timeout.
     * @return The timeout (in milliseconds) for database operations.
     */
    quint32 timeout();

    /*!
     * Sets whether to abort the application when a database timeout occurs.
     * By default the library does not abort the application.
     */
    void setAbortOnTimeout(bool abort);

    /*!
     * @return Whether the application will be aborted when a database timeout
     * occurs.
     */
    bool abortOnTimeout() const;

    /*!
     * Gets the last error. Not all operations set/reset the error; see the
     * individual methods' documentation to see if they set the last error or
     * not. Call this method right after an account operation
     * has failed; if no error occurred, the result of this method are
     * undefined.
     *
     * @return The last error.
     */
    Error lastError() const;

signals:
    /*!
     * The signal is emitted when new account is created.
     *
     * @param id Identifier of the Account
     */
    void accountCreated(Accounts::AccountId id);

    /*!
     * The signal is emitted when existing account is removed.
     *
     * @param id Identifier of the Account
     */
    void accountRemoved(Accounts::AccountId id);

    /*!
     * The signal is emitted when any account property for a particular service is updated.
     *
     * To receive this notification user has to create accounts manager using
     * Manager(const QString &serviceType, QObject *parent) constructor.
     * Update notification is only emitted when manager is created for particular type
     * of service.
     *
     * @param id Identifier of the Account
     */
    void accountUpdated(Accounts::AccountId id);

    /*!
     * If the manager has been created with serviceType, this
     * signal will be emitted when an account (identified by AccountId) has been
     * modified in such a way that the application might be interested to start/stop
     * using it: the "enabled" flag on the account or in some service supported by the
     * account and matching the AgManager::serviceType have changed.
     * In practice, this signal might be emitted more often than when strictly needed;
     * applications must call Account::enabledServices() to get the current state.
     *
     * @param id identifier of the Account
     */
    void enabledEvent(Accounts::AccountId id);

private:

    // \cond
    class Private;
    friend class Private;
    Private *d; // Owned.

    Provider *providerInstance(AgProvider *provider) const;
    Service *serviceInstance(AgService *service) const;
    friend class Account;
    // \endcond
}; // Manager

} //namespace Accounts

#endif // ACCOUNTMANAGER_H
