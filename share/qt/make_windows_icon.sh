#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/extractcoin.png
ICON_DST=../../src/qt/res/icons/extractcoin.ico
convert ${ICON_SRC} -resize 16x16 extractcoin-16.png
convert ${ICON_SRC} -resize 32x32 extractcoin-32.png
convert ${ICON_SRC} -resize 48x48 extractcoin-48.png
convert extractcoin-16.png extractcoin-32.png extractcoin-48.png ${ICON_DST}

