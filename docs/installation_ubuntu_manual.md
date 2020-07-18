## Step by step guide for compilation and dependencies!

##### Attention!
Make sure to set "path to your rathena" and "path to roCORD" corretly.
It's required when a command has "<" ">" in it.

Example:

```
	$ cd <path to your rathena>/src/map
```
In my case will result in:
```
	$ cd /home/norm/rathena/src/map
```


#### Get roCORD and apply the patches.
First we get roCORD src files.
```
  $ git clone https://github.com/Normynator/roCORD.git
  $ cd roCORD
  $ git checkout development
```
Now we go into your rathena folder and apply the patches.
```
  $ cd <path to your rathena>/src/map
  $ patch channel.cpp <path to roCORD>/diff/rev<X>/channel.diff
  $ patch map.cpp <path to roCORD>/diff/rev<X>/map.diff
  $ patch script.cpp <path to roCORD>/diff/rev<X>/script.diff
  $ patch CMakeLists.txt <path to roCORD>/diff/rev<X>/CmakeLists.txt.diff
```
Next we are going to create folders for the roCORD config & src files.
Also copying the files to them.

Usermade patches for newer versions of rathena are avaliable here.
https://github.com/Normynator/roCORD/tree/master/diff/user_patches

Config files:
```
  $ cd ../../conf
  $ mkdir discord
  $ cd discord
  $ cp <path to roCORD>/config/* .
```

Source files:
```
 $ cd ../../src/map
 $ mkdir discord
 $ cp <path to roCORD>/src/* discord
 $ cp <path to roCORD>/CMakeLists.txt discord
 $ cp -r <path to roCORD>/third_party/* <path to rathena>/3rdparty/.
```


#### Installing and compiling dependencies
Now we take care about the dependencies. We go to our home directory and install all requirements.
```
 $ cd
 $ sudo apt-get install libboost-all-dev
 $ sudo apt-get install libcurl4-gnutls-dev
 $ sudo apt-get install libssl1.0-dev
```

#### Compiling and starting rAthena with roCORD!
Last we use all the components to compile roCORD together with rAthena.
```
 $ cd <path to your rathena>
 $ mkdir build
 $ cd build
 $ cmake -G"Unix Makefiles" -DINSTALL_TO_SOURCE=ON ..
 $ make install
```
Done! Now you can leave the build directory and start your server with ./athena-start start.
You should be able to see that roCORD is working when looking at the map-server output.


#### Notes
If you get an error when running make install that has a lot of pointers from boost it's probably because it's trying to target a version of boost that doesn't exist.
You can install the correct version of boost.
```
wget http://sourceforge.net/projects/boost/files/boost/1.53.0/boost_1_53_0.tar.gz
tar -xvzf boost_1_53_0.tar.gz
cd boost_1_53_0/
./bootstrap.sh --with-libraries=atomic,date_time,exception,filesystem,iostreams,locale,program_options,regex,signals,system,test,thread,timer
./b2 install
```
install takes an optional directory parameter `./b2 install --prefix=<install directory>`.

For some reason I had a problem getting the locale library to build correctly if you have that problem.
```
./bootstrap.sh --with-libraries=locale
./bjam boost.locale.posix=off boost.locale.icu=off --with-locale stage install
```
This will disable icu on the build of local and use backend processes instead. It seems to work fine with roCORD.

You can try and target your new boost installation like.
```
cd <path to rathena>
cd build
rm -f CMakeCache.txt
cmake -G"Unix Makefiles" -DINSTALL_TO_SOURCE=ON \ -DBoost_NO_BOOST_CMAKE=TRUE \ -DBOOST_NO_SYSTEM_PATHS=TRUE \ -DBOOST_ROOT:PATHNAME=/usr/local/boost/ \ -DBOOST_LIBRARY_DIRS:FILEPATH=/usr/local/boost/lib ..
```

If that doesn't work you might need to remove your old boost installation.
```
sudo apt-get --purge remove libboost-all-dev
sudo apt-get --purge remove libboost-dev
```

You can tell what version of boost cmake is targeting by the cmake output.
```
cd <path to rathena>
cd build
rm -f CMakeCache.txt
cmake -G"Unix Makefiles" -DINSTALL_TO_SOURCE=ON ..
make install
```

Enjoy!