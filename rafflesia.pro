QT += core
QT -= gui

TARGET = rafflesia
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    variable.h

INCLUDEPATH += /home/azkahariz/Downloads/opencv-3.4.4/build/include

LIBS += -L"/home/azkahariz/Downloads/opencv-3.4.4/build/lib"

LIBS += -lopencv_aruco

LIBS += -lopencv_bgsegm

LIBS += -lopencv_bioinspired

LIBS += -lopencv_calib3d

LIBS += -lopencv_ccalib

LIBS += -lopencv_core

LIBS += -lopencv_datasets

LIBS += -lopencv_dnn

LIBS += -lopencv_dpm

LIBS += -lopencv_face

LIBS += -lopencv_features2d

LIBS += -lopencv_flann

LIBS += -lopencv_freetype

LIBS += -lopencv_fuzzy

LIBS += -lopencv_hfs

LIBS += -lopencv_highgui

LIBS += -lopencv_imgcodecs

LIBS += -lopencv_img_hash

LIBS += -lopencv_imgproc

LIBS += -lopencv_line_descriptor

LIBS += -lopencv_ml

LIBS += -lopencv_objdetect

LIBS += -lopencv_optflow

LIBS += -lopencv_phase_unwrapping

LIBS += -lopencv_photo

LIBS += -lopencv_plot

LIBS += -lopencv_reg

LIBS += -lopencv_rgbd

LIBS += -lopencv_saliency

LIBS += -lopencv_shape

LIBS += -lopencv_stereo

LIBS += -lopencv_stitching

LIBS += -lopencv_structured_light

LIBS += -lopencv_superres

LIBS += -lopencv_surface_matching

LIBS += -lopencv_text

LIBS += -lopencv_tracking

LIBS += -lopencv_video

LIBS += -lopencv_videoio

LIBS += -lopencv_videostab

LIBS += -lopencv_xfeatures2d

LIBS += -lopencv_ximgproc

LIBS += -lopencv_xobjdetect

LIBS += -lopencv_xphoto
