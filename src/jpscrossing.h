/**
 * \file        jpscrossing.h
 * \date        Oct-01-2018
 * \version     v0.8.4
 * \copyright   <2009-2018> Forschungszentrum Jülich GmbH. All rights reserved.
 *
 * \section License
 * This file is part of JuPedSim.
 *
 * JuPedSim is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * JuPedSim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with JuPedSim. If not, see <http://www.gnu.org/licenses/>.
 *
 * \section Description
 * This class is representing a door to another room in the building or to the outside.
 *
 **/

#ifndef JPSCROSSING_H
#define JPSCROSSING_H

#include "rooms.h"

class jpsCrossing
{
public:
    jpsCrossing(jpsLineItem *line);

    jpsCrossing(jpsLineItem *cLine, bool isExit, float elevation);

    ~jpsCrossing(){}
    QList<jpsRoom *> get_roomList();
    QString get_name();
    int get_id();
    void set_id(int id);
    jpsLineItem *get_cLine();
    void change_name(QString name);
    void add_rooms(jpsRoom* room1, jpsRoom* room2=0L);
    void SetRoom(jpsRoom* room);
    void RemoveRoom(jpsRoom* room);
    void SetStatExit(bool stat);
    bool IsExit();
    float get_elevation();
    void set_elevation(float elevation);

    QString getMaxAgents() const;

    void setMaxAgents(QString maxAgents);

    QString getOutflow() const;

    void setOutflow(QString outflow);

    bool isState() const;

    void setState(bool state);


private:
    QList<jpsRoom *> roomList;
    QString cName;
    jpsLineItem *cLine;
    int cId;
    bool _isExit;
    float _elevation;
    bool state;
    QString max_agents;
    QString outflow;
};

#endif // JPSCROSSING_H
