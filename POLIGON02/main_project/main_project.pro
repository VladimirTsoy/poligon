#-------------------------------------------------
#
# Project created by QtCreator 2019-06-10T20:34:29
#
#-------------------------------------------------

QT -= core gui

TEMPLATE = subdirs

SUBDIRS += Air
Air.subdir = ../Air

SUBDIRS += Surface
Surface.subdir = ../Surface

SUBDIRS += Poi
Poi.subdir = ../Poi

SUBDIRS += Imit
Imit.subdir = ../Imit

SUBDIRS += input_file_parser
input_file_parser.subdir = ../input_file_parser

SUBDIRS += Grapher2D
Grapher2D.subdir = ../Visualizer/lib/Grapher2D

SUBDIRS += Visualizer
Visualizer.subdir = ../Visualizer

SUBDIRS += GenTypes
GenTypes.subdir = ../RDDS_TGenMsg/GenTypes

CONFIG += warn_on
include(../app.pri)
include(../gen_defs.pri)
message(PWD: $${PWD})
message(PROJECT_PATH: $${PROJECT_PATH})
