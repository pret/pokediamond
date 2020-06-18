#!/bin/bash -ex

ZIPFILE=${HOME}/pokediamond.zip

build_name=${1:-pokediamond}
zip -r ${ZIPFILE} ${TRAVIS_BUILD_DIR}
ANONFILES_URL=$(curl -F "file=@$ZIPFILE" https://api.anonfiles.com/upload | grep -Po '"short": "\K[^"]*')
curl -d "{\"username\": \"$CALCROM_DISCORD_WEBHOOK_USERNAME\", \"avatar_url\": \"$CALCROM_DISCORD_WEBHOOK_AVATAR_URL_NOTOK\", \"content\":\"ERROR IN $build_name\\nBranch: $TRAVIS_BRANCH\\nPull request: $TRAVIS_PULL_REQUEST\\nBuild state: $ANONFILES_URL\"}" -H "Content-Type: application/json" -X POST $CALCROM_DISCORD_WEBHOOK_URL
