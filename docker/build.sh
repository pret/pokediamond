#!/bin/bash

set -eou pipefail

PROJECT_NAME=${PROJECT_NAME:-pokediamond}
PROJECT_PATH=${PROJECT_PATH:-$(dirname $(pwd))}

# Build container image
IMAGE_NAME=${IMAGE_NAME:-$PROJECT_NAME-image}
docker build -t $IMAGE_NAME .

# Start container and wine server
CONTAINER_NAME=${CONTAINER_NAME:-$PROJECT_NAME}
docker run -d -i --name $CONTAINER_NAME --rm -t -v $PROJECT_PATH:/$PROJECT_NAME -w /$PROJECT_NAME $IMAGE_NAME

# Build selected project, always exit successfully to ensure container stops
docker exec -i -t $CONTAINER_NAME make $@ || true

# Exit the container and remove
docker stop $CONTAINER_NAME
