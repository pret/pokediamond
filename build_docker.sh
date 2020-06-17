#!/bin/sh

ver="0.1"

docker inspect pokediamond:$ver > /dev/null
if [ $? = 0 ];  then
    echo "Not rebuilding image since image exists";
else
    docker build -t pokediamond:$ver .
fi
docker run --network=none -it -v $(pwd):/app pokediamond:$ver
