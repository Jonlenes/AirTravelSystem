#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T16:22:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Aeroporto
TEMPLATE = app


SOURCES +=  main.cpp\
            Mainwindow.cpp \
            Vertex.cpp \
            Edge.cpp \
            Date.cpp \
            Graph.cpp \
            PathAirTransport.cpp \
            Util.cpp \
            DataStructures/List.cpp \
            DataStructures/Stack.cpp \
            DataStructures/Queue.cpp \
            DataStructures/Node.cpp \
            GUI/PopUp.cpp \
            GUI/paintGraph/WidgetGrafo.cpp \
    GUI/paintGraph/EdgePrint.cpp \
    GUI/paintGraph/VertexPrint.cpp \
    GUI/NewTrip.cpp

HEADERS  += Mainwindow.h \
            Vertex.h \
            Edge.h \
            Date.h \
            Graph.h \
            PathAirTransport.h \
            Util.h \
            DataStructures/List.h \
            DataStructures/Stack.h \
            DataStructures/Queue.h \
            DataStructures/Node.h \
            GUI/PopUp.h \
    GUI/paintGraph/EdgePrint.h \
    GUI/paintGraph/VertexPrint.h \
    GUI/NewTrip.h \
    GUI/paintGraph/WidgetGraph.h

FORMS    += Mainwindow.ui \
            GUI/PopUp.ui \
    GUI/NewTrip.ui

RESOURCES += \
    imagens.qrc
