#include "roomdefinition.h"
#include "../datamanager.h"
#include "../jpsLineItem.h"
#include "./djsf.h"
#include "./roomID.h"
#include "roomidentification.h"

RoomDefinition::RoomDefinition()
{
    _dManager=nullptr;
}

RoomDefinition::RoomDefinition(const QList<jpsLineItem*>& lineItems, jpsDatamanager* dManager)
{
    _dManager=dManager;

    for (jpsLineItem* lineItem:lineItems)
    {
        if(!lineItem->IsHLine())
        {
            _lines.push_back(lineItem->get_line()->line());
            _lineItems.push_back(lineItem);
        }
    }

}

void RoomDefinition::SetUpRoomsAndDoors()
{
    //*** use code by nick sohre (uofm) (in roomID.h)***

    std::vector<std::vector<double>> floorPlan;

    for (const QLineF& line:_lines)
    {
        std::vector<double> lineasVector1 = {line.p1().x(),
                                    line.p1().y()};
        floorPlan.push_back(lineasVector1);
        std::vector<double> lineasVector2 = {line.p2().x(),
                                    line.p2().y()};
        floorPlan.push_back(lineasVector2);
    }
    if (floorPlan.empty())
        return;

    //std::cout << "Starting" << std::endl;
    std::vector<std::list<double>> roomList = getRooms(floorPlan);
    //std::cout << "Found rooms" << std::endl;
    // *** end of Nicks code ***


    for (const std::list<double>& room:roomList)
    {
        _dManager->new_room();
        jpsRoom* cRoom = _dManager->get_roomlist().back();
        std::vector<double> roomasVector = std::vector<double>{room.begin(),room.end()};
        for (size_t i=0; i<roomasVector.size(); i+=4)
        {
            QLineF line = QLineF(QPointF(roomasVector[i+0],roomasVector[i+1]),QPointF(roomasVector[i+2],roomasVector[i+3]));
            jpsLineItem* cLineItem = FindLineItem(line);
            if (cLineItem->is_Wall())
                cRoom->addWall(cLineItem);

            else if (cLineItem->is_Door())
            {
                // will only be done if crossing not already exists (check in function new_crossing)
                _dManager->new_crossing(cLineItem);

                for (jpsCrossing* crossing:_dManager->get_crossingList())
                {
                    if (crossing->get_cLine()==cLineItem)
                    {
                        crossing->SetRoom(cRoom);
                    }
                }
            }
        }
    }

    for (jpsRoom* room:_dManager->get_roomlist())
    {
        room->IdentifyInnerOuter();
    }

    RemoveOutside();

    RemoveRoomsWithoutDoors();

    // set contigous ids after removing outside
    int idCounter=1;
    for (jpsRoom* room:_dManager->get_roomlist())
    {
        room->set_id(idCounter);
        idCounter++;
        room->change_name("Room "+QString::number(room->get_id()));
    }


    // declare exits
    for (jpsCrossing* crossing:_dManager->get_crossingList())
    {
        if (crossing->get_roomList().size()<2)
        {
            crossing->SetStatExit(true);
            crossing->get_cLine()->setExit();
        }
    }

}

void RoomDefinition::RemoveOutside()
{
    qreal maxArea=_dManager->get_roomlist().front()->GetArea();
    jpsRoom* roomWithMaxArea=_dManager->get_roomlist().front();

    for (jpsRoom* room:_dManager->get_roomlist())
    {
        if (room->GetArea()>maxArea)
        {
            roomWithMaxArea=room;
            maxArea=room->GetArea();
        }
    }

    _dManager->remove_room(roomWithMaxArea);

}

void RoomDefinition::RemoveRoomsWithoutDoors()
{
    for (jpsRoom* room:_dManager->get_roomlist())
    {
        if (room->GetDoors().empty())
            _dManager->remove_room(room);
    }
}


jpsLineItem *RoomDefinition::FindLineItem(const QLineF &line) const
{
    for (jpsLineItem* lineItem:_lineItems)
    {
        if ((lineItem->get_line()->line().p1() == line.p1() && lineItem->get_line()->line().p2() == line.p2())
                || (lineItem->get_line()->line().p1() == line.p2() && lineItem->get_line()->line().p2() == line.p1()))
            return lineItem;
    }
    throw std::invalid_argument("Line does not belong to any lineItem");
    return nullptr;
}

