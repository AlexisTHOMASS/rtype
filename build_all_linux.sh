rm -f r-type_server
rm -f r-type_client
rm -rf _buildClient
rm -rf _buildServer
rm -rf bin
mkdir _buildClient
mkdir _buildServer
cd _buildClient && conan install .. --build=missing
cd ../_buildServer && conan install .. --build=missing
cd ../client && cmake -H. -B../_buildClient
cd ../server && cmake -H. -B../_buildServer
cd ../_buildClient && make -j6 && cp -r bin ..
cd ../_buildServer && make -j6 && cp -r bin ..