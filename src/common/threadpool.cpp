/*
 * Copyright (C) 2017 ~ 2018 Wuhan Deepin Technology Co., Ltd.
 *
 * Author:     Iceyer <me@iceyer.net>
 *
 * Maintainer: Iceyer <me@iceyer.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "threadpool.h"

#include <QDebug>

ThreadPool::ThreadPool(QObject *parent) : QObject(parent)
{
}

ThreadPool::~ThreadPool()
{
    quitAll();
}

QThread *ThreadPool::newThread()
{
    auto thread = new QThread;
//    qInfo() << "add <<<<<<<" << thread;
    m_pool.push_back(thread);
    return thread;
}

void ThreadPool::moveToNewThread(QObject *obj)
{
    auto work = newThread();
    obj->moveToThread(work);
    work->start();
}

void ThreadPool::quitAll()
{
    for (auto thread : m_pool) {
//        qInfo() << thread;
        thread->quit();
        thread->wait(2000);
    }
    qInfo() << "all thread quit";
}
