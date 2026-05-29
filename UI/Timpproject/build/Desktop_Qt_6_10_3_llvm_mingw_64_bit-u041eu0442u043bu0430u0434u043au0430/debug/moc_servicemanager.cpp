/****************************************************************************
** Meta object code from reading C++ file 'servicemanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../servicemanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'servicemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN14ServiceManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto ServiceManager::qt_create_metaobjectdata<qt_meta_tag_ZN14ServiceManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ServiceManager",
        "connected",
        "",
        "disconnected",
        "error",
        "message",
        "connectionFailed",
        "reconnecting",
        "regRequestCodeResult",
        "success",
        "code",
        "regConfirmResult",
        "authRequestCodeResult",
        "email",
        "authConfirmResult",
        "sessionToken",
        "codeRequestResult",
        "passwordChangeWithCodeResult",
        "functionDataReceived",
        "data",
        "authResult",
        "login",
        "logoutResult",
        "logoutAllResult",
        "refreshTokenResult",
        "newToken",
        "onReadyRead",
        "onConnected",
        "onDisconnected",
        "onError",
        "QAbstractSocket::SocketError",
        "socketError",
        "onReconnectTimer"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'connected'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'disconnected'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'error'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Signal 'connectionFailed'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'reconnecting'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'regRequestCodeResult'
        QtMocHelpers::SignalData<void(bool, const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 }, { QMetaType::QString, 10 },
        }}),
        // Signal 'regConfirmResult'
        QtMocHelpers::SignalData<void(bool)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 },
        }}),
        // Signal 'authRequestCodeResult'
        QtMocHelpers::SignalData<void(bool, const QString &, const QString &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 }, { QMetaType::QString, 13 }, { QMetaType::QString, 10 },
        }}),
        // Signal 'authConfirmResult'
        QtMocHelpers::SignalData<void(bool, const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 }, { QMetaType::QString, 15 },
        }}),
        // Signal 'codeRequestResult'
        QtMocHelpers::SignalData<void(bool)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 },
        }}),
        // Signal 'passwordChangeWithCodeResult'
        QtMocHelpers::SignalData<void(bool)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 },
        }}),
        // Signal 'functionDataReceived'
        QtMocHelpers::SignalData<void(const QString &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 },
        }}),
        // Signal 'authResult'
        QtMocHelpers::SignalData<void(bool, const QString &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 }, { QMetaType::QString, 21 },
        }}),
        // Signal 'logoutResult'
        QtMocHelpers::SignalData<void(bool)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 },
        }}),
        // Signal 'logoutAllResult'
        QtMocHelpers::SignalData<void(bool)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 },
        }}),
        // Signal 'refreshTokenResult'
        QtMocHelpers::SignalData<void(bool, const QString &)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 }, { QMetaType::QString, 25 },
        }}),
        // Slot 'onReadyRead'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onConnected'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDisconnected'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onError'
        QtMocHelpers::SlotData<void(QAbstractSocket::SocketError)>(29, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 30, 31 },
        }}),
        // Slot 'onReconnectTimer'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ServiceManager, qt_meta_tag_ZN14ServiceManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ServiceManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ServiceManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ServiceManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14ServiceManagerE_t>.metaTypes,
    nullptr
} };

void ServiceManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ServiceManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->error((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->connectionFailed(); break;
        case 4: _t->reconnecting(); break;
        case 5: _t->regRequestCodeResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->regConfirmResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->authRequestCodeResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3]))); break;
        case 8: _t->authConfirmResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 9: _t->codeRequestResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 10: _t->passwordChangeWithCodeResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->functionDataReceived((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->authResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 13: _t->logoutResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 14: _t->logoutAllResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 15: _t->refreshTokenResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 16: _t->onReadyRead(); break;
        case 17: _t->onConnected(); break;
        case 18: _t->onDisconnected(); break;
        case 19: _t->onError((*reinterpret_cast<std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 20: _t->onReconnectTimer(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)()>(_a, &ServiceManager::connected, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)()>(_a, &ServiceManager::disconnected, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)(const QString & )>(_a, &ServiceManager::error, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)()>(_a, &ServiceManager::connectionFailed, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)()>(_a, &ServiceManager::reconnecting, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)(bool , const QString & )>(_a, &ServiceManager::regRequestCodeResult, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)(bool )>(_a, &ServiceManager::regConfirmResult, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)(bool , const QString & , const QString & )>(_a, &ServiceManager::authRequestCodeResult, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)(bool , const QString & )>(_a, &ServiceManager::authConfirmResult, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)(bool )>(_a, &ServiceManager::codeRequestResult, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)(bool )>(_a, &ServiceManager::passwordChangeWithCodeResult, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)(const QString & )>(_a, &ServiceManager::functionDataReceived, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)(bool , const QString & )>(_a, &ServiceManager::authResult, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)(bool )>(_a, &ServiceManager::logoutResult, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)(bool )>(_a, &ServiceManager::logoutAllResult, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServiceManager::*)(bool , const QString & )>(_a, &ServiceManager::refreshTokenResult, 15))
            return;
    }
}

const QMetaObject *ServiceManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServiceManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ServiceManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ServiceManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void ServiceManager::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ServiceManager::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ServiceManager::error(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void ServiceManager::connectionFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ServiceManager::reconnecting()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ServiceManager::regRequestCodeResult(bool _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void ServiceManager::regConfirmResult(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void ServiceManager::authRequestCodeResult(bool _t1, const QString & _t2, const QString & _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2, _t3);
}

// SIGNAL 8
void ServiceManager::authConfirmResult(bool _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1, _t2);
}

// SIGNAL 9
void ServiceManager::codeRequestResult(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 10
void ServiceManager::passwordChangeWithCodeResult(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}

// SIGNAL 11
void ServiceManager::functionDataReceived(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1);
}

// SIGNAL 12
void ServiceManager::authResult(bool _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 12, nullptr, _t1, _t2);
}

// SIGNAL 13
void ServiceManager::logoutResult(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 13, nullptr, _t1);
}

// SIGNAL 14
void ServiceManager::logoutAllResult(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 14, nullptr, _t1);
}

// SIGNAL 15
void ServiceManager::refreshTokenResult(bool _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 15, nullptr, _t1, _t2);
}
QT_WARNING_POP
