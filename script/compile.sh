WORKSPACE=$(cd "$(dirname "$0")";pwd)/..

BUILD_DIR=$WORKSPACE/build
MY_QT_DIR=/Users/czl/Qt5.12.1/5.12.1/clang_64

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
    cmake -S $WORKSPACE -B "$BUILD_DIR" -G Xcode --config $CONFIG
fi


echo 编译代码

cmake --build "$BUILD_DIR" 

