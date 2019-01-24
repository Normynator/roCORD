command -v patch >/dev/null 2>&1 || { echo "I require patch but it's not installed.  Aborting." >&2; exit 1; }
cp -r ../rathena ../rathena.bk
mkdir ../rathena/src/map/discord
mkdir ../rathena/conf/discord
cp CMakeLists.txt ../rathena/src/map/discord/.
cp src/* ../rathena/src/map/discord/.
cp config/* ../rathena/conf/discord/.
cp -r third_party/* ../rathena/3rdparty/.
cd .. # going directory up to avoid ../ patch bug
patch rathena/src/map/channel.cpp roCORD/diff/rev2/channel.diff
patch rathena/src/map/map.cpp roCORD/diff/rev2/map.diff
patch rathena/src/map/script.cpp roCORD/diff/rev2/script.diff
patch rathena/src/map/CMakeLists.txt roCORD/diff/rev2/CmakeLists.txt.diff
mkdir rathena/build
cd rathena/build
cmake -G"Unix Makefiles" -DINSTALL_TO_SOURCE=ON ..
cd ../../roCORD


