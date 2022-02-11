rm -f r-type_server
rm -f r-type_client
rm -rf bin
cd client && cmake -H. -B../_buildClient
cd ../server && cmake -H. -B../_buildServer
cd ../_buildClient && make -j6 && cp -r bin ..
cd ../_buildServer && make -j6 && cp -r bin ..