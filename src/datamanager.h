/**
 * \file        datamanager.h
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
 * The class is responsible for handling and organisation of rooms, walls and doors. Further more
 * it handles the reading and writing of dxf and xml files.
 *
 **/


#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QtGui>
#include <QApplication>
#include <QGraphicsView>
#include <QMessageBox>
#include "rooms.h"
#include "jpscrossing.h"
#include "jpsLineItem.h"
#include "jpsexit.h"
#include "jpsobstacle.h"
#include "GraphicView.h"
#include "jpsconnection.h"
#include "jpsregion.h"
#include "jpssource.h"
#include <random>

#include "../dxflib/src/dl_creationadapter.h"
#include "../dxflib/src/dl_dxf.h"

using ptrConnection = std::shared_ptr<jpsConnection>;



class jpsDatamanager: public DL_CreationAdapter
{
public:
    jpsDatamanager(QWidget* parent=0L, jpsGraphicsView* view=0L);
    ~jpsDatamanager();
    //Room
    QList<jpsRoom *> get_roomlist();
    void new_room();
    void remove_room(jpsRoom* room);
    void change_roomName(jpsRoom* room, QString name);
    void remove_all_rooms();
    //Obstacle
    QList<jpsObstacle *> get_obstaclelist();
    void new_obstacle();
    void remove_obstacle(jpsObstacle* obs);
    void change_obstacleName(jpsObstacle* obs, QString name);
    void remove_all_obstacles();
    //Crossing
    QList<jpsCrossing *> get_crossingList();
    void new_crossing(QList<jpsLineItem *> newCrossing);
    void new_crossing(jpsLineItem* newCrossing);
    void remove_crossing(jpsCrossing* crossing);
    void change_crossingName(jpsCrossing* crossing, QString name);
    void remove_all_crossings();
    //Exit
    QList<jpsExit *> get_exitList();
    void new_exit(QList<jpsLineItem *> newExits);
    void new_exit(jpsLineItem* newExit);
    void remove_exit(jpsExit* exit);
    void change_exitName(jpsExit* exit, QString name);
    void remove_all_exits();
    //Landmark
    QList<jpsLandmark *> get_landmarks();
    void new_landmark(jpsLandmark * newlandmark);
    void remove_landmark(jpsLandmark* landmark);
    void change_LandmarkName(jpsLandmark* landmark, QString name);
    void remove_all_landmarks();
    const int& GetLandmarkCounter() const;
    //Connection
    const QList<jpsConnection*>& GetAllConnections() const;
    void NewConnection(jpsConnection* newConnection);
    void RemoveConnection(jpsConnection* connection);
    void RemoveAllConnections();
    //Regions
    const QList<jpsRegion*>& GetRegions() const;
    void NewRegion(jpsRegion* region);
    void RemoveRegion(jpsRegion* region);
    void RemoveAllRegions();
    const int& GetRegionCounter() const;
    //Layers
    QList<QString> getElevationList();

    //Sources TODO: write sources by a writer class
    void writeSourceXML(QFile &file);
    void writeSourceHeader(QXmlStreamWriter *stream);
    void writeSources(QXmlStreamWriter *stream, QList<JPSSource *>& sourcelist);
    const QList<JPSSource *> &getSourcelist() const;


    //Goals TODO: write goals by a writer class
    void writeGoalXML(QFile &file);
    void writeGoals(QXmlStreamWriter *stream, QList<JPSGoal *>& goallist);
    const QList<JPSGoal *> &getGoallist();

    //Traffic
    void writeTrafficXML(QFile &file);
    void writeTraffics(QXmlStreamWriter *stream, QList<jpsCrossing *> const &doorlist);
    bool readTrafficXML(QFile &file);
    void readDoor(QXmlStreamReader &xmlReader);


    void remove_all();
    void remove_marked_lines();
    void set_view(jpsGraphicsView* view);
    jpsGraphicsView* get_view();

    // Auto Assign
//    void AutoAssignCrossings();
//    void AutoAssignExits();


    // Read XML

    bool readXML(QFile &file);
    bool readRoutingXML(QFile &file);
    void parseHline(QXmlStreamReader &xmlReader);
    void parseSubRoom(QXmlStreamReader &xmlReader);
    void parseWalls(QXmlStreamReader &xmlReader,jpsRoom* room);
    void parseWalls(QXmlStreamReader &xmlReader,jpsObstacle* room);
    void parseCrossings(QXmlStreamReader &xmlReader);
    void parseTransitions(QXmlStreamReader &xmlReader);
    void parseObstacles(QXmlStreamReader &xmlReader, jpsRoom *room);
    QPointF parseUp(QXmlStreamReader &xmlReader); /// stair's up point
    QPointF parseDown(QXmlStreamReader &xmlReader); /// stair's down point

    // Write XML
    void writeXML(QFile &file);
    void writeRoutingXML(QFile &file);
    void writeLineItems(QFile & file);

