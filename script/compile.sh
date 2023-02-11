WORKSPACE=$(cd "$(dirname "$0")";pwd)/..

BUILD_DIR=$WORKSPACE/build
MY_QT_DIR=/Users/czl/Qt5.12.1/5.12.1/clang_64

if [ ! -d "$BUILD_DIR" ]; then
	echo "$BUILD_DIR不存在，重新创建"
	mkdir "$BUILD_DIR"
fi


echo 判断本地有否有预设的qt路径
if [  -d "$MY_QT_DIR" ]; then
    echo "$MY_QT_DIR 存在，使用该qt"
    CMAKE_PREFIX_PATH=$MY_QT_DIR
fi

echo 选择编译模式
if [ "$CONFIG" != "Release" ]; then
    CONFIG=Debug
fi
echo "选择 $CONFIG 编译模式"

echo 生成工程
if [ $CMAKE_PREFIX_PATH ];then
    cmake -S $WORKSPACE -B "$BUILD_DIR" -G Xcode -DCMAKE_PREFIX_PATH="$CMAKE_PREFIX_PATH"
else
    cmake -S $WORKSPACE -B "$BUILD_DIR" -G Xcode 
fi




echo 获取git版本号
svnInfoResult=`git rev-list HEAD --count`
svnVersion=${svnInfoResult##* }
DYLIB_CURRENT_VERSION="1.1.${svnVersion}"
DYLIB_COMPATIBILITY_VERSION="1.0.1"
GCC_PREPROCESSOR_DEFINITIONS="LIB_VERSION=\\\"${DYLIB_CURRENT_VERSION}\\\""



echo 编译代码

BUILD_SETTING=" -configuration $CONFIG DYLIB_CURRENT_VERSION=${DYLIB_CURRENT_VERSION} DYLIB_COMPATIBILITY_VERSION=${DYLIB_COMPATIBILITY_VERSION} GCC_PREPROCESSOR_DEFINITIONS=${GCC_PREPROCESSOR_DEFINITIONS} build"

xcodebuild -project $BUILD_DIR/libAudibleConverter.xcodeproj -target libAudibleConverter $BUILD_SETTING
xcodebuild -project $BUILD_DIR/libAudibleConverter.xcodeproj -target AudibleConverter $BUILD_SETTING



