WORKSPACE=$(cd "$(dirname "$0")";pwd)/..
SCRIPT_DIR=$WORKSPACE/script
PACKAGE_DIR=$WORKSPACE/package
PACKAGE_BIN=$PACKAGE_DIR/bin
PACKAGE_DOC=$PACKAGE_DIR/doc
PACKAGE_INCLUDE=$PACKAGE_DIR/include
CONFIG=Debug
BUILD_DIR=$WORKSPACE/build/x64/$CONFIG
LIBFILE=$BUILD_DIR/liblibAudibleConverter.dylib
DEMOFILE=$BUILD_DIR/AudibleConverter
SDK_BIN=$WORKSPACE/sdk/mac/bin
HEADER_FILE=$WORKSPACE/src/libAudibleConverter/IAudibleConvert.h
DOC_DIR=$WORKSPACE/doc

$WORKSPACE
echo 调用编译脚本
sh "$SCRIPT_DIR"/compile.sh

if [ ! -d "$PACKAGE_DIR" ]; then
	echo 创建 "$PACKAGE_DIR"
	mkdir "$PACKAGE_DIR"
fi

if [ ! -d "$PACKAGE_BIN" ]; then
	echo 创建 "$PACKAGE_BIN"
	mkdir $PACKAGE_BIN
fi

if [ ! -d "$PACKAGE_DOC" ]; then
	echo 创建 "$PACKAGE_DOC"
	mkdir "$PACKAGE_DOC"
fi

if [ ! -d "$PACKAGE_INCLUDE" ]; then
	echo 创建 "$PACKAGE_INCLUDE"
	mkdir "$PACKAGE_INCLUDE"
fi



echo  将$LIBFILE 和 $DEMOFILE 复制到 $PACKAGE_BIN
cp $LIBFILE $DEMOFILE $PACKAGE_BIN

echo 将$SDK_BIN 的所有文件复制到 $PACKAGE_BIN
cp -r $SDK_BIN/* $PACKAGE_BIN

echo 将$HEADER_FILE 复制到 $PACKAGE_INCLUDE
cp $HEADER_FILE $PACKAGE_INCLUDE

echo 将 $DOC_DIR 的所有文档复制到 $PACKAGE_DOC
cp $DOC_DIR/* $PACKAGE_DOC