    void AutoSaveXML(QFile &file);
    void writeHeader(QXmlStreamWriter *stream);
    void writeRoutingHeader(QXmlStreamWriter *stream);
    void writeHLines(QXmlStreamWriter *stream, QList<jpsLineItem* >& hLines);
    QString RoomIDHLine(jpsLineItem* lineItem);
    void writeRooms(QXmlStreamWriter *stream, QList<jpsLineItem* >& lines);
    void writeSubRoom(QXmlStreamWriter *stream, jpsRoom* room, QList<jpsLineItem* >& lines);
    void AutoSaveRooms(QXmlStreamWriter *stream, QList<jpsLineItem* >& lines);
    void writeCrossings(QXmlStreamWriter *stream, QList<jpsLineItem* >& lines);
    void writeTransitions(QXmlStreamWriter *stream, QList<jpsLineItem* >& lines);
    void writeObstacles(QXmlStreamWriter *stream, jpsObstacle *obs, QList<jpsLineItem *> &lines);
    void writeNotAssignedWalls(QXmlStreamWriter *stream, QList<jpsLineItem* >& lines);
    void writeNotAssignedDoors(QXmlStreamWriter *stream, QList<jpsLineItem* >& lines);
    void writeNotAssignedExits(QXmlStreamWriter *stream, QList<jpsLineItem* >& lines);

    void writeTransitionXML(QFile &file);

    //Write Cognitive Map XML
    void WriteCognitiveMapXML(QFile &file, bool fuzzy=false);
    void WriteCognitiveMapXML(QFile &file, int k, double m, double p0);
    void WriteCognitiveMapHeader(QXmlStreamWriter *stream);
    void WriteRegions(QXmlStreamWriter *stream, bool fuzzy=false);
    void WriteRegions(QXmlStreamWriter *stream, int k, double m, double p0);
    void WriteLandmarks(jpsRegion *cRegion, QXmlStreamWriter *stream, bool fuzzy=false);
    void WriteLandmarks(jpsRegion *cRegion, QXmlStreamWriter *stream, int k, double m, double p0);
    void CutOutLandmarks();
    void CutOutLandmarks(int k, double m, double p0);
    double GetProbability(int k, double m, double p0);
    void BridgeLostLandmark(jpsLandmark* landmark);
    void WriteConnections(jpsRegion *cRegion, QXmlStreamWriter *stream);
    void CreateAndSaveASimilarCogMap(const int &id);
    void CreateAndSaveASimilarCogMap(int id, int k, double m, double p0);
    qreal MakeItFuzzy(const qreal &mean, const qreal& std);
    int GetNumberOfMainTargets() const;

    // Read DXF
    bool readDXF(std::string filename);
    virtual void addLine(const DL_LineData& d);
    // write DXF
    void writeDXF(std::string filename);
    void writeDXFHeader(DL_Dxf* dxf, DL_WriterA *dw);
    void writeDXFTables(DL_Dxf* dxf, DL_WriterA *dw);
    void writeDXFBlocks(DL_Dxf* dxf, DL_WriterA *dw);
    void writeDXFEntities(DL_Dxf* dxf, DL_WriterA *dw);
    void writeDXFObjects(DL_Dxf* dxf, DL_WriterA *dw);

    QString check_printAbility();

    //Parse Cognitive Map
    bool ParseCogMap(QFile &file);
    jpsRegion* ParseRegion(QXmlStreamReader &xmlReader);
    void ParseYAHPointer(QXmlStreamReader &xmlReader, const int &frame);
    void ParseLandmark(jpsRegion* actRegion, QXmlStreamReader &xmlReader);
    void ParseConnection(jpsRegion* actRegion, QXmlStreamReader &xmlReader);

    // read line file
    bool ReadLineFile(QFile &file);



//    //Show Cognitive Map
//    void ShowCMapFrame(const int& frame) const;
//    const double& GetCMapFrameRate() const;
//    const int& GetLastCMapFrame() const;

private:
    //Geometry
    QList<jpsRoom *> roomlist;
    QList<jpsObstacle *> obstaclelist;
    QList<jpsCrossing *> crossingList;
    QList<jpsExit *> exitList;
    QList<jpsLandmark* > _landmarks;
    QList<jpsConnection* > _landmarkConnections;
    QList<jpsLandmark* > _landmarksAfterLoose;
    QList<jpsConnection* > _ConnectionsAfterLandmarkLoose;
    QList<jpsRegion* > _regions;

    QList<JPSSource *> sourcelist;
    QList<JPSGoal *> goallist;

    int room_id_counter;
    int obs_id_counter;
    QWidget* parent_widget;
    jpsGraphicsView* _mView;

    //CognitiveMap
    //QList<jpsLandmark* > _landmarksInCMap;
    //QList<ptrConnection> _connectionsInCMap;
    //double _frameRate;
    //int _lastCMapFrame;
    int _landmarkCounter;
    int _regionCounter;

    QString _currentCogMapFileName;

    std::default_random_engine _generator;

};

//check if two lines are equal with certain tolerance; heading direction of line does not matter
bool LineIsEqual(const QLineF& line1, const QLineF& line2, double eps=0.1);

#endif // DATAMANAGER_H
