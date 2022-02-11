rm -f r-type_server
rm -f r-type_client
rm -rf bin
mkdir bin
cd _buildClient && conan install .. --build=missing
cd ../_buildServer && conan install .. --build=missing
cd ../client && cmake -H. -B../_buildClient
cd ../server && cmake -H. -B../_buildServer
cd ../_buildClient && make -j6 && cp r-type_client ../bin
cd ../_buildServer && make -j6 && cp r-type_server ../bin