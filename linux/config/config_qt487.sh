#!/bin/sh

export QTDIR=/usr/local/Trolltech/Qt-4.8.7
export QMAKEDIR=$QTDIR/mkspecs
export QMAKESPEC=$QMAKEDIR/linux-g++

export PATH=$QTDIR/bin:$PATH
export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH

export DISPLAY=:0.0
