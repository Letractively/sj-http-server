/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011-2012  Jakub Wachowski

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef HANDLERDATA_H
#define HANDLERDATA_H

#include <QString>
#include "abstractrequesthandler.h"

/**
 * @brief Stores information and settings of request handlers
 */
class HandlerData
{
public:
    /**
     * @brief Default constructor, does nothing
     */
    HandlerData();

    /**
     * @brief Constructs HandlerData with provided handler and its settings group
     * @param handler pointer to a request handler
     * @param settingsGroup key associated with a handler that indicate its settings
     */
    HandlerData(AbstractRequestHandler * handler, const QString & settingsGroup);

    /**
     * @brief Destructor
     */
    ~HandlerData();

    /**
     * @brief returns context root of a hansler
     *
     * for example if handler is available under http://www.exmple.com/myhandler
     *  its context root is /myhandler
     *
     * @return handler's context root
     */
    QString getContextRoot() const;

    /**
     * @brief Returns pointer to a request handler
     *
     * @return pointer to a request handler
     */
    AbstractRequestHandler * getHandler() const {return handler;}

    /**
     * @brief returns setting group associated with a request handler
     *
     * @return settings group
     */
    QString getSettingsGroup() const { return settingsGroup; }
private:
    AbstractRequestHandler * handler;
    QString settingsGroup;
};

#endif // HANDLERDATA_H
