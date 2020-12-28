mkdir logs
mkdir build
cd build
cmake ..
make
mv main ../time_service
mv tests/runUnitTests ../runUnitTests
echo "I'm finished, now you can execute time_service file"