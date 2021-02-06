#!/bin/sh

PROJECT_PATH="$(git rev-parse --show-toplevel)"
PROJECT_NAME="pokediamond"
PROJECT_VER="0.1"

# Build container image
IMAGE_NAME="$PROJECT_NAME:$PROJECT_VER"
IMAGE_PATH="$PROJECT_PATH/contrib/docker"
if docker inspect $IMAGE_NAME > /dev/null; then
    echo "Not rebuilding image since it already exists";
elif [ "x$USE_UBUNTU" != "x" ]; then
    docker build -t $IMAGE_NAME -f $IMAGE_PATH/Dockerfile.ubuntu $IMAGE_PATH
else
    docker build -t $IMAGE_NAME $IMAGE_PATH
fi

# Start container and wine server
CONTAINER_NAME="$PROJECT_NAME-build"
docker run -d --name $CONTAINER_NAME --network=none -it --rm -v $PROJECT_PATH:/app $IMAGE_NAME

# Build selected project, always exit successfully to ensure container stops
EXIT_CODE="0"
docker exec -i -t $CONTAINER_NAME make $@ || EXIT_CODE="$?"

# Exit and remove the container
docker stop $CONTAINER_NAME

exit $EXIT_CODE
