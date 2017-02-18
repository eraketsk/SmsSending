#ifndef SINGLETON_H
/*
 * Copyright (C) <2017>  <Yehor Raketskyi(egormilo@gmail.com)>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define SINGLETON_H

#include <QtGlobal>
#include <QScopedPointer>
#include "call_once.h"

template <class T>
class Singleton
  {
  private:
    typedef T* (*CreateInstanceFunction)();
  public:
    static T* instance(CreateInstanceFunction create);
  private:
    static void init();

    Singleton();
    ~Singleton();
    Q_DISABLE_COPY(Singleton)
    static QBasicAtomicPointer<void> create;
    static QBasicAtomicInt flag;
    static QBasicAtomicPointer<void> tptr;
    bool inited;
  };

template <class T>
T* Singleton<T>::instance(CreateInstanceFunction create)
  {
    Singleton::create.store((void *)create);
    qCallOnce(init, flag);
    return (T*)tptr.load();
  }

template <class T>
void Singleton<T>::init()
  {
    static Singleton singleton;
    if (singleton.inited) {
        CreateInstanceFunction createFunction = (CreateInstanceFunction)Singleton::create.load();
        tptr.store(createFunction());
      }
  }

template <class T>
Singleton<T>::Singleton() {
    inited = true;
  };

template <class T>
Singleton<T>::~Singleton() {
    T* createdTptr = (T*)tptr.fetchAndStoreOrdered(nullptr);
    if (createdTptr) {
        delete createdTptr;
      }
    create.store(nullptr);
  }

template<class T> QBasicAtomicPointer<void> Singleton<T>::create = Q_BASIC_ATOMIC_INITIALIZER(nullptr);
template<class T> QBasicAtomicInt Singleton<T>::flag = Q_BASIC_ATOMIC_INITIALIZER(CallOnce::CO_Request);
template<class T> QBasicAtomicPointer<void> Singleton<T>::tptr = Q_BASIC_ATOMIC_INITIALIZER(nullptr);

#endif // SINGLETON_H
